#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <cstddef>

Sprite::Sprite() {

	_vboID = 0;
}

Sprite::~Sprite() {

	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}

}
void Sprite::draw() {

	// Don't need to unbind the textures because other textures might use the bind.
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	// Bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// Tell opengl that we want to use the first
	// attribute array. We only need one array right now
	// since we are using position.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// This is the position attribute pointer
	glVertexAttribPointer(0,2, GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
	// This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,sizeof(Vertex),(void*)offsetof(Vertex,color));
	// This is the uv attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	// Draw the 6 vertices to the screen
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Disable the vertex attrib array. This is not optional.
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
void Sprite::init(float x, float y, float width, float height, std::string texturePath) {

	// Initialize variables
	_PosX = x;
	_PosY = y;
	_Height = height;
	_Width = width;

	// Load the texture into our sprite
	_texture = ResourceManager::getTexture(texturePath);

	// If the vertex buffer hasn't been initialized yet, create one
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}
	Vertex vertexData[6];

	// First triangle
	vertexData[0].setPosition(x + _Width, y + _Height);
	vertexData[0].setUV(1.0f, 1.0f);
	
	vertexData[1].setPosition(x, y + _Height);
	vertexData[1].setUV(0.0f, 1.0f);


	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);


	// Second triangle
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(x + _Width, y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(x + _Width, y + _Height);
	vertexData[5].setUV(1.0f, 1.0f);


	for (int i = 0; i < 6; i++) {
		vertexData[i].setColor(255, 0, 255, 255);
	}

	vertexData[1].setColor(0, 0, 255, 255);

	vertexData[4].setColor(0, 255, 0, 255);
	

	// Bind the buffer and upload the buffer data
	glBindBuffer(GL_ARRAY_BUFFER,_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}