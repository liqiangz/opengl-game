

#ifndef GAME_RESOURCEMANAGER_H
#define GAME_RESOURCEMANAGER_H

#include <map>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "utility/texture.h"
#include "utility/shader.h"


class ResourceManager
{
public:
    static std::map<std::string, Shader>    shaders;
    static std::map<std::string, Texture2D> textures;
    // 加载 shader 程序
    static Shader   loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    // 获取指定的 shader
    static Shader   getShader(std::string name);
    // 从文件中加载纹理
    static Texture2D loadTexture(const GLchar *file, GLboolean alpha, std::string name);
    // 获取指定的 纹理
    static Texture2D getTexture(std::string name);

    static void      clear();
private:

    ResourceManager() { }

    static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);

    static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif //GAME_RESOURCEMANAGER_H
