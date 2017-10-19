/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "SceneMgr.h"

Renderer *g_Renderer = NULL;
SceneMgr* scene;

bool flag = false;

void Init(void)
{
	srand((unsigned)time(NULL));
	scene = new SceneMgr;
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.7f, 1.0f);

	// Renderer Test
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		g_Renderer->DrawSolidRect(scene->getObject(i)->getPos().x, scene->getObject(i)->getPos().y, scene->getObject(i)->getPos().z, scene->getObject(i)->getSize(), scene->getObject(i)->getColor().r, scene->getObject(i)->getColor().g, scene->getObject(i)->getColor().b, scene->getObject(i)->getColor().a);
	}
	glutSwapBuffers();
}

void Idle(void)
{
	scene->Update();
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			flag = true;

		if (flag == true && state == GLUT_UP)
		{
			flag = false;
			//obj->setPos({ (float)x - 250, 250 - (float)y, 0.0f });
		}
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	Init();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete scene;

    return 0;
}

