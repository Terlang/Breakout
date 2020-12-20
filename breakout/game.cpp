#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "paddle_object.h"
#include "ball_object.h"

SpriteRenderer* Renderer;
PaddleObject* Paddle;
BallObject* Ball;

Game::Game(unsigned int width, unsigned int height) :
	Width(width), Height(height), Keys(), Level()
{ }

Game::~Game() {
    delete Renderer;
    delete Paddle;
}

void Game::Init() {
	ResourceManager::LoadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").use();
    ResourceManager::GetShader("sprite").setInt("image", 0);
    ResourceManager::GetShader("sprite").setMat4("projection", projection);

    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("textures/block.png", false, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("textures/paddle.png", true, "paddle");
    ResourceManager::LoadTexture("textures/ball.png", true, "ball");

    Level.load("levels/level0.txt", this->Width, this->Height / 2);

    glm::vec2 PaddlePos = glm::vec2((this->Width - PADDLE_SIZE.x)/2.0f, this->Height - PADDLE_SIZE.y);
    Paddle = new PaddleObject(PaddlePos, PADDLE_SIZE, ResourceManager::GetTexture("paddle"), PADDLE_VELOCITY);

    glm::vec2 BallPos = glm::vec2(this->Width/2.0f - BALL_RADIUS, PaddlePos.y-2*BALL_RADIUS);
    Ball = new BallObject(BallPos, BALL_RADIUS, BALL_VELOCITY, ResourceManager::GetTexture("ball"));
}

void Game::Update(float dt) { 

}

void Game::ProcessInput(float dt) {
    // move playerboard
    if (this->Keys[GLFW_KEY_A])
    {
        if (Paddle->Position.x >= 0.0f)
        {
            Paddle->Position.x -= Paddle->Velocity.x*dt;
            if (Ball->Stuck)
                Ball->Position.x -= Paddle->Velocity.x * dt;
        }
    }
    if (this->Keys[GLFW_KEY_D])
    {
        if (Paddle->Position.x <= this->Width - Paddle->Size.x)
        {
            Paddle->Position.x += Paddle->Velocity.x * dt;
            if (Ball->Stuck)
                Ball->Position.x += Paddle->Velocity.x * dt;
        }
    }
    if (this->Keys[GLFW_KEY_SPACE]) {
        Ball->Stuck = false;
    }
}

void Game::Render() {
    // draw background
    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

    // draw level
    this->Level.Draw(*Renderer);

    // draw paddle
    Paddle->Draw(*Renderer);

    // draw ball
    Ball->Draw(*Renderer);
}
