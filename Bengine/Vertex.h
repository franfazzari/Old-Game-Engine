#pragma once

#include <GL/glew.h>

struct Position {
	float x;
	float y;
};


struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV {
	float u;
	float v;
};

struct Vertex {
	
	// This is the position struct 
	Position position;

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	// 4 bytes for R G B A 
	Color color;

	// This function helps set the color the struct
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	// UV texture coordinates
	UV uv;

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
};