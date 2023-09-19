#version 130
// The frament shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// This is the 3 component float vector that gets outputted to the screen
// for each pixel.
out vec4 color;

// In this scenario since we are not using the time variable it is going to be deleted when we compile
// our shaders, therefore we need to use the variable somehow or comment out all the code that uses
// it when we try to compile our code.
uniform sampler2D mySampler;

void main() {

	// Look up the texture mySample and lookup the UV for that texture
	vec4 textureColor = texture(mySampler, fragmentUV);
	
	
	// Make colors crazy using time and position;
	
	color = fragmentColor* textureColor;
}