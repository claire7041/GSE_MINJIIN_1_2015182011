#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
}

SceneMgr::SceneMgr(int x, int y)
{
	g_Renderer = new Renderer(x, y);
	m_sound = new Sound();
	soundBG = m_sound->CreateSound("./bgm.wav");
	m_sound->PlaySoundW(soundBG, true, 0.2f);

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	backgroundTex = g_Renderer->CreatePngTexture("./sky.png");
	buildingTex[0] = g_Renderer->CreatePngTexture("./redBuilding.png");
	buildingTex[1] = g_Renderer->CreatePngTexture("./blueBuilding.png");
	objTex = g_Renderer->CreatePngTexture("./Character.png");
	particleBulletTex = g_Renderer->CreatePngTexture("./particleBullet.png");

	charNum = 0;
	bulletNum = 0;
	arrowNum = 0;
	spawnRedTime = 4.0f;
	spawnBlueTime = 0.0f;
	sceneShakeTime = 0.0f;
	startText = 5.0f;

	for (int i = 0; i < 3; ++i)
	{
		if (i == 1)
		{
			building[TEAM_RED][i] = new Object({ (150.0f * i) - 150.0f, 300.0f, 0.0f }, TEAM_RED, OBJECT_BUILDING);
			building[TEAM_BLUE][i] = new Object({ (150.0f * i) - 150.0f, -300.0f, 0.0f }, TEAM_BLUE, OBJECT_BUILDING);
		}
		else
		{
			building[TEAM_RED][i] = new Object({ (150.0f * i) - 150.0f, 270.0f, 0.0f }, TEAM_RED, OBJECT_BUILDING);
			building[TEAM_BLUE][i] = new Object({ (150.0f * i) - 150.0f, -270.0f, 0.0f }, TEAM_BLUE, OBJECT_BUILDING);
		}
	}
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

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (building[i][j] != NULL)
			{
				delete building[i][j];
				building[i][j] = NULL;
			}
		}
	}
	
	/*delete[] objArray;
	delete[] bulletArray;
	delete[] arrowArray;*/
	delete g_Renderer;
}

