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
    Ball->Move(dt, this->Width, this->Height);
    this->DoCollisions();
    // check loss condition
    if (Ball->Position.y >= this->Height) { // did ball reach bottom edge? 
        this->Reset();
    }
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

void Game::Reset() {
    this->Level.load("levels/level0.txt", this->Width, this->Height / 2);
    Paddle->Position = glm::vec2(this->Width / 2.0f - PADDLE_SIZE.x / 2.0f, this->Height - PADDLE_SIZE.y);
    Ball->Position = glm::vec2(this->Width / 2.0f - BALL_RADIUS, Paddle->Position.y - 2 * BALL_RADIUS);
    Ball->Stuck = true;
}


// collision detection
// bool CheckCollision(GameObject& one, GameObject& two);
Collision CheckCollision(BallObject& one, GameObject& two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions() {
    for (BrickObject& box : this->Level.bricks) {
        if (!box.isDestroyed) {
            Collision collision = CheckCollision(*Ball, box);
            if (std::get<0>(collision)) { // if collision is true 
                // destroy block if not solid
                if (!box.isSolid)  box.isDestroyed = true;
                // collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) { // horizontal collision 
                    // reverse horizontal velocity
                    // relocate
                    float penetration = Ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        Ball->Position.x += penetration; // move ball to right
                    else
                        Ball->Position.x -= penetration; // move ball to left;
                }
                else { // vertical collision
                    std::cout << Ball->Position.x << std::endl;
                    Ball->Velocity.y = -Ball->Velocity.y; // reverse vertical velocity
                    // relocate
                    float penetration = Ball->Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        Ball->Position.y -= penetration; // move ball bback up
                    else
                        Ball->Position.y += penetration; // move ball back down
                }
            }
        }
    }
    // check collisions for player pad (unless stuck)
    Collision result = CheckCollision(*Ball, *Paddle);
    if (!Ball->Stuck && std::get<0>(result)) {
        // check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = Paddle->Position.x + Paddle->Size.x / 2.0f;
        float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        float percentage = distance / (Paddle->Size.x / 2.0f);
        // then move accordingly
        float strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = BALL_VELOCITY.x * percentage * strength;
        //Ball->Velocity.y = -Ball->Velocity.y;
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        // fix sticky paddle
        Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
    }
}

Collision CheckCollision(BallObject& one, GameObject& two) // AABB - Circle collision
{
    // get center point circle first 
    glm::vec2 center(one.Position + one.Radius);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;

    if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

// calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f),	// left
        glm::vec2(1.0f, 0.0f)	// right
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}