#include "game_object.h"

GameObject::GameObject() :
	Position(glm::vec2(0.0f)), Size(glm::vec2(10.0f)), Color(glm::vec3(1.0f)), Sprite(), Rotation(0.0f)
{ }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, float rotation) :
	Position(pos), Size(size), Color(color), Sprite(sprite), Rotation(rotation)
{ }

void GameObject::Draw(SpriteRenderer& Renderer) {
	Renderer.DrawSprite(std::move(Sprite), Position, Size, Rotation, Color);
}
