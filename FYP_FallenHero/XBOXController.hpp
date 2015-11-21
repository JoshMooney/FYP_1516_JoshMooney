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

class XBOXController {
private:
	XINPUT_STATE state;
	XINPUT_VIBRATION motor;
	bool output;

	void UpdateA();
	void UpdateB();
	void UpdateX();
	void UpdateY();

	void UpdateDpadUp();
	void UpdateDpadDown();
	void UpdateDpadRight();
	void UpdateDpadLeft();

	void UpdateRB();
	void UpdateLB();

	void UpdateStart();
	void UpdateBack();
public:
	map<string, bool> isPressed;
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

	
};

#endif