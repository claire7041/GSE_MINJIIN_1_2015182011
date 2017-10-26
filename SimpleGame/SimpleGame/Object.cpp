#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(Vec3 p, float s, Color c) : pos(p), size(s), color(c)
{
	speed = { (float)(rand() % 10 + 1) / 1000.0f, (float)(rand() % 10 + 1) / 1000.0f, 0.0f };
	life = 10;
}


Object::~Object()
{
}

void Object::Update(float elapsedTime)
{
	pos.x = pos.x + (speed.x * elapsedTime);
	if (pos.x > 250 - size || pos.x < -250 + size)
		speed.x *= -1;
	pos.y = pos.y + (speed.y * elapsedTime);
	if (pos.y > 250 - size || pos.y < -250 + size)
		speed.y *= -1;
	pos.z = pos.z + (speed.z * elapsedTime);
}

Color Object::getColor()
{
	return color;
}

float Object::getSize()
{
	return size;
}

int Object::getLife()
{
	return life;
}

Vec3 Object::getPos()
{
	return pos;
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
	color = c;
}

void Object::setSize(float size)
{
}

void Object::setCol(bool nowCol)
{
	col = nowCol;
}

void Object::minusLife()
{
	if (life > 0)
	{
		if (!col)
		{
			life -= 1;
			col = true;
		}
	}
}


