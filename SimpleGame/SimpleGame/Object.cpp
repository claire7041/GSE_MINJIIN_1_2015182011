#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(Vec3 p, float s, Color c) : pos(p), size(s), color(c)
{
	speed = { 0.1f, 0.1f, 0.0f };
}


Object::~Object()
{
}

void Object::Update()
{
	pos.x = pos.x + (speed.x * TIME);
	if (pos.x > 250 - size || pos.x < -250 + size)
		speed.x *= -1;
	pos.y = pos.y + (speed.y * TIME);
	if (pos.y > 250 - size || pos.y < -250 + size)
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

void Object::setPos(Vec3 newPos)
{
	pos = newPos;
}

void Object::setColor(Color c)
{
}

void Object::setSize(float size)
{
}

Vec3 Object::getPos()
{
	return pos;
}
