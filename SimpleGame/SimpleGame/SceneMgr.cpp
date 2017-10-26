#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
}

SceneMgr::SceneMgr(int x, int y)
{
	g_Renderer = new Renderer(x, y);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		objArray[i] = new Object({ (float)(200 - rand() % 400),  (float)(200 - rand() % 400), 0.0f }, (float)(rand() % 20 + 5), { 1.0f, 1.0f, 1.0f, 1.0f });
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

	delete g_Renderer;
}

void SceneMgr::Update(float elapsedTime)
{
	float elapsedTimeinsecond = elapsedTime / 1000.0f;

	CollisionObj();
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		objArray[i]->Update(elapsedTime);
	}
}

void SceneMgr::Render()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		g_Renderer->DrawSolidRect(objArray[i]->getPos().x, objArray[i]->getPos().y, objArray[i]->getPos().z, objArray[i]->getSize(), objArray[i]->getColor().r, objArray[i]->getColor().g, objArray[i]->getColor().b, objArray[i]->getColor().a);
	}
}

Object * SceneMgr::getObject(int i)
{
	return objArray[i];
}

Renderer * SceneMgr::getRenderer()
{
	return g_Renderer;
}

void SceneMgr::CollisionObj()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		int count = 0;
		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (i != j)
			{
				if (objArray[i]->getPos().x + (objArray[i]->getSize()) / 2.0f >= objArray[j]->getPos().x - (objArray[j]->getSize()) / 2.0f && objArray[i]->getPos().x - (objArray[i]->getSize()) / 2.0f <= objArray[j]->getPos().x + (objArray[j]->getSize() / 2.0f))
				{
					if (objArray[i]->getPos().y + objArray[i]->getSize() / 2.0f >= objArray[j]->getPos().y - (objArray[j]->getSize()) / 2.0f && objArray[i]->getPos().y - (objArray[i]->getSize() / 2.0f) <= objArray[j]->getPos().y + (objArray[j]->getSize() / 2.0f))
					{
						count += 1;
						objArray[i]->setColor({ 0.1f * (float)objArray[i]->getLife(), 0.0f, 0.0f, 1.0f });
						objArray[i]->minusLife();
					}
				}
			}
		}

		if (count == 0)
		{
			objArray[i]->setColor({ 0.1f * objArray[i]->getLife(),  0.1f * objArray[i]->getLife(), 0.1f * objArray[i]->getLife(), 1.0f });
			objArray[i]->setCol(false);
		}
	}
}
