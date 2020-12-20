#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"


class BallObject : public GameObject {
public:
    // ball state
    float   Radius;
    bool    Stuck;
    glm::vec2 Velocity;

    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));

    glm::vec2 Move(float dt, unsigned int Width, unsigned int Height);
};

#endif