void SceneMgr::Update(float elapsedTime)
{
	float elapsedTimeinsecond = elapsedTime / 1000.0f;
	time += elapsedTimeinsecond;

	spawnRedTime -= elapsedTimeinsecond;
	spawnBlueTime -= elapsedTimeinsecond;
	startText -= elapsedTimeinsecond;

	if (spawnRedTime <= 0.0f)
	{
		AddActorObject({(float)((rand() % WIN_X) - (WIN_X / 2)), (float)((rand() % (WIN_Y / 2))), 0.0f }, TEAM_RED, OBJECT_CHARACTER);
		spawnRedTime = 4.0f;
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (building[i][j] != NULL)
			{
				if (building[i][j]->getArrowTime() >= 7.0f)
				{
					AddActorObject(building[i][j]->getPos(), building[i][j]->getTeam(), OBJECT_BULLET);
					building[i][j]->initArrowTime();
				}

				if (building[i][j] != NULL)
				{
					CollisionBuilding(building[i][j]);
					if (building[i][j]->getLife() < 1)
					{
						delete building[i][j];
						building[i][j] = NULL;
					}
				}
				if (building[i][j] != NULL)
				{
					CollisionObjBuilding(building[i][j], arrowArray);
					if (building[i][j]->getLife() < 1)
					{
						delete building[i][j];
						building[i][j] = NULL;
					}
				}
				if (building[i][j] != NULL)
				{
					CollisionObjBuilding(building[i][j], bulletArray);
					if (building[i][j]->getLife() < 1)
					{
						delete building[i][j];
						building[i][j] = NULL;
					}
				}
			}
		}
	}

	CollisionObj(objArray, bulletArray);
	CollisionObj(objArray, arrowArray);


	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (building[i][j] != NULL)
			{
				building[i][j]->Update(elapsedTime);
			}
		}
	}

	for (int i = 0; i < charNum; ++i)
	{
		if (objArray[i] != NULL) 
		{
			objArray[i]->Update(elapsedTime);
			if (objArray[i]->getArrowTime() >= 0.5f)
			{
				AddActorObject(objArray[i]->getPos(), objArray[i]->getTeam(), OBJECT_ARROW);
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
	g_Renderer->DrawTexturedRect(0.0f, 0.0f, 0.0f, 800.0f, 1.0f, 1.0f, 1.0f, 1.0f, backgroundTex, 0.5f);
	g_Renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, particleBulletTex, time, 0.01f);
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (building[i][j] != NULL)
			{
				g_Renderer->DrawTexturedRect(building[i][j]->getPos().x, building[i][j]->getPos().y, building[i][j]->getPos().z, building[i][j]->getSize(), building[i][j]->getColor().r, building[i][j]->getColor().g, building[i][j]->getColor().b, building[i][j]->getColor().a, buildingTex[i], building[i][j]->getLevel());
				if(building[i][j]->getTeam() == TEAM_RED)
					g_Renderer->DrawSolidRectGauge(building[i][j]->getPos().x, building[i][j]->getPos().y + 70, building[i][j]->getPos().z, building[i][j]->getSize(), 10.0f, 1.0f, 0.0f, 0.0f, 1.0f, (float)(building[i][j]->getLife() / 500.0f), building[i][j]->getLevel());
				else if(building[i][j]->getTeam() == TEAM_BLUE)
					g_Renderer->DrawSolidRectGauge(building[i][j]->getPos().x, building[i][j]->getPos().y - 70, building[i][j]->getPos().z, building[i][j]->getSize(), 10.0f, 0.0f, 0.0f, 1.0f, 1.0f, (float)(building[i][j]->getLife() / 500.0f), building[i][j]->getLevel());
			}
		}
	}

	for (int i = 0; i < charNum; ++i)
	{
		if (objArray[i] != NULL)
		{
			g_Renderer->DrawTexturedRectSeq(objArray[i]->getPos().x, objArray[i]->getPos().y, objArray[i]->getPos().z, objArray[i]->getSize(), objArray[i]->getColor().r, objArray[i]->getColor().g, objArray[i]->getColor().b, objArray[i]->getColor().a, objTex, objArray[i]->getCurrentAnimX(), objArray[i]->getCurrentAnimY(), objArray[i]->getTotalAnimX(), objArray[i]->getTotalAnimY(), objArray[i]->getLevel());
			if (objArray[i]->getTeam() == TEAM_RED)
				g_Renderer->DrawSolidRectGauge(objArray[i]->getPos().x, objArray[i]->getPos().y + 20, objArray[i]->getPos().z, objArray[i]->getSize(), 5.0f, 1.0f, 0.0f, 0.0f, objArray[i]->getColor().a, (float)(objArray[i]->getLife() / 10.0f), objArray[i]->getLevel());
			else if (objArray[i]->getTeam() == TEAM_BLUE)
				g_Renderer->DrawSolidRectGauge(objArray[i]->getPos().x, objArray[i]->getPos().y - 20, objArray[i]->getPos().z, objArray[i]->getSize(), 5.0f, 0.0f, 0.0f, 1.0f, objArray[i]->getColor().a, (float)(objArray[i]->getLife() / 10.0f), objArray[i]->getLevel());

		}
	}

	for (int i = 0; i < bulletNum; ++i)
	{
		if (bulletArray[i] != NULL)
		{
			g_Renderer->DrawParticle(bulletArray[i]->getPos().x, bulletArray[i]->getPos().y, bulletArray[i]->getPos().z, 5.0f, 1.0f, 1.0f, 0.6f, 1.0f, -bulletArray[i]->getDir().x, -bulletArray[i]->getDir().y, particleBulletTex, bulletArray[i]->getTime(), 0.25f);
			g_Renderer->DrawSolidRect(bulletArray[i]->getPos().x, bulletArray[i]->getPos().y, bulletArray[i]->getPos().z, bulletArray[i]->getSize(), bulletArray[i]->getColor().r, bulletArray[i]->getColor().g, bulletArray[i]->getColor().b, bulletArray[i]->getColor().a, bulletArray[i]->getLevel());
		}
	}

	for (int i = 0; i < arrowNum; ++i)
	{
		if (arrowArray[i] != NULL)
			g_Renderer->DrawSolidRect(arrowArray[i]->getPos().x, arrowArray[i]->getPos().y, arrowArray[i]->getPos().z, arrowArray[i]->getSize(), arrowArray[i]->getColor().r, arrowArray[i]->getColor().g, arrowArray[i]->getColor().b, arrowArray[i]->getColor().a, arrowArray[i]->getLevel());
	}

	if (startText > 0.0f)
		g_Renderer->DrawText(0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, 0.0f, 0.0f, 0.0f, "START");
}

