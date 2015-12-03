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

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const sf::Time DELTA_TIME = sf::seconds(1.f / 60.f);
#define FTS std::chrono::time_point<std::chrono::system_clock>

// TODO: reference additional headers your program requires here

//Left the Platoforms in the project they are not working a the moment remove the files and project will run.
