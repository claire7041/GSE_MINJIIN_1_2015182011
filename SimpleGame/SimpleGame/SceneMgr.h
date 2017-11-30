#pragma once
#include "Object.h"
#include "Renderer.h"

class SceneMgr
{
	Object* objArray[MAX_CHARACTER_COUNT];
	Object* bulletArray[MAX_OBJECTS_COUNT];
	Object* arrowArray[MAX_OBJECTS_COUNT];
	Object* building[2][3];
	
	int charNum;
	int bulletNum;
	int arrowNum;
	float spawnRedTime;
	float spawnBlueTime;

	GLuint buildingTex[2];
	GLuint objTex;
	GLuint backgroundTex;
	GLuint particleBulletTex;

	Renderer* g_Renderer;

public:
	SceneMgr();
	SceneMgr(int x, int y);
	~SceneMgr();

	void Update(float elapsedTime);
	void Render();

	void AddActorObject(Vec3 pos, int team, int type);
	Object* getObject(int i);
	Renderer* getRenderer();

	void CollisionBuilding(Object* building);
	void CollisionObjBuilding(Object* building, Object* colObj[]);
	void CollisionObj(Object* charObj[], Object* colObj[]);
	void CollisionChar();

};