void SceneMgr::AddActorObject(Vec3 pos, int team, int type)
{
	if (type == OBJECT_BUILDING)
	{
	}
	else if (type == OBJECT_CHARACTER)
	{
		if (team == TEAM_RED || (team == TEAM_BLUE && spawnBlueTime <= 0.0f))
		{
			if (charNum < MAX_CHARACTER_COUNT)
			{
				objArray[charNum] = new Object(pos, team, OBJECT_CHARACTER);
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
						objArray[i] = new Object(pos, team, OBJECT_CHARACTER);
						objArray[i]->setId(i);
						break;
					}
					i++;
				}
			}

			if (team == TEAM_BLUE)
				spawnBlueTime = 4.0F;
		}
	}
	else if (type == OBJECT_BULLET)
	{
		if (bulletNum == MAX_OBJECTS_COUNT)
		{
			bulletNum = 0;
		}

		bulletArray[bulletNum] = new Object(pos, team, OBJECT_BULLET);
		bulletNum++;
	}
	else if(type == OBJECT_ARROW)
	{
		if (arrowNum == MAX_OBJECTS_COUNT)
		{
			arrowNum = 0;
		}

		arrowArray[arrowNum] = new Object(pos, team, OBJECT_ARROW);

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

void SceneMgr::CollisionBuilding(Object* building)
{
	for (int i = 0; i < charNum; ++i)
	{
		if (objArray[i] != NULL && building != NULL)
		{
			if (objArray[i]->getPos().x + (objArray[i]->getSize()) / 2.0f >= building->getPos().x - (building->getSize()) / 2.0f && objArray[i]->getPos().x - (objArray[i]->getSize()) / 2.0f <= building->getPos().x + (building->getSize() / 2.0f))
			{
				if (objArray[i]->getPos().y + objArray[i]->getSize() / 2.0f >= building->getPos().y - (building->getSize()) / 2.0f && objArray[i]->getPos().y - (objArray[i]->getSize() / 2.0f) <= building->getPos().y + (building->getSize() / 2.0f))
				{
					if (!objArray[i]->getCol() && objArray[i]->getTeam() != building->getTeam())
					{
						objArray[i]->setCol(true);
						building->minusLife(objArray[i]->getLife());
						building->setTime(0.2f);
						objArray[i]->minusLife(20);
					
						//printf("%d캐릭터, %d건물수명: %d\n", objArray[i]->getTeam(), building->getTeam(), building->getLife());
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

void SceneMgr::CollisionObjBuilding(Object* building, Object * colObj[])
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (colObj[i] != NULL && building != NULL && colObj[i]->getTeam() != building->getTeam())
		{
			if (colObj[i]->getPos().x + (colObj[i]->getSize()) / 2.0f >= building->getPos().x - (building->getSize()) / 2.0f && colObj[i]->getPos().x - (colObj[i]->getSize()) / 2.0f <= building->getPos().x + (building->getSize() / 2.0f))
			{
				if (colObj[i]->getPos().y + colObj[i]->getSize() / 2.0f >= building->getPos().y - (building->getSize()) / 2.0f && colObj[i]->getPos().y - (colObj[i]->getSize() / 2.0f) <= building->getPos().y + (building->getSize() / 2.0f))
				{
					if (building->getTeam() != colObj[i]->getTeam())
					{
						building->setTime(0.2f);
						building->minusLife(colObj[i]->getLife());
						//printf("%d팀 %d타입, %d건물수명: %d\n", colObj[i]->getTeam(), colObj[i]->getLife(), building->getTeam(), building->getLife());
						
						delete colObj[i];
						colObj[i] = NULL;
					}
				}
			}
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
							if (charObj[i]->getTeam() != colObj[j]->getTeam())
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
