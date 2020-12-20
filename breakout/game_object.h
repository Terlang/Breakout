#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

/* Position represents left-up corner of a game object.
 * Size defines object as a rectangle 
 */

class GameObject {
public:
    // object state
    glm::vec2   Position, Size;
    glm::vec3   Color;
    float       Rotation;
    // render state
    Texture2D   Sprite;
    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), float rotation = 0.0f);
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);
};

#endif