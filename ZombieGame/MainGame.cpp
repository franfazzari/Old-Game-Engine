#include "MainGame.h"
#include <Bengine/Bengine.h>


MainGame::MainGame() :
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	_fps(0),
	_objects(1)
{
	// TODO
	_camera.init(_screenWidth, _screenHeight);
	;
}

MainGame::~MainGame() {
	//TODO
	for (int i = 0; i < _levels.size(); i++) {
		delete(_levels[i]);
	}
}

void MainGame::run() {
	//TODO
	initSystems();
	gameLoop();

}

void MainGame::initSystems() {
	//TODO

	Bengine::init();

	// Initialize the window
	_window.createWindow("Zombie Game", _screenWidth, _screenHeight, 0);
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);

	// Initialize shaders
	initShaders();

	_camera.init(_screenWidth, _screenHeight);

	//Level 1
	_levels.push_back(new Level("Levels/level1.txt"));
	_currentLevel = 0;

	// Initialize spriteBatch
	_spriteBatch.init();

	// Initialize FPSLimiter
	_fpsLimiter.init(_maxFPS);

}

void MainGame::initShaders() {
	//TODO
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::drawGame() {
	//TODO
	// Clear the screen
	glClearDepth(1.0f);
	// Clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind the shaders
	_colorProgram.use();


	// Make sure the shader uses texture 0
	GLint textureUniform = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	// Grab the camera matrix
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _colorProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Draw the level
	_levels[_currentLevel]->draw();

	// Unbind the shader
	_colorProgram.unuse();

	_window.swapBuffer();
}

void MainGame::gameLoop() {
	//TODO

	// Will loop until we set _gameState to EXIT
	while (_gameState != GameState::EXIT) {
		// Use for frame time measuring
		
		_fpsLimiter.setMaxFPS(60.0f);
		_fpsLimiter.begin();

		processInput();
		_time += 0.01f;

		_camera.update();

		// Draw my game
		drawGame();

		_fps = _fpsLimiter.end();

	}
}

void MainGame::processInput() {
	//TODO
	
	// Camera speed indicator
	const float CAMERA_SPEED = 5.0f;

	// Player speed indicator
	const float PLAYER_SPEED = 5.0f;
	
	// Camera scale speed indicator
	const float SCALE_SPEED = 0.1f;

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	// While the application is running
	while (SDL_PollEvent(&e)) {
		
		switch (e.type) {

			// Check for user exit
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

			// Check for user mouse usage
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(e.motion.x, e.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(e.button.button);
			break;
			
			// Check for button use
		case SDL_KEYDOWN:
			_inputManager.pressKey(e.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(e.key.keysym.sym);
		}
	}

	// Different key cases

	// Handle movement of player and camera at the same time
	if (_inputManager.isKeyPressed(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_a)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.screenToWorldCoords(mouseCoords);
		std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(playerPosition, direction, 5.0f, 1000);

	}


}
