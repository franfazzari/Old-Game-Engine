#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Bengine/SpriteBatch.h"
#include "Bengine/ResourceManager.h"
class Level
{
public:
	// Load the level
	Level(const std::string& fileName);

	~Level();

	void draw();


private:
	std::vector<std::string> _levelData;
	int _numHumans;
	Bengine::SpriteBatch _spriteBatch;
	
	glm::ivec2 _startPlayerPos;
	std::vector<glm::ivec2> _zombieStartPositions;
};

