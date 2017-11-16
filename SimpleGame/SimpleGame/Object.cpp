#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(Vec3 p, int team, int type) : pos(p), team(team), type(type)
{
	time = 0;

	int x = rand() % 2;
	int y = rand() % 2;

	if(x == 0)
		dir.x = 1;
	else
		dir.x = -1;

	if (y == 0)
		dir.y = 1;
	else
		dir.y = -1;

	dir.z = 0;
	id = -1;

	if (type == OBJECT_BUILDING)
	{
		life = 500;
		lifeTime = 500;
		speed = { 0, 0, 0 };
		size = 100;
		arrowTime = 0;

		if(team == TEAM_RED)
			color = { 1.0f, 0.0f, 0.0f, 1.0f };
		else if (team == TEAM_BLUE)
			color = { 0.0f, 0.0f, 1.0f, 1.0f };
	}
	else if (type == OBJECT_CHARACTER)
	{
		life = 10;
		lifeTime = 10;
		speed = { 300, 300, 0 };
		size = 10;
		
		if (team == TEAM_RED)
			color = { 1.0f, 0.0f, 0.0f, 1.0f };
		else if (team == TEAM_BLUE)
			color = { 0.0f, 0.0f, 1.0f, 1.0f };

		arrowTime = 0;
		col = false;
	}
	else if (type == OBJECT_BULLET)
	{
		life = 20;
		lifeTime = 20;
		speed = { 600, 600, 0 };
		size = 2;

		if (team == TEAM_RED)
			color = { 1.0f, 0.0f, 0.0f, 1.0f };
		else if (team == TEAM_BLUE)
			color = { 0.0f, 0.0f, 1.0f, 1.0f };
	}
	else if (type == OBJECT_ARROW)
	{
		life = 10;
		lifeTime = 10;
		speed = { 100, 100, 0 };
		size = 2;
	
		if (team == TEAM_RED)
			color = { 0.5f, 0.2f, 0.7f, 1.0f };
		else if(team == TEAM_BLUE)
			color = { 1.0f, 1.0f, 0.0f, 1.0f };
	}
}


Object::~Object()
{
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeinsecond = elapsedTime / 1000.0f;
	
	if (type == OBJECT_CHARACTER || type == OBJECT_BUILDING)
	{
		arrowTime += elapsedTimeinsecond;
	}

	if (type != OBJECT_BUILDING)
		decreaseLifeTime(elapsedTimeinsecond);

	pos.x = pos.x + (speed.x * dir.x * elapsedTimeinsecond);
	if (pos.x > (WIN_X / 2 - 5) - size || pos.x < -(WIN_X / 2 - 5) + size)
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
	if (pos.y > (WIN_Y / 2 - 5) - size || pos.y < -(WIN_Y / 2 - 5) + size)
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

int Object::getTeam()
{
	return team;
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


