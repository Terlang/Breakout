#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

// Initial size of the player paddle
const glm::vec2 PADDLE_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const glm::vec2 PADDLE_VELOCITY(500.0f, 0.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;
// Initial velocity of the Ball
const glm::vec2 BALL_VELOCITY(100.0f, -350.0f);

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