#pragma once
#include <SDL.h>
#include <gl/glew.h>
#include <string>
#include <iostream>
#include <GL/GL.h>
#include <vector>
#include <Bengine/Window.h>
#include <Bengine/Camera2D.h>
#include "Bengine/Sprite.h"
#include "Bengine/Errors.h"
#include "Bengine/GLSLProgram.h"
#include "Bengine/GLTexture.h"


// SCreen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

enum class GameState {PLAY,EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();



private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void calculateFPS();

	Window _window;

	GameState _gameState;
	int _screenHeight = SCREEN_HEIGHT;
	int _screenWidth = SCREEN_WIDTH;


	std::vector <Sprite*> _sprites;

	GLSLProgram _colorProgram;
	Bengine::Camera2D _camera;

	float _frameTime;
	float _fps;
	float _maxFPS;

	float _time;
};

