

#ifndef GAME_GAMELEVEL_H
#define GAME_GAMELEVEL_H

#include <vector>
#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "gameObject.h"
#include "../utility/texture.h"
#include "../resourceManager.h"
#include "spriteRenderer.h"

class GameLevel {
public:
    //一个游戏物体对象的向量
    std::vector<GameObject> bricks;
    //记录启示点的位置和大小，方便后面渲染 player
    glm::vec2 pos, size;

    GameLevel() {}

    //加载游戏场景文件
    void load(const GLchar *file, GLuint LevelWidth, GLuint levelHeight);

    //渲染场景
    void draw(SpriteRenderer &renderer);

private:
    void init(std::vector<std::vector<GLuint>> titleData, GLuint levelWidth, GLuint levelHeight);
};


#endif //GAME_GAMELEVEL_H
