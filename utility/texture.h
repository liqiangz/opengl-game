

#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H
#include <GL/glew.h>


class Texture2D
{
public:
    GLuint id;
    // Texture 图片尺寸
    GLuint width, height;
    // Texture 格式
    GLuint internalFormat; // 纹理对象的格式
    GLuint imageFormat; // 加载图片的格式
    // 纹理设置
    GLuint wrapS;
    GLuint wrapT;
    GLuint filterMin;
    GLuint filterMax;

    Texture2D();
    // 生成纹理
    void generate(GLuint width, GLuint height, unsigned char* data);
    // 绑定纹理
    void bind() const;
};
#endif //GAME_TEXTURE_H
