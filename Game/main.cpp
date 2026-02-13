#define SDL_MAIN_HANDLED
#include <Windows.h>
#include <SDL.h>
#include <gl/glew.h>
#include <stdio.h>
#include "MainGame.h"
#include <iostream>
#include <glm/glm.hpp>

int main(int argv, char** args) {

	MainGame mainGame;
	mainGame.run();
	return 0;
} 