#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

TextureCache::TextureCache() {

}

TextureCache::~TextureCache() {

}

GLTexture TextureCache::getTexture(std::string texturePath) {

	// Lookup the texture and see if its in the map
	auto mit  = _textureMap.find(texturePath);

	// Check if the texture is not in the map
	if (mit == _textureMap.end()) {
		// If it's not in the map we have to load it to the map

		// Load the texture 
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);

		// Insert the new texture into the map
		_textureMap.insert(make_pair(texturePath, newTexture));

		std::cout << "Used Cached Texture!\n";
		return newTexture;
	}
	else {

		std::cout << "Loaded Texture\n";
		// If the texture is already loaded we want to return the texture
		return mit->second;
	}
}