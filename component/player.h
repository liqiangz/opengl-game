

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gameObject.h"

class Player : public GameObject {
public:
    //左右移动时的加速度
    GLfloat acceleration=200.0f;
    //是否处于跳跃状态中
    GLboolean isJumped = GL_FALSE;
    //是否左移中
    GLboolean isAed = GL_TRUE;
    //是否右移中
    GLboolean isDed = GL_TRUE;
    //左移速度
    GLfloat velocitya = 0;
    //右移速度
    GLfloat velocityd = 0;
    //重力加速度
    GLfloat gravity;
    //跳跃给予物体向上的速度
    GLfloat jumpVelocity;
    Player():GameObject(),gravity(1.0f){}
    Player(Texture2D sprite, glm::vec2 position, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f),GLfloat gravity=200.0f)
            :GameObject(sprite, position, size, color),gravity(gravity),jumpVelocity(200.0f){}
    //对象位置的更新
    void move(GLfloat dt);
    //按键反馈
    void processInput(GLfloat dt,GLboolean* keys);
};

#endif //GAME_PLAYER_H
