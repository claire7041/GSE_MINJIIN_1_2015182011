#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
}

SceneMgr::SceneMgr(int x, int y)
{
	bulletTime = 0.5f;
	g_Renderer = new Renderer(x, y);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	buildingTex = g_Renderer->CreatePngTexture("./building.png");
	charNum = 0;
	bulletNum = 0;
	arrowNum = 0;
	building = new Object({ 0.0f, 0.0f, 0.0f }, OBJECT_BUILDING);
}

SceneMgr::~SceneMgr()
{
	for (int i = 0; i < charNum; ++i)
	{
		if (objArray[i] != NULL)
		{
			delete[] objArray[i];
			objArray[i] = NULL;
		}
	}

	for (int i = 0; i < bulletNum; ++i)
	{
		if (bulletArray[i] != NULL)
		{
			delete[] bulletArray[i];
			bulletArray[i] = NULL;
		}
	}

	for (int i = 0; i < arrowNum; ++i)
	{
		if (arrowArray[i] != NULL)
		{
			delete[] arrowArray[i];
			arrowArray[i] = NULL;
		}
	}

	if(building != NULL)
		delete building;
	delete[] objArray;
	delete[] bulletArray;
	delete[] arrowArray;
	delete g_Renderer;
}

void SceneMgr::Update(float elapsedTime)
{
	float elapsedTimeinsecond = elapsedTime / 1000.0f;
	
	if (building != NULL)
	{
		bulletTime -= elapsedTimeinsecond;
		if (bulletTime <= 0.0f)
		{
			AddActorObject({ 0.0f, 0.0f, 0.0f }, OBJECT_BULLET);
		}

		CollisionBuilding();
		CollisionObjBuilding(arrowArray);
	}
	CollisionObj(objArray, bulletArray);
	CollisionObj(objArray, arrowArray);


	if (building != NULL)
	{
		building->Update(elapsedTime);
	}

	for (int i = 0; i < charNum; ++i)
	{
		if (objArray[i] != NULL) 
		{
			objArray[i]->Update(elapsedTime);
			if (objArray[i]->getArrowTime() >= 0.5f)
			{
				AddActorObject(objArray[i]->getPos(), OBJECT_ARROW);
				arrowArray[arrowNum - 1]->setId(objArray[i]->getId());
				objArray[i]->initArrowTime();
			}

			if (objArray[i]->getLifeTime() <= 0.0f)
			{
				for (int j = 0; j < arrowNum; ++j)
				{
					if (arrowArray[j] != NULL)
					{
						if (objArray[i]->getId() == arrowArray[j]->getId())
						{
							delete arrowArray[j];
							arrowArray[j] = NULL;
						}
					}
				}
				delete objArray[i];
				objArray[i] = NULL;
			}
		}
	}
	for (int i = 0; i < bulletNum; ++i)
	{
		if (bulletArray[i] != NULL)
		{
			bulletArray[i]->Update(elapsedTime);
			if (bulletArray[i]->getLifeTime() <= 0.0f)
			{
				delete bulletArray[i];
				bulletArray[i] = NULL;
			}
		}
	}
	for (int i = 0; i < arrowNum; ++i)
	{
		if (arrowArray[i] != NULL)
		{
			arrowArray[i]->Update(elapsedTime);
			if (arrowArray[i]->getLifeTime() <= 0.0f)
			{
				delete arrowArray[i];
				arrowArray[i] = NULL;
			}
		}
	}
}

void SceneMgr::Render()
{
	if(building != NULL) 
		g_Renderer->DrawTexturedRect(building->getPos().x, building->getPos().y, building->getPos().z, building->getSize(), building->getColor().r, building->getColor().g, building->getColor().b, building->getColor().a, buildingTex);

	for (int i = 0; i < charNum; ++i)
	{
		if(objArray[i] != NULL)
			g_Renderer->DrawSolidRect(objArray[i]->getPos().x, objArray[i]->getPos().y, objArray[i]->getPos().z, objArray[i]->getSize(), objArray[i]->getColor().r, objArray[i]->getColor().g, objArray[i]->getColor().b, objArray[i]->getColor().a);
	}

	for (int i = 0; i < bulletNum; ++i)
	{
		if (bulletArray[i] != NULL)
			g_Renderer->DrawSolidRect(bulletArray[i]->getPos().x, bulletArray[i]->getPos().y, bulletArray[i]->getPos().z, bulletArray[i]->getSize(), bulletArray[i]->getColor().r, bulletArray[i]->getColor().g, bulletArray[i]->getColor().b, bulletArray[i]->getColor().a);
	}

	for (int i = 0; i < arrowNum; ++i)
	{
		if (arrowArray[i] != NULL)
			g_Renderer->DrawSolidRect(arrowArray[i]->getPos().x, arrowArray[i]->getPos().y, arrowArray[i]->getPos().z, arrowArray[i]->getSize(), arrowArray[i]->getColor().r, arrowArray[i]->getColor().g, arrowArray[i]->getColor().b, arrowArray[i]->getColor().a);
	}
}

