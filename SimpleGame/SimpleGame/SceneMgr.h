#pragma once
#include "Object.h"
#include "Renderer.h"

class SceneMgr
{
	Object* objArray[MAX_OBJECTS_COUNT];
	Renderer* g_Renderer;

public:
	SceneMgr();
	SceneMgr(int x, int y);
	~SceneMgr();

	void Update(float elapsedTime);
	void Render();
	Object* getObject(int i);
	Renderer* getRenderer();

	void CollisionObj();
};

