#pragma once
#include "GLTexture.h"
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

// Loads images into GLTextures
class ImageLoader
{
public:
	static GLTexture loadPNG(std::string filePath);
};

