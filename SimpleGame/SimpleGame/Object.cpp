#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(Vec3 p, int type) : pos(p), type(type)
{
	time = 0;

	dir.x = (float)(1 - rand() % 3);
	dir.y = (float)(1 - rand() % 3);
	if (dir.x == 0 && dir.y == 0)
	{
		dir.x = 1;
		dir.y = -1;
	}
	dir.z = 0;
	id = -1;

	if (type == OBJECT_BUILDING)
	{
		life = 500;
		lifeTime = 500;
		speed = { 0, 0, 0 };
		color = { 1.0f, 1.0f, 0.0f, 1.0f };
		size = 50;
	}
	else if (type == OBJECT_CHARACTER)
	{
		life = 10;
		lifeTime = 10;
		speed = { 300, 300, 0 };
		color = { 1.0f, 1.0f, 1.0f, 1.0f };
		arrowTime = 0;
		size = 10;
		col = false;
	}
	else if (type == OBJECT_BULLET)
	{
		life = 20;
		lifeTime = 20;
		speed = { 600, 600, 0 };
		color = { 1.0f, 0.0f, 0.0f, 1.0f };
		size = 5;
	}
	else if (type == OBJECT_ARROW)
	{
		life = 10;
		lifeTime = 10;
		speed = { 100, 100, 0 };
		color = { 0.0f, 1.0f, 0.0f, 1.0f };
		size = 5;
	}
}


Object::~Object()
{
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeinsecond = elapsedTime / 1000.0f;
	
	if (type == OBJECT_CHARACTER)
	{
		arrowTime += elapsedTimeinsecond;
	}

	if (type != OBJECT_BUILDING)
		decreaseLifeTime(elapsedTimeinsecond);

	pos.x = pos.x + (speed.x * dir.x * elapsedTimeinsecond);
	if (pos.x > 240 - size || pos.x < -240 + size)
	{
		if (type == OBJECT_CHARACTER)
		{
			dir.x *= -1;
			pos.x += (dir.x * 2.5f);
		}
		else
		{
			lifeTime = 1.0f;
		}
	}
	pos.y = pos.y + (speed.y * dir.y * elapsedTimeinsecond);
	if (pos.y > 240 - size || pos.y < -240 + size)
	{
		if (type == OBJECT_CHARACTER)
		{
			dir.y *= -1;
			pos.y += (dir.y * 2.5f);
		}
		else
		{
			lifeTime = 1.0f;
		}
	}
	pos.z = pos.z + (speed.z * elapsedTimeinsecond);

	if (time > 0)
	{
		setColorTime(elapsedTimeinsecond);
		if (time <= 0)
		{
			setColor({ 1.0f, 1.0f, 0.0f, 1.0f }, 0.0f);
		}
	}
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

float Object::getLifeTime()
{
	return lifeTime;
}

bool Object::getCol()
{
	return col;
}

float Object::getArrowTime()
{
	return arrowTime;
}

int Object::getId()
{
	return id;
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

void Object::setColor(Color c, float t)
{
	time = t;
	color = c;
}

void Object::setSize(float size)
{
}

void Object::setCol(bool nowCol)
{
	col = nowCol;
}

void Object::setId(int num)
{
	id = num;
}

void Object::setLifeTime()
{
	lifeTime = 1.0f;
}

void Object::initArrowTime()
{
	arrowTime = 0;
}

void Object::decreaseLifeTime(float elapsedTimeSecond)
{
	lifeTime -= elapsedTimeSecond;
}

void Object::minusLife(int minus)
{
	if (life - minus > 0)
	{
		life -= minus;
	}
	else
	{
		life = 0;
	}
}

void Object::setColorTime(float elapsedTimeSecond)
{
	time -= elapsedTimeSecond;
}


