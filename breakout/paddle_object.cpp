#include "paddle_object.h"

PaddleObject::PaddleObject() :
	GameObject(), Velocity(glm::vec2(0.0f))
{ }

PaddleObject::PaddleObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, float rotation) :
	GameObject(pos, size, sprite, color, rotation), Velocity(glm::vec2(0.0f))
{ }

void PaddleObject::Move(float dt, unsigned int Width, unsigned int Height) {
	Position += dt * Velocity;
	if (Position.x < 0.0f) {
		Position.x = 0.0f; 
		Velocity = -Velocity;
	}
	else if (Position.x + Size.x > Width) {
		Position.x = Width - Size.x; 
		Velocity = -Velocity;
	}
}
