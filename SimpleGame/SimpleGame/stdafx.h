#pragma once

#include "targetver.h"
#pragma comment(lib, "winmm.lib") 

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define WIN_X 500
#define WIN_Y 800

#define TIME 0.3f
#define MAX_OBJECTS_COUNT 100
#define MAX_CHARACTER_COUNT 50

#define TEAM_RED  0
#define TEAM_BLUE 1

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

enum ObjectType
{
	OBJECT_BUILDING = 0,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW,
	OBJECT_FIRE,
};


