#include "Timing.h"

#include <SDL.h>

namespace Bengine {

	FPSLimiter::FPSLimiter() {

	}

	void FPSLimiter::init(float maxFPS) {
		setMaxFPS(maxFPS);
	}

	void FPSLimiter::setMaxFPS(float maxFPS) {
		_maxFPS = maxFPS;
	}

	void FPSLimiter::begin() {
		_startTicks = SDL_GetTicks();
	}

	float FPSLimiter::end() {

		calculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;
		// Limit the fps to the max fps
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}

		return _fps;
	}

	void FPSLimiter::calculateFPS() {
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


}