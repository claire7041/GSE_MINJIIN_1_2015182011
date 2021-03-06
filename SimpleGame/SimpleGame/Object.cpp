#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(Vec3 p, int team, int type) : pos(p), team(team), type(type)
{
	time = 0;
	currentAnimX = 0;
	currentAnimY = 0;
	consistDamegeTime = 0.0f;

	int x = rand() % 2;
	int y = rand() % 2;

	if(x == 0 && y == 0)
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
		level = 0.1f;

		color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}
	else if (type == OBJECT_CHARACTER)
	{
		life = 10;
		lifeTime = 10;
		speed = { 100, 100, 0 };
		size = 35;
		level = 0.2f;

		if (team == TEAM_RED)
		{
			color = { 1.0f, 1.0f, 1.0f, 1.0f };
			dir.y = -1;
		}
		else if (team == TEAM_BLUE)
		{
			color = { 1.0f, 1.0f, 1.0f, 1.0f };
			dir.y = 1;
		}

		totalAnimX = 5;
		totalAnimY = 1;

		arrowTime = 0;
		col = false;
	}
	else if (type == OBJECT_BULLET)
	{
		life = 20;
		lifeTime = 20;
		speed = { 100, 100, 0 };
		size = 5;
		level = 0.3f;
		dir.x = 0;

		if (team == TEAM_RED)
		{
			color = { 1.0f, 0.0f, 0.0f, 1.0f };
			dir.y = -1;
		}
		else if (team == TEAM_BLUE)
		{
			color = { 0.0f, 0.0f, 1.0f, 1.0f };
			dir.y = 1;
		}
	}
	else if (type == OBJECT_ARROW)
	{
		life = 5;
		lifeTime = 10;
		speed = { 80, 80, 0 };
		size = 3;
		level = 0.3f;

		if (team == TEAM_RED)
		{
			color = { 0.5f, 0.2f, 0.7f, 1.0f };
			dir.y = -1;
		}
		else if (team == TEAM_BLUE)
		{
			color = { 1.0f, 1.0f, 0.0f, 1.0f };
			dir.y = 1;
		}
	}
	else if (type == OBJECT_FIRE)
	{
		life = 100;
		lifeTime = 5;
		speed = { 0, 0, 0 };
		size = 300;
		level = 0.35f;

		color = { 1.0f, 0.0f, 0.0f, 1.0f };

		totalAnimX = 8;
		totalAnimY = 4;
	}
}


Object::~Object()
{
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeinsecond = elapsedTime / 1000.0f;
	if (type == OBJECT_CHARACTER || type == OBJECT_BULLET || type == OBJECT_FIRE)
		time += elapsedTimeinsecond;

	if (type == OBJECT_CHARACTER || type == OBJECT_BUILDING)
		arrowTime += elapsedTimeinsecond;

	if (type != OBJECT_BUILDING)
		decreaseLifeTime(elapsedTimeinsecond);

	pos.x = pos.x + (speed.x * dir.x * elapsedTimeinsecond);
	if (pos.x > (WIN_X / 2)|| pos.x < -(WIN_X / 2))
	{
		if (type == OBJECT_CHARACTER)
		{
			dir.x *= -1;
			pos.x += (dir.x * 5.0f);
		}
		else
		{
			lifeTime = 1.0f;
		}
	}
	pos.y = pos.y + (speed.y * dir.y * elapsedTimeinsecond);
	if (pos.y > (WIN_Y / 2) || pos.y < -(WIN_Y / 2))
	{
		if (type == OBJECT_CHARACTER)
		{
			dir.y *= -1;
			pos.y += (dir.y * 5.0f);
		}
		else
		{
			lifeTime = 1.0f;
		}
	}
	pos.z = pos.z + (speed.z * elapsedTimeinsecond);

	if (time > 0 && type == OBJECT_BUILDING)
	{
		time -= elapsedTimeinsecond;
		if (time > 0.2f)
		{
			size += 1.0f;
		}
		else if (time <= 0.2f)
		{
			size -= 1.0f;
		}
	}
	else if (time <= 0 && type == OBJECT_BUILDING)
	{
		time = 0;
		size = 100;
	}

	if (time > 0.2f && type == OBJECT_CHARACTER )
	{
		currentAnimX = (currentAnimX + 1) % totalAnimX;
		currentAnimY = (currentAnimY + 1) % totalAnimY;
		time = 0;
	}

	if (time > 0.5f && type == OBJECT_FIRE)
	{
		currentAnimX = (currentAnimX + 1) % totalAnimX;
		currentAnimY = (currentAnimY + 1) % totalAnimY;
		time = 0;
	}

	if (type == OBJECT_CHARACTER)
	{
		if (consistDamegeTime > 0.0f)
		{
			life -= 1;
			consistDamegeTime -= 1;
		}
		else
		{
			if (color.b != 1.0f)
				color = { 1.0f, 1.0f, 1.0f, 1.0f };
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

float Object::getLevel()
{
	return level;
}

int Object::getTeam()
{
	return team;
}

int Object::getId()
{
	return id;
}

int Object::getCurrentAnimX()
{
	return currentAnimX;
}

int Object::getCurrentAnimY()
{
	return currentAnimY;
}

int Object::getTotalAnimX()
{
	return totalAnimX;
}

int Object::getTotalAnimY()
{
	return totalAnimY;
}

Vec3 Object::getPos()
{
	return pos;
}

Vec3 Object::getDir()
{
	return dir;
}

float Object::getTime()
{
	return time;
}

float Object::getType()
{
	return type;
}

float Object::getDamegeTime()
{
	return consistDamegeTime;
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
	color = c;
}

void Object::setTime(float t)
{
	time = t;
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

void Object::setDamegeTime(float t)
{
	consistDamegeTime = t;
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


