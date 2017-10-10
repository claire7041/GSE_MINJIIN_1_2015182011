#pragma once

class Object
{
private:
	Rect r;
	Color c;

public:
	Object();
	Object(Rect rect, Color color);
	~Object();

	Color getColor();
	Rect getRect();
};

