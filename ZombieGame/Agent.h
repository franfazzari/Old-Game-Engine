#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <Bengine/SpriteBatch.h>

class Agent
{
public:
	Agent(glm::vec2 pos, glm::vec2 dir, float speed, int health);
	~Agent();

	void updateHealth(int health);
	void update();

	//getters
	glm::vec2 getPosition();
	int getRadius();
	int getHealth();

	//setters
	void setPosition(const glm::vec2& newPosition) { _position = newPosition; _updated = false; }


	void draw(Bengine::SpriteBatch& spriteBatch);


private:
	int _radius;
	bool _updated;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;
	int _health;
};

