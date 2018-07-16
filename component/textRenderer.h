//
// Created by ibm on 2017/2/9.
//

#ifndef GAME_TEXTRENDER_H
#define GAME_TEXTRENDER_H

#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../utility/texture.h"
#include "../utility/shader.h"


struct Character {
    GLuint TextureID;   // ID 字形纹理
    glm::ivec2 Size;    // 字形尺寸
    glm::ivec2 Bearing; // 向上的偏移量
    GLuint Advance;     // 水平偏移量
};

class TextRenderer
{
public:

    std::map<GLchar, Character> Characters;
    // 需要用到的 shader
    Shader TextShader;

    TextRenderer(GLuint width, GLuint height);
    // 加载字形文件
    void load(std::string font, GLuint fontSize);
    // 渲染指定的文本
    void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
private:

    GLuint VAO, VBO;
};
#endif //GAME_TEXTRENDER_H
