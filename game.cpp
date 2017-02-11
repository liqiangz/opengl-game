
#include "game.h"
#include <tuple>

SpriteRenderer *renderer;


Game::Game(GLuint width, GLuint height)
        : state(GAME_ACTIVE), keys(), width(width), height(height) {}

Game::~Game() {
    delete renderer;
}

void Game::init() {
    //加载 shaders
    ResourceManager::loadShader("../shaders/sprite.vs.glsl", "../shaders/sprite.frag.glsl", nullptr, "sprite");
    // 投影矩阵
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f,
                                      -1.0f, 1.0f);
    ResourceManager::getShader("sprite").use().SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);

    ResourceManager::loadTexture("../textures/car.png", GL_TRUE, "car");

    Shader spriteShader = ResourceManager::getShader("sprite");
    renderer = new SpriteRenderer(spriteShader);
}

void Game::processInput(GLfloat dt) {

}

void Game::update(GLfloat dt) {

}

void Game::render() {

    if (this->state == GAME_ACTIVE) {
        renderer->drawSprite(ResourceManager::getTexture("car"), glm::vec2(0, 0),
                             glm::vec2(this->width, this->height/3*2));
    }
}