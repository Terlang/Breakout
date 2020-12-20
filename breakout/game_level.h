#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "brick_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

class GameLevel {
public:
	std::vector<BrickObject> bricks;

	GameLevel() { }
	int load(const char *path, unsigned int levelWidth, unsigned int levelHeight);
	void Draw(SpriteRenderer& Renderer);
	bool isComplete();
};

#endif