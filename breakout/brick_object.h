#ifndef BRICK_OBJECT_H
#define BRICK_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "game_object.h"

class BrickObject : public GameObject {
public:
	bool isDestroyed;
	bool isSolid;
	BrickObject();
	BrickObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), float rotation = 0.0f, bool solid = true);
};


#endif