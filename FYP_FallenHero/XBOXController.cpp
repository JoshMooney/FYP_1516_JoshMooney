#include "stdafx.h"
#include "XBOXController.hpp"

XBOXController::XBOXController() {
	output = false;
	connected = false;
	memset(&state, 0, sizeof(XINPUT_STATE));
	memset(&motor, 0, sizeof(XINPUT_VIBRATION));

	dz_LX = 0.15f;
	dz_LY = 0.15f;
		  
	dz_RX = 0.15f;
	dz_RY = 0.15f;
	
	threshold_LT = 0.4f;
	threshold_RT = 0.4f;

	left_X = 0;
	left_Y = 0;
	right_X = 0; 
	right_Y = 0;
	left_trigger = 0;
	right_trigger = 0;

	isPressed["A"] = false;
	isPressed["B"] = false;
	isPressed["X"] = false;
	isPressed["Y"] = false;

	isPressed["LB"] = false;
	isPressed["RB"] = false;

	isPressed["LT"] = false;
	isPressed["RT"] = false;

	isPressed["START"] = false;
	isPressed["SELECT"] = false;

	isPressed["D_UP"] = false;
	isPressed["D_DOWN"] = false;
	isPressed["D_LEFT"] = false;
	isPressed["D_RIGHT"] = false;

	isPressed["AL_UP"] = false;
	isPressed["AL_DOWN"] = false;
	isPressed["AL_LEFT"] = false;
	isPressed["AL_RIGHT"] = false;

	isPressed["AR_UP"] = false;
	isPressed["AR_DOWN"] = false;
	isPressed["AR_LEFT"] = false;
	isPressed["AR_RIGHT"] = false;

	isPressed_cleared = isPressed;
}
XBOXController::XBOXController(bool is_output)	{
	output = is_output;
	connected = false;
	memset(&state, 0, sizeof(XINPUT_STATE));
	memset(&motor, 0, sizeof(XINPUT_VIBRATION));

	dz_LX = 0.15f;
	dz_LY = 0.15f;

	dz_RX = 0.15f;
	dz_RY = 0.15f;

	threshold_LT = 0.4f;
	threshold_RT = 0.4f;

	left_X = 0;
	left_Y = 0;
	right_X = 0;
	right_Y = 0;
	left_trigger = 0;
	right_trigger = 0;

	isPressed["A"] = false;
	isPressed["B"] = false;
	isPressed["X"] = false;
	isPressed["Y"] = false;

	isPressed["LB"] = false;
	isPressed["RB"] = false;

	isPressed["LT"] = false;
	isPressed["RT"] = false;

	isPressed["START"] = false;
	isPressed["SELECT"] = false;

	isPressed["D_UP"] = false;
	isPressed["D_DOWN"] = false;
	isPressed["D_LEFT"] = false;
	isPressed["D_RIGHT"] = false;

	isPressed["AL_UP"] = false;
	isPressed["AL_DOWN"] = false;
	isPressed["AL_LEFT"] = false;
	isPressed["AL_RIGHT"] = false;

	isPressed["AR_UP"] = false;
	isPressed["AR_DOWN"] = false;
	isPressed["AR_LEFT"] = false;
	isPressed["AR_RIGHT"] = false;
	isPressed_cleared = isPressed;
}
XBOXController::~XBOXController()
{

}

bool XBOXController::isConnected() {
	if (output)		cLog::inst()->print(3, "XBOXController", "XBOXController is Checking for Xbox controller.");
	prev_state = state;
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		if (output)		cLog::inst()->print(3, "XBOXController", "Xbox controller connected successfully.");
		connected = true;
		return true;
	}
	else
	{
		if (output)		cLog::inst()->print(3, "XBOXController", "No Xbox controller detected.");
		connected = false;
		return false;
	}
}

void XBOXController::Rumble(int l_rm, int r_rm) {
	if (connected) {
		motor.wLeftMotorSpeed = l_rm;
		motor.wRightMotorSpeed = r_rm;
		XInputSetState(0, &motor);
	}
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
	UpdateAnalogSticks();
	UpdateTriggers();
}

