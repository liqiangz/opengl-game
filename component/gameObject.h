//
// Created by ibm on 2017/2/4.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../utility/texture.h"
#include "spriteRenderer.h"
enum Type {
    NOTHING,
    BRICK,
    END,
    BEGIN
};

class GameObject {

public:
    //颜色
    glm::vec3 color;
    //位置，大小，速度
    glm::vec2 position, size, velocity;
    //纹理
    Texture2D sprite;
    //旋转
    GLfloat rotation;
    //类型
    Type type;

    GameObject();

    GameObject(Texture2D sprite, glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));

    //渲染
    virtual void draw(SpriteRenderer &renderer);
};

#endif //GAME_GAMEOBJECT_H
