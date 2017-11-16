#pragma once

class Object
{
private:
	int team;
	int type;
	int id;

	Vec3 pos;
	Vec3 speed;
	Vec3 dir;
	float size;
	Color color;
	
	int life;
	float lifeTime;
	
	bool col;
	
	float time;
	float arrowTime;

public:
	Object();
	Object(Vec3 p, int team, int type);
	~Object();

	void Update(float elapsedTime);

	Color getColor();
	Vec3 getPos();
	float getSize();
	int getLife();
	float getLifeTime();
	bool getCol();
	float getArrowTime();
	int getTeam();
	int getId();

	void setSpeed(Vec3 s);
	void setPos(Vec3 newPos);
	void setColor(Color c, float t);
	void setSize(float size);
	void setCol(bool nowCol);
	void setId(int num);
	void setLifeTime();

	void initArrowTime();
	void decreaseLifeTime(float elapsedTimeSecond);

	void minusLife(int minus);

	void setColorTime(float elapsedTime);
};

