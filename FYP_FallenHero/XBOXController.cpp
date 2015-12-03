#include "stdafx.h"
#include "XBOXController.hpp"

XBOXController::XBOXController()
{
	output = false;
	memset(&state, 0, sizeof(XINPUT_STATE));
	memset(&motor, 0, sizeof(XINPUT_VIBRATION));

	isPressed["A"] = false;
	isPressed["B"] = false;
	isPressed["X"] = false;
	isPressed["Y"] = false;

	isPressed["LB"] = false;
	isPressed["RB"] = false;

	isPressed["START"] = false;
	isPressed["SELECT"] = false;

	isPressed["D_UP"] = false;
	isPressed["D_DOWN"] = false;
	isPressed["D_LEFT"] = false;
	isPressed["D_RIGHT"] = false;

	isPressed_cleared = isPressed;
}
XBOXController::XBOXController(bool is_output)	{
	output = is_output;
	memset(&state, 0, sizeof(XINPUT_STATE));
	memset(&motor, 0, sizeof(XINPUT_VIBRATION));

	isPressed["A"] = false;
	isPressed["B"] = false;
	isPressed["X"] = false;
	isPressed["Y"] = false;

	isPressed["LB"] = false;
	isPressed["RB"] = false;

	isPressed["START"] = false;
	isPressed["SELECT"] = false;

	isPressed["D_UP"] = false;
	isPressed["D_DOWN"] = false;
	isPressed["D_LEFT"] = false;
	isPressed["D_RIGHT"] = false;
	isPressed_cleared = isPressed;
}
XBOXController::~XBOXController()
{

}

bool XBOXController::isConnected()
{
	if (output)		cLog::inst()->print(3, "XBOXController", "XBOXController is Checking for Xbox controller.");
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (output)		cLog::inst()->print(3, "XBOXController", "Xbox controller connected successfully.");
		return true;
	}
	else
	{
		if (output)		cLog::inst()->print(3, "XBOXController", "No Xbox controller detected.");
		return false;
	}
}

void XBOXController::Rumble(int l_rm, int r_rm)
{
	motor.wLeftMotorSpeed = l_rm;
	motor.wRightMotorSpeed = r_rm;
	XInputSetState(0, &motor);
}

void XBOXController::UpdateButtons(){
	//isPressed = isPressed_cleared;
	wasPressed = isPressed;
	UpdateA();
	UpdateB();
	UpdateX();
	UpdateY();
	UpdateDpadUp();
	UpdateDpadDown();
	UpdateDpadRight();
	UpdateDpadLeft();
	UpdateRB();
	UpdateLB();
	UpdateStart();
	UpdateBack();
}

void XBOXController::UpdateA()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			if (isPressed["A"] == false)
			{
				isPressed["A"] = true;
				if (output)		cLog::inst()->print("A");
			}
		}
		else isPressed["A"] = false;
	}
}
void XBOXController::UpdateB()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			if (isPressed["B"] == false)
			{
				isPressed["B"] = true;
				if (output)		cLog::inst()->print("B");
			}
		}
		else isPressed["B"] = false;
	}
}
void XBOXController::UpdateX()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			if (isPressed["X"] == false)
			{
				isPressed["X"] = false;
				if (output)		cLog::inst()->print("X");
			}
		}
		else isPressed["X"] = false;
	}
}
void XBOXController::UpdateY()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			if (isPressed["Y"] == false)
			{
				isPressed["Y"] = true;
				if (output)		cLog::inst()->print("Y");
			}
		}
		else isPressed["Y"] = false;
	}
}

void XBOXController::UpdateDpadUp()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			if (isPressed["D_UP"] == false)
			{
				isPressed["D_UP"] = true;
				if (output)		cLog::inst()->print("D_UP");
			}
		}
		else isPressed["D_UP"] = false;
	}
}
void XBOXController::UpdateDpadDown()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			if (isPressed["D_DOWN"] == false)
			{
				isPressed["D_DOWN"] = true;
				if (output)		cLog::inst()->print("D_DOWN");
			}
		}
		else isPressed["D_DOWN"] = false;
	}
}
void XBOXController::UpdateDpadRight()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			if (isPressed["D_RIGHT"] == false)
			{
				isPressed["D_RIGHT"] = true;
				if (output)		cLog::inst()->print("D_RIGHT");
			}
		}
		else isPressed["D_RIGHT"] = false;
	}
}
void XBOXController::UpdateDpadLeft()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			if (isPressed["D_LEFT"] == false)
			{
				isPressed["D_LEFT"] = true;
				if (output)		cLog::inst()->print("D_LEFT");
			}
		}
		else isPressed["D_LEFT"] = false;
	}
}

void XBOXController::UpdateRB()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			if (isPressed["RB"] == false)
			{
				isPressed["RB"] = true;
				if (output)		cLog::inst()->print("RB");
			}
		}
		else isPressed["RB"] = false;
	}
}
void XBOXController::UpdateLB()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			if (isPressed["LB"] == false)
			{
				isPressed["LB"] = true;
				if (output)		cLog::inst()->print("LB");
			}
		}
		else isPressed["LB"] = false;
	}
}

void XBOXController::UpdateStart()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
		{
			if (isPressed["START"] == false)
			{
				isPressed["START"] = true;
				if (output)		cLog::inst()->print("START");
			}
		}
		else isPressed["START"] = false;
	}
}
void XBOXController::UpdateBack()
{
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			if (isPressed["SELECT"] == false)
			{
				isPressed["SELECT"] = true;
				if (output)		cLog::inst()->print("SELECT");
			}
		}
		else isPressed["SELECT"] = false;
	}
}

bool XBOXController::isIdle(){
	if (isPressed == isPressed_cleared)	return true;
	return false;
}

