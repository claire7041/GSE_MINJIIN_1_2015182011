#pragma once

class Object
{
private:
	Vec3 pos;
	Vec3 speed;
	Color color;
	float size;

public:
	Object();
	Object(Vec3 p, float s, Color c);
	~Object();

	void Update();

	Color getColor();
	Vec3 getPos();
	float getSize();

	void setSpeed(Vec3 s);
	void setPos(Vec3 newPos);
	void setColor(Color c);
	void setSize(float size);
};

