#pragma once
#include <glm/glm.hpp>
#include <Bengine/SpriteBatch.h>

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifetime);

	void init(glm::vec2 pos, glm::vec2 dir, float speed);
	void draw(Bengine::SpriteBatch& spriteBatch);
	// Returns true when we need to be destroyed.
	bool update();

private:
	int _lifetime;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;

};

