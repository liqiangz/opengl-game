


#define GAME_SPRITERENDERER_H
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utility/texture.h"
#include "../utility/shader.h"


class SpriteRenderer
{
public:

    SpriteRenderer(Shader &shader);

    ~SpriteRenderer();
    // 渲染纹理，注意，这里的 pos 坐标是纹理的左上角点的坐标
    void drawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:

    Shader shader;
    GLuint quadVAO;
    // 初始化
    void initRenderData();
};
#endif //GAME_SPRITERENDERER_H
