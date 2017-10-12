#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(Vec3 p, float s, Color c) : pos(p), size(s), color(c)
{
	speed = { 0.25, 0.25, 0 };
}


Object::~Object()
{
}

void Object::Update()
{
	pos.x = pos.x + (speed.x * TIME);
	if (pos.x > 200 || pos.x < -200)
		speed.x *= -1;
	pos.y = pos.y + (speed.y * TIME);
	if (pos.y > 200 || pos.y < -200)
		speed.y *= -1;
	pos.z = pos.z + (speed.z * TIME);
}

Color Object::getColor()
{
	return color;
}

float Object::getSize()
{
	return size;
}

void Object::setSpeed(Vec3 s)
{
	speed = s;
}

Vec3 Object::getPos()
{
	return pos;
}
