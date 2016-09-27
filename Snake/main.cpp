#include "RenderManager.h"

#include <Windows.h>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	RenderManager* render = new RenderManager();

	render->initGLFW();
	if (!render->createWindowObject())
		return -1;
	render->setKeyCallback();
	if (!render->initGLEW())
		return -1;
	render->setViewport();
	render->setDepthBuffer();
	render->setMatrixes();
	render->createObjects();

	render->gameLoop();

	delete render;
	return 0;
}