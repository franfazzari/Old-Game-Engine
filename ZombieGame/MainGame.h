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
#include "Bengine/SpriteBatch.h"
#include "Bengine/ResourceManager.h"
#include "Bengine/InputManager.h"
#include "Bengine/Timing.h"
#include "Bullet.h"
#include "Agent.h"
#include <SDL_image.h>
#include "Level.h"

// SCreen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();



private:
	// Initializes the game systems
	void initSystems();
	// Handlers the game shaders
	void initShaders();
	// Game logic
	void gameLoop();
	// Handles user input
	void processInput();
	// Renders the game
	void drawGame();

	bool checkCollisions(Agent agent1, Agent object2);


	Window _window;	// The game window

	GameState _gameState;
	int _screenHeight = SCREEN_HEIGHT;
	int _screenWidth = SCREEN_WIDTH;

	GLSLProgram _colorProgram;
	Bengine::Camera2D _camera; // Main camera

	Bengine::SpriteBatch _spriteBatch;

	Bengine::InputManager _inputManager;
	Bengine::FPSLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;
	std::vector<Agent> _agents;
	std::vector<Level*> _levels; // Vector of all levels

	int _currentLevel;

	int _objects;

	float _fps;
	float _maxFPS;

	float _time;
};

