#include "gameLevel.h"

#include <fstream>
#include <sstream>

//加载文件并存入数组中
void GameLevel::load(const GLchar *file, GLuint levelWidth, GLuint levelHeight) {
    std::string line;
    std::ifstream fstream(file);
    GLuint tileCode;
    std::vector<std::vector<GLuint>> tileData;
    if (fstream) {
        while (std::getline(fstream, line)) {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        };
        if (tileData.size() > 0)
            init(tileData, levelWidth, levelHeight);
    }
}

//渲染场景
void GameLevel::draw(SpriteRenderer &renderer) {
    for (GameObject &tile : this->bricks)
        tile.draw(renderer);
}

//初始化
void GameLevel::init(std::vector<std::vector<GLuint>> titleData, GLuint levelWidth, GLuint levelHeight) {
    //根据文件计算出每个物体的长和宽
    GLuint hight = titleData.size();
    GLuint width = titleData[0].size();
    GLfloat unitHeight = levelHeight / hight;
    GLfloat unitWidth = levelWidth / static_cast<GLfloat>(width);
    //根据类型的不同来构造不同的对象
    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            if (titleData[i][j] == 1) {
                glm::vec2 pos(unitWidth * j, unitHeight * i);
                glm::vec2 size(unitWidth, unitHeight);
                GameObject obj(ResourceManager::getTexture("brick"), pos, size);
                obj.type = BRICK;
                this->bricks.push_back(obj);
            }
            if (titleData[i][j] == BEGIN || titleData[i][j] == END) {
                glm::vec2 pos(unitWidth * j, unitHeight * i);
                glm::vec2 size(unitWidth, unitHeight);
                GameObject obj(ResourceManager::getTexture("flag"), pos, size);
                obj.type = (Type) titleData[i][j];
                this->bricks.push_back(obj);
                if (titleData[i][j] == BEGIN) {
                    this->pos = glm::vec2(pos.x, pos.y);
                    this->size = glm::vec2(size.x / 5 * 4, size.y / 3);
                }
            }
        }
    }
}

