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

	//Initialize our sprite (temporary).
	_sprites.push_back(new Sprite());
	_sprites.back()->init(_screenWidth/2,_screenWidth/2,_screenWidth/2,_screenWidth/2, "Textures/PNG/wood.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, _screenWidth/2, _screenWidth/2, _screenWidth/2, "Textures/PNG/wood.png");
	//_playerTexture = ImageLoader::loadPNG("Textures/PNG/wood.png");

	gameLoop();
}

void MainGame::initSystems() {
	Bengine::init();

	// Initialize the window
	_window.createWindow("Game Engine", _screenWidth, _screenHeight, 0); 

	// Initialize shaders
	initShaders();
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
	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	// Setting the camera matrix uniform
	GLuint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	// Draw our sprite!
	for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	}
	

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
		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.01;

		_camera.update();

		drawGame();
		calculateFPS();

		// Print once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		// Limit the fps to the max fps
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
	}
}

// Main game process inputs function
void MainGame::processInput() {

	// Camera speed indicator
	const float CAMERA_SPEED = 20.0f;
	
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
			switch (e.key.keysym.sym) {
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
				break;
			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
				break;
			case SDLK_a:
				_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
				break;
			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
				break;
			case SDLK_q:
				_camera.setScale(_camera.getScale() + SCALE_SPEED);
				break;
			case SDLK_e:
				_camera.setScale(_camera.getScale() - SCALE_SPEED);
				break;
			}
			break;
		}
	}

}

void MainGame::calculateFPS() {
	// We initialize the array of fps samples
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;


	// Get the current ticks and the previous ticks
	static float prevTicks = SDL_GetTicks();
	
	float currentTicks;
	currentTicks = SDL_GetTicks();

	// We calculate the frame time by substracting the previous ticks from the current
	// Giving us the amount of ticks in between each frame
	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	}
	else {
		_fps = 60.0f;
	}
	currentFrame++;
}