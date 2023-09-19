#include "MainGame.h"
#include <Bengine/Bengine.h>




MainGame::MainGame(): 
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() {

}

// Main game run function
void MainGame::run() {
	initSystems();

	// Set the camera position otherwise it loads wrong, not sure why
	_camera.setPosition(glm::vec2(_screenWidth / 2.0f, _screenWidth / 2.0f));

	gameLoop();
}

void MainGame::initSystems() {
	Bengine::init();

	// Initialize the window
	_window.createWindow("Game Engine", _screenWidth, _screenHeight, 0); 

	// Initialize shaders
	initShaders();

	// Initialize spriteBatch
	_spriteBatch.init();

	// Initialize FPSLimiter
	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

// Main game drawing to screen function 
void MainGame::drawGame() {
	// Clear the screen 
	glClearDepth(1.0);
	// Clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable the shader
	_colorProgram.use();

	// We are using the texture unit 0
	glActiveTexture(GL_TEXTURE0);
	// Get the uniform location
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	// Tell the shader that the texture is in texture unit 0
	glUniform1i(textureLocation, 0);

	// Setting up the uniform
	

	// Setting the camera matrix uniform
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.begin();
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 pos(_screenWidth / 2.0f, _screenHeight / 2.0f, 50.0f, 50.0f);

	static GLTexture texture = ResourceManager::getTexture("Textures/PNG/rock_wall.png");
	if (texture.id == 0) {
		while (true) {

		}
	}
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;	
	color.a = 255;

	_spriteBatch.draw(pos,uv, texture.id, 0.0f, color);

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable the shader
	_colorProgram.unuse();

	// Swap the buffer window and draw everything to screen!
	_window.swapBuffer();

}

// Main game loop function
void MainGame::gameLoop() {

	// Will loop until we set _gameState to EXIT
	while (_gameState != GameState::EXIT) {
		// Use for frame time measuring
		_fpsLimiter.begin();

		processInput();
		_time += 0.01;

		_camera.update();

		drawGame();

		_fps = _fpsLimiter.end();

		// Print once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

// Main game process inputs function
void MainGame::processInput() {

	// Camera speed indicator
	const float CAMERA_SPEED = 5.0f;
	
	// Camera scale speed indicator
	const float SCALE_SPEED = 0.1f;

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;
	
	// While application is running
	while (SDL_PollEvent(&e)) {

		switch (e.type) {
		// Check for user exit
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		// Check for user mouse movement
		case SDL_MOUSEMOTION:
			//std::cout << e.motion.x << " " << e.motion.y << std::endl;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(e.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(e.key.keysym.sym);
			break;
		}
	}
	
	if (_inputManager.isKeyPressed(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_s)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
	if (_inputManager.isKeyPressed(SDLK_a)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}

	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}

}
