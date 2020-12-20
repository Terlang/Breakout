#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

enum Direction {
	UP,
	DONW,
	LEFT,
	RIGHT
};

class Game {
public:
	bool Keys[1024];
	unsigned int Width, Height;
	GameLevel Level;

	Game(unsigned int width, unsigned int height);
	~Game();
	void Init();
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};

#endif