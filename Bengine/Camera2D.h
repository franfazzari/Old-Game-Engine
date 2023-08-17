#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
namespace Bengine {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		// setters
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _updated = false; }
		void setScale(float newScale) { _scale = newScale; _updated = false; }

		// getters
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:

		int _screenWidth, _screenHeight;
		bool _updated;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};
}
