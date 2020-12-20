#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"

SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height) :
	Width(width), Height(height), Keys(), Level()
{ }

Game::~Game() {
    delete Renderer;
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

    Level.load("levels/level0.txt", this->Width, this->Height / 2);
}

void Game::Update(float dt) { }

void Game::ProcessInput(float dt) { }

void Game::Render() {
    // draw background
    Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

    // draw level
    this->Level.Draw(*Renderer);
}