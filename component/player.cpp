#include "player.h"

void Player::move(GLfloat dt) {
    //重力加速度
    if (this->velocity.y < 200.f) {
        this->velocity.y += gravity * dt;
    } else {
        this->velocity.y = 200;
    }
    this->position += this->velocity * dt;

    //左移和右移的界限
    if (this->position.x <= 0.0f) {
        this->velocity.x = -this->velocity.x;
        this->position.x = 0.0f;
    } else if (this->position.x + this->size.x >= 800) {
        this->velocity.x = -this->velocity.x;
        this->position.x = 800 - this->size.x;
    }
    if (this->position.y >= 600) {
        this->position.y = 0.0f;
    }
}

void Player::processInput(GLfloat dt, GLboolean *keys) {

    //跳跃
    if (keys[GLFW_KEY_SPACE]) {
        if (isJumped == GL_TRUE) {
            this->velocity.y = -jumpVelocity;
            isJumped = GL_FALSE;
        }
    }
    //左移和右移，但在左移或右移只能执行其一。
    if (isAed == true) {
        if (keys[GLFW_KEY_A]) {
            velocitya -= acceleration * dt;
            if (velocitya < -100.0f)
                velocitya = -100.0f;
            if (this->position.x >= 0) {
                this->position.x += velocitya * dt;
            }
            isDed = GL_FALSE;
        } else {
            isDed = GL_FALSE;
            velocitya += acceleration * dt;
            if (velocitya > 0.0f) {
                velocitya = 0.0f;
                isDed = GL_TRUE;
            }
            if (this->position.x >= 0) {
                this->position.x += velocitya * dt;
            }
        }
    }
    if (isDed == GL_TRUE) {
        if (keys[GLFW_KEY_D]) {
            velocityd += acceleration * dt;
            if (velocityd > 100.0f)
                velocityd = 100.0f;
            if (this->position.x >= 0) {
                this->position.x += velocityd * dt;
            }
            isAed = GL_FALSE;
        } else {
            isAed = GL_FALSE;
            velocityd -= acceleration* dt;
            if (velocityd < 0.0f) {
                velocityd = 0.0f;
                isAed = GL_TRUE;
            }
            if (this->position.x >= 0) {
                this->position.x += velocityd * dt;
            }
        }
    }
}

