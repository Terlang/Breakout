#include "ball_object.h"


BallObject::BallObject()
    : GameObject(), Radius(12.5f), Stuck(true), Velocity(glm::vec2(0.0f))
{ }

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite, glm::vec3 color)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, color),
    Velocity(velocity), Radius(radius), Stuck(true)
{ }

glm::vec2 BallObject::Move(float dt, unsigned int Width, unsigned int Height) {
    // if not stuck to player board
    if (!this->Stuck)
    {
        // move the ball
        this->Position += this->Velocity * dt;
        // then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= Width) {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = Width - this->Size.x;
        }
        if (this->Position.y <= 0.0f) {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }
    return this->Position;
}
