#ifndef PLATE_OBJECT_H
#define PLATE_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"

class PaddleObject : public GameObject {
public:
	glm::vec2 Velocity;

	PaddleObject();
	PaddleObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), float rotation = 0.0f);

	void Move(float dt, unsigned int Width, unsigned int Height);
};

#endif