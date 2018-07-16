
#include "gameObject.h"

GameObject::GameObject()
        : color(1.0f), position(0, 0), size(1, 1), sprite(),rotation(0.0f) {}

GameObject::GameObject(Texture2D sprite, glm::vec2 position, glm::vec2 size, glm::vec3 color)
        : color(color), position(position), size(size), sprite(sprite),rotation(0.0f),velocity(0.0f,0.0f),type(NOTHING) {}

void GameObject::draw(SpriteRenderer &renderer) {
    renderer.drawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}

