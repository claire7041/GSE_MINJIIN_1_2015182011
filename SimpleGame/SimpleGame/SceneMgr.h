#pragma once
#include "Object.h"
#include "Renderer.h"

class SceneMgr
{
	Object* objArray[MAX_CHARACTER_COUNT];
	Object* bulletArray[MAX_OBJECTS_COUNT];
	Object* arrowArray[MAX_OBJECTS_COUNT];
	Object* building;
	int charNum;
	int bulletNum;
	int arrowNum;
	Renderer* g_Renderer;
	float bulletTime;
	GLuint buildingTex;

public:
	SceneMgr();
	SceneMgr(int x, int y);
	~SceneMgr();

	void Update(float elapsedTime);
	void Render();

	void AddActorObject(Vec3 pos, int type);
	Object* getObject(int i);
	Renderer* getRenderer();

	void CollisionBuilding();
	void CollisionObjBuilding(Object* colObj[]);
	void CollisionObj(Object* charObj[], Object* colObj[]);
	void CollisionChar();

};

