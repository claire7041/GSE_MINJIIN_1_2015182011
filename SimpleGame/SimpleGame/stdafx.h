#pragma once

#include "targetver.h"
#pragma comment(lib, "winmm.lib") 

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define TIME 0.3f
#define MAX_OBJECTS_COUNT 50

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

struct Vec3
{
	float x;
	float y;
	float z;
};