void XBOXController::UpdateA()
{
	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_A) && connected)	{
		if (isPressed["A"] == false)	{
			isPressed["A"] = true;
			if (output)		cLog::inst()->print("A");
		}
	}
	else isPressed["A"] = false;
}
void XBOXController::UpdateB()
{
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && connected)
	{
		if (isPressed["B"] == false)
		{
			isPressed["B"] = true;
			if (output)		cLog::inst()->print("B");
		}
	}
	else isPressed["B"] = false;
}
void XBOXController::UpdateX() {
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X && connected)
	{
		if (isPressed["X"] == false)
		{
			isPressed["X"] = false;
			if (output)		cLog::inst()->print("X");
		}
	}
	else isPressed["X"] = false;
}
void XBOXController::UpdateY() {	
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y && connected)
	{
		if (isPressed["Y"] == false)
		{
			isPressed["Y"] = true;
			if (output)		cLog::inst()->print("Y");
		}
	}
	else isPressed["Y"] = false;
}

void XBOXController::UpdateDpadUp()
{
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && connected)
	{
		if (isPressed["D_UP"] == false)
		{
			isPressed["D_UP"] = true;
			if (output)		cLog::inst()->print("D_UP");
		}
	}
	else isPressed["D_UP"] = false;
}
void XBOXController::UpdateDpadDown()
{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && connected)
		{
			if (isPressed["D_DOWN"] == false)
			{
				isPressed["D_DOWN"] = true;
				if (output)		cLog::inst()->print("D_DOWN");
			}
		}
		else isPressed["D_DOWN"] = false;
	
}
void XBOXController::UpdateDpadRight()
{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT  && connected)
		{
			if (isPressed["D_RIGHT"] == false)
			{
				isPressed["D_RIGHT"] = true;
				if (output)		cLog::inst()->print("D_RIGHT");
			}
		}
		else isPressed["D_RIGHT"] = false;
}
void XBOXController::UpdateDpadLeft()
{

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && connected)
		{
			if (isPressed["D_LEFT"] == false)
			{
				isPressed["D_LEFT"] = true;
				if (output)		cLog::inst()->print("D_LEFT");
			}
		}
		else isPressed["D_LEFT"] = false;
	
}

/*NEEDS: Checks to ensure either NSEW direction each analog stick is pointing in*/
void XBOXController::UpdateLeftAnalogUp() {
	if (left_Y > 0 && left_X < .4 && left_X > -.4)
		isPressed["AL_UP"] = true;
	else
		isPressed["AL_UP"] = false;
}
void XBOXController::UpdateLeftAnalogDown() {
	if (left_Y < 0 && left_X < .4 && left_X > -.4)
		isPressed["AL_DOWN"] = true;
	else
		isPressed["AL_DOWN"] = false;
}
void XBOXController::UpdateLeftAnalogRight() {
	if (left_X > 0 && left_Y < .4 && left_Y > -.4)
		isPressed["AL_RIGHT"] = true;
	else
		isPressed["AL_RIGHT"] = false;
}
void XBOXController::UpdateLeftAnalogLeft() {
	if (left_X < 0 && left_Y < .4 && left_Y > -.4)
		isPressed["AL_LEFT"] = true;
	else
		isPressed["AL_LEFT"] = false;
}

void XBOXController::UpdateRightAnalogUp() {
	if (left_Y > 0 && left_X < .4 && left_X > -.4)
		isPressed["AL_UP"] = true;
}
void XBOXController::UpdateRightAnalogDown() {
	if (left_Y < 0)
		isPressed["AL_DOWN"] = true;
}
void XBOXController::UpdateRightAnalogRight() {
	if (left_X > 0)
		isPressed["AL_RIGHT"] = true;
}
void XBOXController::UpdateRightAnalogLeft() {
	if (left_X < 0)
		isPressed["AL_LEFT"] = true;
}

