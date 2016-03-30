#ifndef _XBOX_CONTROLLER_HPP
#define _XBOX_CONTROLLER_HPP
#include "stdafx.h"

#include <Xinput.h>
#pragma comment(lib, "XInput9_1_0.lib")   // Library. If your compiler doesn't support this type of lib include change to the corresponding one
//#pragma comment(lib,"xinput.lib") 
/*
#pragma comment(lib,"xinput.lib") 
#elif (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*) 
#include <XInput.h> 
#pragma comment(lib,"xinput.lib") 
#else 
#include <XInput.h> 
#pragma comment(lib,"xinput9_1_0.lib") 
#endif 
*/
#include <map>
#include "cLog.hpp"
#include <utility>

/**
*	@class XBOXController
*	@brief This is an instance of the XBOX controller which uses xinput v9.1.0 to detect and store
*	information on the first controller connected to the system. This class will be passed around 
*	by the game to different scenes to detect input only if the controller is actually connected.
*	Otherwise the keyboard is passed around for input checking.
*/

class XBOXController {
private:
	XINPUT_STATE state, prev_state;
	XINPUT_VIBRATION motor;
	bool connected;
	bool output;

	void UpdateA();
	void UpdateB();
	void UpdateX();
	void UpdateY();

	void UpdateDpadUp();
	void UpdateDpadDown();
	void UpdateDpadRight();
	void UpdateDpadLeft();

	void UpdateLeftAnalogUp();
	void UpdateLeftAnalogDown();
	void UpdateLeftAnalogRight();
	void UpdateLeftAnalogLeft();

	void UpdateRightAnalogUp();
	void UpdateRightAnalogDown();
	void UpdateRightAnalogRight();
	void UpdateRightAnalogLeft();

	void UpdateAnalogSticks();
	void UpdateTriggers();

	void UpdateRB();
	void UpdateLB();

	void UpdateStart();
	void UpdateBack();

	/*Deadzones*/
	float dz_LX, dz_LY;
	float dz_RX, dz_RY;
	const float DEADZONE_MAX = 1.f;
	const float ANALOG_GREATEST_DIR = 0.51f;
	/*Trigger Thresholds*/
	float threshold_LT, threshold_RT;
	const float THRESHOLD_MAX = 1.f;
	/*Left & Right Stick Values*/
	float left_X, left_Y;
	float right_X, right_Y;
	const short STICK_MAX = 32767;
	/*Trigger Values*/
	float left_trigger, right_trigger;
	const BYTE TRIGGER_MAX = 255;
public:
	map<string, bool> isPressed;			//!<Is a map of strings to bools used for identlifing the keys to a bool for whether its pressed.
	map<string, bool> wasPressed;           //!<Is a map of strings to bools used for identlifing the keys to a bool for whether the key was pressed.
	map<string, bool> isPressed_cleared;    //!<This is a cleared lists of keys to false bools.

	/**
	*	@brief The default constructor for the Xbox contrller class, the variables for triggers, bumpers and
	*	analog will be initalised and the isPressed map must be set up.
	*/
	XBOXController();
	/**
	*	@brief The overloaded constructor for the Xbox contrller class, the variables for triggers, bumpers and
	*	analog will be initalised and the isPressed map must be set up. This object will output button presses.
	*	@param bool Wheather or not there is debug output for the controller.
	*/
	XBOXController(bool is_output);
	/**
	*	@brief This is the deconstructor for the XBOX Controller class
	*/
	~XBOXController();

	/**
	*	@brief A check for if the controller is connected or not.
	*	@return bool return true if connected else return false if not connected
	*/
	bool isConnected();

	/**
	*	@brief This function rumbles the controller by the amount of the values passed in.
	*	@param l_rm is the amount of rumble of the left motor
	*	@param r_rm is the amount of rumble of the right motor
	*/
	void Rumble(int l_rm, int r_rm);

	/**
	*	@brief This method calls all the individual update button private methods in the 
	*	class eg. UpdateA(), UpdateAnalogSticks() etc.
	*/
	void UpdateButtons();
	/**
	*	@brief Simple check to see whether or not the controller is idle this compairs the
	*	isPressed_cleared against the isPressed and returns the result.
	*	@return bool if the controller is idle or not.
	*/
	bool isIdle();

	/**
	*	@brief This function gets the value of the Right Trigger press
	*	@return float Value of right trigger press
	*/
	float getRT();
	/**
	*	@brief This function gets the value of the Left Trigger press
	*	@return float Value of left trigger press 
	*/
	float getLT();
	/**
	*	@brief This function fetchs the x and y axis of the right analog stick.
	*	@return std::pair Of floats to the x and y values.
	*/
	std::pair<float, float> getRightAnalog();
	/**
	*	@brief This function fetchs the x and y axis of the left analog stick.
	*	@return std::pair Of floats to the x and y values.
	*/
	std::pair<float, float> getLeftAnalog();
};

#endif