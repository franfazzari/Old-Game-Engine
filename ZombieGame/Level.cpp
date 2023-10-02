#include "Level.h"
#include <fstream>
#include "Bengine/Errors.h"

#define TILE_WIDTH = 50;

Level::Level(const std::string& fileName) {

	std::ifstream(file);
	file.open(fileName);
	// If the file failed to open
	if (file.fail()) {
		fatalError("Failed to open" + fileName);
	}

	// The file opened correctly
	std::string tmp;
	file >> tmp >> _numHumans;
	while (std::getline(file, tmp)) {
		_levelData.push_back(tmp);
	}
	
	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color color;
	color = { 255,255,255,255 };
	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[0].size(); x++) {
			// Grab the tile
			char tile = _levelData[y][x];

			// Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH, y* TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			// Process the tile
			switch (tile) {
			case 'R':
				_spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture("Textures/red_bricks.png").id,0.0f,color);
				break;
			case 'G':
				_spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture("Textures/glass.png").id, 0.0f, color);
				break;
			case 'L':
				_spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture("Textures/light_bricks.png").id, 0.0f, color);
				break;
			case '@':
				_startPlayerPos = { x * TILE_WIDTH, y * TILE_WIDTH };
				break;
			case 'Z':
				_zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
				break;
			}
		}
	}
	_spriteBatch.end();
}

Level::~Level(){
}

void Level::draw() {
	_spriteBatch.renderBatch();
}