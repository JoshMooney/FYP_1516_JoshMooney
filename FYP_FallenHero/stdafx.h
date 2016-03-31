// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include "cLog.hpp"
#include "vHelper.hpp"
#include "SFML\System\Time.hpp"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <chrono>

static enum _filterCategory {
	PLAYER = 0x0001,			//	0000 0000 0000 0001
	ENEMY = 0x0002,				//	0000 0000 0000 0010
	BULLET = 0x0004,			//	0000 0000 0000 0100
	TERRAIN = 0x0008,			//	0000 0000 0000 1000
	PLATFORM = 0x0010,			//	0000 0000 0001 0000
	GEM = 0x0020,				//	0000 0000 0010 0000
	SENSOR = 0x0040,			//	0000 0000 0100 0000
	//Unused
	/*
	
	PATHING = 0x0080,			//	0000 0000 1000 0000
	SPEED = 0x0100,				//	0000 0001 0000 0000
	SHOOT = 0x0200,				//	0000 0010 0000 0000
	FACTION = 0x0400,			//	0000 0100 0000 0000
	TIMETOLIVE = 0x0800,		//	0000 1000 0000 0000
	USER_DATA = 0x1000,			//	0001 0000 0000 0000
	ANIMATION_SET = 0x2000,		//	0010 0000 0000 0000
	PAIR_INT_DATA = 0x4000,		//	0100 0000 0000 0000
	BOOL_DATA = 0x8000 			//	1000 0000 0000 0000*/
};

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const sf::Time DELTA_TIME = sf::seconds(1.f / 60.f);
#define FTS std::chrono::time_point<std::chrono::system_clock>

// TODO: reference additional headers your program requires here

//Left the Platoforms in the project they are not working a the moment remove the files and project will run.
