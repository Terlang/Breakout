#include "paddle_object.h"

PaddleObject::PaddleObject() :
	GameObject(), Velocity(glm::vec2(0.0f))
{ }

PaddleObject::PaddleObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, glm::vec3 color, float rotation) :
	GameObject(pos, size, sprite, color, rotation), Velocity(velocity)
{ }
