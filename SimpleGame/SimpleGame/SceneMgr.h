#pragma once
#include "Object.h"

class SceneMgr
{
	Object* objArray[MAX_OBJECTS_COUNT];

public:
	SceneMgr();
	~SceneMgr();

	void Update();
	Object* getObject(int i);

	void CollisionObj();
};

