#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>

class Sprite
{
public:

	Sprite();
	~Sprite();

	void draw();

	void init(float x, float y, float width, float height, std::string texturePath);

private:
	int _PosX;
	int _PosY;
	int _Width;
	int _Height;
	GLuint _vboID;
	GLTexture _texture;

};

