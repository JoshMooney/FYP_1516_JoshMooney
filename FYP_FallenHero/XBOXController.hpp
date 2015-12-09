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
	map<string, bool> isPressed;
	map<string, bool> wasPressed;
	map<string, bool> isPressed_cleared;

	XBOXController();
	XBOXController(bool is_output);
	~XBOXController();

	//Check if controller is connected
	bool isConnected();

	//Make the controller rumble
	void Rumble(int l_rm, int r_rm);

	void UpdateButtons();
	bool isIdle();

	float getRT();
	float getLT();
	std::pair<float, float> getRightAnalog();
	std::pair<float, float> getLeftAnalog();
};

#endif