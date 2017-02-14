
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game.h"
#include "resourceManager.h"
void key_callback(GLFWwindow* wwindow, int key,int scancode, int action, int mode);

//屏幕宽度
const GLuint SCREEN_WIDTH = 800;
//屏幕高度
const GLuint SCREEN_HEIGHT = 600;

GLboolean jumpState=GL_TRUE;

Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

int main() {

    //初始化 glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    //初始化 glew
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();

    //opengl 设置
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game.init();

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = glfwGetTime();

    game.state = GAME_MENU;

    //游戏循环
    while(!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        game.processInput(deltaTime);
        game.update(deltaTime);

        //设置屏幕颜色
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.render();
        glfwSwapBuffers(window);
    }
    ResourceManager::clear();
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key==GLFW_KEY_SPACE)
        game.keys[key] = GL_FALSE;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if(key==GLFW_KEY_SPACE) {
            if (action == GLFW_PRESS && jumpState == GL_TRUE) {
                game.keys[key] = GL_TRUE;
                jumpState = GL_FALSE;
            } else if (action == GLFW_RELEASE) {
                game.keys[key] = GL_FALSE;
                jumpState = GL_TRUE;
            }
        } else{
            if (action == GLFW_PRESS ) {
                game.keys[key] = GL_TRUE;
            } else if (action == GLFW_RELEASE) {
                game.keys[key] = GL_FALSE;
            }
        }
    }
}