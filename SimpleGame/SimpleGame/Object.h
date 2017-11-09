#pragma once

class Object
{
private:
	int type;
	Vec3 pos;
	Vec3 speed;
	Vec3 dir;
	Color color;
	float size;
	int life;
	float lifeTime;
	bool col;
	float time;

public:
	Object();
	Object(Vec3 p, int type);
	~Object();

	void Update(float elapsedTime);

	Color getColor();
	Vec3 getPos();
	float getSize();
	int getLife();
	float getLifeTime();
	bool getCol();

	void setSpeed(Vec3 s);
	void setPos(Vec3 newPos);
	void setColor(Color c, float t);
	void setSize(float size);
	void setCol(bool nowCol);
	void decreaseLifeTime(float elapsedTimeSecond);

	void minusLife(int minus);

	void setColorTime(float elapsedTime);
};

