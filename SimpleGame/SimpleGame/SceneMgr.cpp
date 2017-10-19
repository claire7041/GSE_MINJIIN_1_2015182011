#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		objArray[i] = new Object({ (float)(200 - rand() % 400),  (float)(200 - rand() % 400), 0.0f }, (float)(rand() % 20 + 5), {1.0f, 1.0f, 1.0f, 1.0f });
	}
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (objArray[i] != NULL)
		{
			delete objArray[i];
			objArray[i] = NULL;
		}
	}
}

void SceneMgr::Update()
{
	CollisionObj();
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		objArray[i]->Update();
	}
}

Object * SceneMgr::getObject(int i)
{
	return objArray[i];
}

void SceneMgr::CollisionObj()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT - 1; ++i)
	{
		for (int j = i + 1; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (objArray[i]->getPos().x + objArray[i]->getSize() / 2.0f > objArray[j]->getPos().x - objArray[j]->getSize() / 2.0f && objArray[i]->getPos().x - objArray[i]->getSize() / 2.0f < objArray[j]->getPos().x + objArray[j]->getSize() / 2.0f)
			{
				if (objArray[i]->getPos().y + objArray[i]->getSize() / 2.0f > objArray[j]->getPos().y - objArray[j]->getSize() / 2.0f && objArray[i]->getPos().y - objArray[i]->getSize() / 2.0f < objArray[j]->getPos().y + objArray[j]->getSize() / 2.0f)
				{
					objArray[i]->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
					objArray[j]->setColor({ 1.0f, 1.0f, 0.0f, 1.0f });
				}
			}
		}
	}
}