void SceneMgr::AddActorObject(Vec3 pos, int type)
{
	if (type == OBJECT_BUILDING)
	{
	}
	else if (type == OBJECT_CHARACTER)
	{
		if (charNum < MAX_CHARACTER_COUNT)
		{
			objArray[charNum] = new Object(pos, OBJECT_CHARACTER);
			objArray[charNum]->setId(charNum);
			charNum++;
		}
		else
		{
			int i = 0;
			while (i < MAX_CHARACTER_COUNT)
			{
				if (objArray[i] == NULL)
				{
					objArray[i] = new Object(pos, OBJECT_CHARACTER);
					objArray[i]->setId(i);
					break;
				}
				i++;
			}
		}
	}
	else if (type == OBJECT_BULLET)
	{
		if (bulletNum == MAX_OBJECTS_COUNT)
		{
			bulletNum = 0;
		}

		bulletArray[bulletNum] = new Object(pos, OBJECT_BULLET);
		bulletNum++;
		bulletTime = 0.5f;
	}
	else if(type == OBJECT_ARROW)
	{
		if (arrowNum == MAX_OBJECTS_COUNT)
		{
			arrowNum = 0;
		}

		arrowArray[arrowNum] = new Object(pos, OBJECT_ARROW);

		arrowNum++;
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

void SceneMgr::CollisionBuilding()
{
	for (int i = 0; i < charNum; ++i)
	{
		if (objArray[i] != NULL && building != NULL)
		{
			if (objArray[i]->getPos().x + (objArray[i]->getSize()) / 2.0f >= building->getPos().x - (building->getSize()) / 2.0f && objArray[i]->getPos().x - (objArray[i]->getSize()) / 2.0f <= building->getPos().x + (building->getSize() / 2.0f))
			{
				if (objArray[i]->getPos().y + objArray[i]->getSize() / 2.0f >= building->getPos().y - (building->getSize()) / 2.0f && objArray[i]->getPos().y - (objArray[i]->getSize() / 2.0f) <= building->getPos().y + (building->getSize() / 2.0f))
				{
					if (!objArray[i]->getCol())
					{
						objArray[i]->setCol(true);
						building->setColor({ 1.0f, 0.0f, 0.0f, 1.0f }, 0.1f);
						building->minusLife(objArray[i]->getLife());
						objArray[i]->minusLife(20);
						//printf("캐릭터%d수명: %d, 건물수명: %d\n", i, objArray[i]->getLife(), building->getLife());
					}
				}
				else
				{
					if (objArray[i]->getCol())
					{
						objArray[i]->setCol(false);
					}
				}
			}
			else
			{
				if (objArray[i]->getCol())
				{
					objArray[i]->setCol(false);
				}
			}
		}
	}

	if (building != NULL)
	{
		if (building->getLife() < 1)
		{

			delete building;
			building = NULL;
		}
	}

	
	for (int i = 0; i < charNum; ++i)
	{
		if (objArray[i] != NULL)
		{
			if (objArray[i]->getLife() < 1)
			{
				for (int j = 0; j < arrowNum; ++j)
				{
					if (arrowArray[j] != NULL)
					{
						if (objArray[i]->getId() == arrowArray[j]->getId())
						{
							delete arrowArray[j];
							arrowArray[j] = NULL;
						}
					}
				}
				delete objArray[i];
				objArray[i] = NULL;
			}
		}
	}


}

void SceneMgr::CollisionObjBuilding(Object * colObj[])
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (colObj[i] != NULL && building != NULL)
		{
			if (colObj[i]->getPos().x + (colObj[i]->getSize()) / 2.0f >= building->getPos().x - (building->getSize()) / 2.0f && colObj[i]->getPos().x - (colObj[i]->getSize()) / 2.0f <= building->getPos().x + (building->getSize() / 2.0f))
			{
				if (colObj[i]->getPos().y + colObj[i]->getSize() / 2.0f >= building->getPos().y - (building->getSize()) / 2.0f && colObj[i]->getPos().y - (colObj[i]->getSize() / 2.0f) <= building->getPos().y + (building->getSize() / 2.0f))
				{
						building->setColor({ 1.0f, 0.0f, 0.0f, 1.0f }, 0.1f);
						building->minusLife(colObj[i]->getLife());

						delete colObj[i];
						colObj[i] = NULL;
				}
			}
		}
	}

	if (building != NULL)
	{
		if (building->getLife() < 1)
		{

			delete building;
			building = NULL;
		}
	}
}

