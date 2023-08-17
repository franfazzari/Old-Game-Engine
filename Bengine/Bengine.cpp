#include "Bengine.h"
#include <SDL.h>
#include <GL/glew.h>

namespace Bengine {

	int init() {
		// Initialize SDL 
		SDL_Init(SDL_INIT_EVERYTHING);

		// Sets up two buffer windows that we can switch in between when drawing
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}