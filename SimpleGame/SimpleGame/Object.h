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
	float level;
	Color color;
	int currentAnimX;
	int totalAnimX;
	int currentAnimY;
	int totalAnimY;

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
	Vec3 getDir();
	bool getCol();
	float getSize();
	float getLifeTime();
	float getArrowTime();
	float getLevel();
	int getLife();
	int getTeam();
	int getId();
	int getCurrentAnimX();
	int getCurrentAnimY();
	int getTotalAnimX();
	int getTotalAnimY();
	float getTime();


	void setSpeed(Vec3 s);
	void setPos(Vec3 newPos);
	void setColor(Color c, float t);
	void setSize(float size);
	void setCol(bool nowCol);
	void setId(int num);
	void setTime(float t);
	void setLifeTime();

	void initArrowTime();
	void decreaseLifeTime(float elapsedTimeSecond);

	void minusLife(int minus);

	void setColorTime(float elapsedTime);
};