void SceneMgr::CollisionObj(Object* charObj[], Object* colObj[])
{
	for (int i = 0; i < MAX_CHARACTER_COUNT; ++i)
	{
		if (charObj[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
			{
				if (colObj[j] != NULL && charObj[i]->getId() != colObj[j]->getId())
				{
					if (charObj[i]->getPos().x + (charObj[i]->getSize()) / 2.0f >= colObj[j]->getPos().x - (colObj[j]->getSize()) / 2.0f && charObj[i]->getPos().x - (charObj[i]->getSize()) / 2.0f <= colObj[j]->getPos().x + (colObj[j]->getSize() / 2.0f))
					{
						if (charObj[i]->getPos().y + charObj[i]->getSize() / 2.0f >= colObj[j]->getPos().y - (colObj[j]->getSize()) / 2.0f && charObj[i]->getPos().y - (charObj[i]->getSize() / 2.0f) <= colObj[j]->getPos().y + (colObj[j]->getSize() / 2.0f))
						{
							charObj[i]->setColor({ 1.0f, 0.0f, 0.0f, 1.0f }, 0.1f);
							charObj[i]->minusLife(colObj[j]->getLife());

							delete colObj[j];
							colObj[j] = NULL;
						}
					}
				}
			}

		}
	}

	for (int i = 0; i < MAX_CHARACTER_COUNT; ++i)
	{
		if (charObj[i] != NULL)
		{
			if (charObj[i]->getLife() < 1)
			{
				for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
				{
					if (arrowArray[j] != NULL)
					{
						if (charObj[i]->getId() == arrowArray[j]->getId())
						{
							delete arrowArray[j];
							arrowArray[j] = NULL;
						}
					}
				}
				delete charObj[i];
				charObj[i] = NULL;
			}
		}
	}
}

void SceneMgr::CollisionChar()
{
	for (int i = 0; i < charNum; ++i)
	{
		int count = 0;
		for (int j = 0; j < charNum; ++j)
		{
			if (i != j)
			{
				if (objArray[i]->getPos().x + (objArray[i]->getSize()) / 2.0f >= objArray[j]->getPos().x - (objArray[j]->getSize()) / 2.0f && objArray[i]->getPos().x - (objArray[i]->getSize()) / 2.0f <= objArray[j]->getPos().x + (objArray[j]->getSize() / 2.0f))
				{
					if (objArray[i]->getPos().y + objArray[i]->getSize() / 2.0f >= objArray[j]->getPos().y - (objArray[j]->getSize()) / 2.0f && objArray[i]->getPos().y - (objArray[i]->getSize() / 2.0f) <= objArray[j]->getPos().y + (objArray[j]->getSize() / 2.0f))
					{
						count += 1;
						objArray[i]->setColor({ 0.1f * (float)objArray[i]->getLife(), 0.0f, 0.0f, 1.0f }, 0);
						objArray[i]->minusLife(1);
					}
				}
			}
		}

		if (count == 0)
		{
			objArray[i]->setColor({ 0.1f * objArray[i]->getLife(),  0.1f * objArray[i]->getLife(), 0.1f * objArray[i]->getLife(), 1.0f }, 0);
			objArray[i]->setCol(false);
		}
	}
}
