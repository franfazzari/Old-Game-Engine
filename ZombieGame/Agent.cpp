#include "Agent.h"
#include <Bengine/ResourceManager.h>

Agent::Agent(glm::vec2 pos, glm::vec2 dir, float speed, int health) {
	_position = pos;
	_direction = dir;
	_speed = speed;
	_health = health;
	_updated = false;
}
Agent::~Agent()
{}

void Agent::draw(Bengine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::getTexture("Texture/PNG/Agent.png");
	Color color;
	// The Agent color depends on the type for now is white.
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

void Agent::updateHealth(int change) {
	_health += change;
}

void Agent::update() {
	_updated = true;
}

glm::vec2 Agent::getPosition() {
	return _position;
}

int Agent::getHealth() {
	return _health;
}

int Agent::getRadius() {
	return _radius;
}


