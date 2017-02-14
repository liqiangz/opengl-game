
#include "game.h"
#include "component/player.h"
#include "component/textRenderer.h"
#include <tuple>
#include <algorithm>
#include <sstream>

SpriteRenderer *renderer;
Player *player;
GLfloat time = 0;

//碰撞方向
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

//文字渲染器
TextRenderer *Text;

Game::Game(GLuint width, GLuint height)
        : state(GAME_MENU), keys(), width(width), height(height), level(0), fps(0), deathNumber(0) {}

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

    //加载纹理
    ResourceManager::loadTexture("../textures/background.jpg", GL_FALSE, "background");
    ResourceManager::loadTexture("../textures/brick.jpg", GL_FALSE, "brick");
    ResourceManager::loadTexture("../textures/flag.png", GL_TRUE, "flag");
    ResourceManager::loadTexture("../textures/car.png", GL_TRUE, "car");

    //加载关卡文件
    GameLevel one, two, three;
    one.load("../levels/one.level", this->width, this->height);
    two.load("../levels/two.level", this->width, this->height);
    three.load("../levels/three.level", this->width, this->height);
    this->levels.push_back(one);
    this->levels.push_back(two);
    this->levels.push_back(three);
    player = new Player(ResourceManager::getTexture("car"), this->levels[this->level].pos,
                        this->levels[this->level].size);
    Shader spriteShader = ResourceManager::getShader("sprite");
    renderer = new SpriteRenderer(spriteShader);

    Text = new TextRenderer(this->width, this->height);
    //加载字体
    Text->load("../fonts/arial.TTF", 24);
}

void Game::processInput(GLfloat dt) {
    if (this->state == GAME_MENU) {
        if (this->keys[GLFW_KEY_ENTER]) {
            state = GAME_ACTIVE;
        }
    }
    if (this->state == GAME_WIN) {
        if (this->keys[GLFW_KEY_R]) {
            state = GAME_ACTIVE;
            this->deathNumber = 0;
            this->level = 0;
            player->position = this->levels[level].pos;
        }
    }
    if (this->state == GAME_ACTIVE) {
        player->processInput(dt, keys);
    }
}

void Game::update(GLfloat dt) {
    if(state == GAME_ACTIVE) {
        time += dt;
        player->move(dt);
        this->doCollisions();
        if (time >= 1) {
            fps = 1 / dt;
            time = 0;
        }
    }
}

void Game::render() {
    std::stringstream sDeathNumber;
    sDeathNumber << this->deathNumber;

    if (this->state == GAME_ACTIVE) {
        ResourceManager::getShader("sprite").use();
        renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0, 0),
                             glm::vec2(this->width, this->height));
        this->levels[this->level].draw(*renderer);
        player->draw(*renderer);
        std::stringstream sLevel;
        sLevel << this->level;
        Text->renderText("level:" + sLevel.str(), 5.0f, 5.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        std::stringstream sFps;
        sFps << this->fps;
        Text->renderText("fps:" + sFps.str(), 5.0f, 30.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        Text->renderText("The number of death: " + sDeathNumber.str(), 500.0f, 5.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    if (this->state == GAME_MENU) {
        ResourceManager::getShader("sprite").use();
        renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0, 0),
                             glm::vec2(this->width, this->height));
        Text->renderText("Press ENTER to start", 250.0f, height / 2, 1.0f);
    }

    if (this->state == GAME_WIN) {
        ResourceManager::getShader("sprite").use();
        renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0, 0),
                             glm::vec2(this->width, this->height));
        Text->renderText("You win!", 250.0f, height / 2, 1.0f);
        Text->renderText("The number of death: " + sDeathNumber.str(), 250.0f, height / 2 - 30.0f, 1.0f,
                         glm::vec3(0.0f, 0.0f, 1.0f));
        Text->renderText("Press R to restart ", 250.0f, height / 2 - 60.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    }
}

Direction VectorDirection(GameObject &one, GameObject &two) {
    GLuint best_match = -1;
    if ((one.position.y + one.size.y - 5) < two.position.y)
        best_match = UP;
    else if (one.position.y > (two.position.y + two.size.y - 5))
        best_match = DOWN;
    else if (one.position.x > two.position.x)
        best_match = RIGHT;
    else if (one.position.x < two.position.x)
        best_match = LEFT;
    return (Direction) best_match;
}

Collision checkCollision(GameObject &one, GameObject &two) {
    // X 轴
    bool collisionX = one.position.x + one.size.x >= two.position.x &&
                      two.position.x + two.size.x >= one.position.x;
    // Y轴
    bool collisionY = one.position.y + one.size.y >= two.position.y &&
                      two.position.y + two.size.y >= one.position.y;

    if (collisionX && collisionY) {
        glm::vec2 difference = two.position - one.position;
        return std::make_tuple(GL_TRUE, VectorDirection(one, two), difference);
    } else
        return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
}

void Game::reset() {
    if (this->level == 0)this->levels[0].load("levels/one.lvl", this->width, this->height * 0.5f);
    else if (this->level == 1)
        this->levels[1].load("levels/two.lvl", this->width, this->height * 0.5f);
    else if (this->level == 2)
        this->levels[2].load("levels/three.lvl", this->width, this->height * 0.5f);

}

void Game::doCollisions() {
    player->isJumped = GL_FALSE;
    //使 player 与每个对象进行碰撞检测
    for (GameObject &box : this->levels[this->level].bricks) {
        Collision collision = checkCollision(*player, box);
        //有碰撞时，并根据不同情况进行处理
        if (std::get<0>(collision)) {
            if (box.type == BRICK) {
                if (player->position.y == 0) {
                    this->deathNumber++;
                    reset();
                    player->position = this->levels[level].pos;
                    return;
                }
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == UP) {
                    player->velocity.y = 0;
                    player->position.y = box.position.y - player->size.y - 0.1f;
                    player->isJumped = GL_TRUE;
                }
                if (dir == DOWN) {
                    if (player->velocity.y < 0)
                        player->velocity.y = 0;
                }
                if (dir == RIGHT) {
                    if (player->velocity.x < 0)
                        player->velocity.x = 0;
                    player->position.x = box.position.x + box.size.x + 0.1f;
                }
                if (dir == LEFT) {
                    if (player->velocity.x > 0)
                        player->velocity.x = 0;
                    player->position.x = box.position.x - player->size.x - 0.1f;
                }
            }
            //到达终点时
            if (box.type == END) {
                this->level++;
                if (this->level >= this->levels.size()) {
                    state = GAME_WIN;
                    this->level = 0;
                }
                reset();
                player->position = this->levels[level].pos;
            }
        }
    }

}

