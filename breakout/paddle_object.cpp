#include "paddle_object.h"

PaddleObject::PaddleObject() :
	GameObject(), Velocity(glm::vec2(0.0f))
{ }

PaddleObject::PaddleObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, glm::vec3 color, float rotation) :
	GameObject(pos, size, sprite, color, rotation), Velocity(velocity)
{ }

glm::vec2 PaddleObject::Move(float dt, unsigned int Width, unsigned int Height) {
	this->Position += dt * Velocity;
	if (Position.x < 0.0f) {
		this->Position.x = 0.0f; 
		Velocity = -Velocity;
	}
	else if (Position.x + Size.x > Width) {
		this->Position.x = Width - Size.x; 
		Velocity = -Velocity;
	}
	return this->Position;
}
