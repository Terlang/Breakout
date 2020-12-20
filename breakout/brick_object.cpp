#include "brick_object.h"

BrickObject::BrickObject() : 
	GameObject(), isSolid(false), isDestroyed(false)
{ }

BrickObject::BrickObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, float rotation, bool solid) :
	GameObject(pos, size, sprite, color, rotation), isSolid(solid), isDestroyed(false)
{ }

void BrickObject::Draw(SpriteRenderer& Renderer) {
	if (!isDestroyed) {
		GameObject::Draw(Renderer);
	}
}
