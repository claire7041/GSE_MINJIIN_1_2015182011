#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(Rect rect, Color color) : r(rect), c(color)
{
}


Object::~Object()
{
}

Color Object::getColor()
{
	return c;
}

Rect Object::getRect()
{
	return r;
}
