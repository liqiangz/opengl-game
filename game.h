

#ifndef GAME_GAME_H
#define GAME_GAME_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "resourceManager.h"
#include "component/spriteRenderer.h"
#include "component/gameLevel.h"



enum gameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:

    // 游戏状态
    std::vector<GameLevel> levels;
    gameState              state;
    GLuint                 deathNumber;
    GLuint                 fps;
    GLuint                 level;
    GLboolean              keys[1024];
    GLuint                 width, height;

    Game(GLuint width, GLuint height);
    ~Game();
    // 初始化 - 加载纹理、着色器等
    void init();
    void reset();
    void processInput(GLfloat dt);
    void update(GLfloat dt);
    void render();
private:
    void doCollisions();

};

#endif //GAME_GAME_H