void XBOXController::UpdateAnalogSticks() {
	if (connected)
	{
		//Left Stick Update
		//Get normalised stick position
		float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / STICK_MAX);
		float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / STICK_MAX);

		//Get position betweeen deadzone and edge
		left_X = (abs(normLX) < dz_LX ? 0 : (abs(normLX) - dz_LX) * (normLX / abs(normLX)));
		left_Y = (abs(normLY) < dz_LY ? 0 : (abs(normLY) - dz_LY) * (normLY / abs(normLY)));

		//Scale position to between -1 and 1
		if (dz_LX > 0) left_X *= 1 / (DEADZONE_MAX - dz_LX);
		if (dz_LY > 0) left_Y *= 1 / (DEADZONE_MAX - dz_LY);

		//Right Stick Update
		float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / STICK_MAX);
		float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / STICK_MAX);

		right_X = (abs(normRX) < dz_RX ? 0 : (abs(normRX) - dz_RX) * (normRX / abs(normRX)));
		right_Y = (abs(normRY) < dz_RY ? 0 : (abs(normRY) - dz_RY) * (normRY / abs(normRY)));

		if (dz_RX > 0) right_X *= 1 / (DEADZONE_MAX - dz_RX);
		if (dz_RY > 0) right_Y *= 1 / (DEADZONE_MAX - dz_RY);
	}
	if (output) {
		cLog::inst()->debug("RX", right_X);
		cLog::inst()->debug("RY", right_Y);
		cLog::inst()->debug("LX", left_X);
		cLog::inst()->debug("LY", left_Y);
		cLog::inst()->newline();
	}

	UpdateLeftAnalogUp();
	UpdateLeftAnalogDown();
	UpdateLeftAnalogRight();
	UpdateLeftAnalogLeft();

	if (right_Y > 0)	isPressed["AR_UP"] = true;
	if (right_Y < 0)	isPressed["AR_DOWN"] = true;
	if (right_X < 0)	isPressed["AR_LEFT"] = true;
	if (right_X > 0)	isPressed["AR_RIGHT"] = true;
}
void XBOXController::UpdateTriggers() {
	if (connected)	{
		//Trigger update
		left_trigger = (float)state.Gamepad.bLeftTrigger / TRIGGER_MAX;
		right_trigger = (float)state.Gamepad.bRightTrigger / TRIGGER_MAX;
	}

	if (left_trigger > threshold_LT)		isPressed["LT"] = true;
	if (right_trigger > threshold_RT)		isPressed["RT"] = true;
}

void XBOXController::UpdateRB()
{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && connected)
		{
			if (isPressed["RB"] == false)
			{
				isPressed["RB"] = true;
				if (output)		cLog::inst()->print("RB");
			}
		}
		else isPressed["RB"] = false;
}
void XBOXController::UpdateLB()
{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && connected)
		{
			if (isPressed["LB"] == false)
			{
				isPressed["LB"] = true;
				if (output)		cLog::inst()->print("LB");
			}
		}
		else isPressed["LB"] = false;
}

void XBOXController::UpdateStart()
{
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && connected)
		{
			if (isPressed["START"] == false)
			{
				isPressed["START"] = true;
				if (output)		cLog::inst()->print("START");
			}
		}
		else isPressed["START"] = false;
}
void XBOXController::UpdateBack()
{

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK && connected)
		{
			if (isPressed["SELECT"] == false)
			{
				isPressed["SELECT"] = true;
				if (output)		cLog::inst()->print("SELECT");
			}
		}
		else isPressed["SELECT"] = false;
}

bool XBOXController::isIdle(){
	if (isPressed == isPressed_cleared)	return true;
	return false;
}

float XBOXController::getRT() { return right_trigger; }
float XBOXController::getLT() { return left_trigger; }
std::pair<float, float> XBOXController::getRightAnalog() {
	return std::pair<float, float>(right_X, right_Y);
}
std::pair<float, float> XBOXController::getLeftAnalog(){
	return std::pair<float, float>(left_X, left_Y);
}

