#include "Game.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

TextRenderer* text;
ISoundEngine* sound = irrklang::createIrrKlangDevice();

GameObject* map;

void Game::Init()
{
    LoadResources();

    // tools
    projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    text = new TextRenderer(this->width, this->height);
    text->Load("../fonts/Garamond.ttf", 24);
    cursorPos = glm::vec2(this->width / 2.0f - 50.0f, this->height / 2.0f);

    // background/map
    map = new GameObject(glm::vec2(0.0f, 80.0f), glm::vec2(this->width, this->height - 80.0f));
    map->SetTexture(ResourceManager::GetTexture("map"));

    // game objects
}

void Game::InitGrid()
{
    grid.resize(11, std::vector<glm::vec2>(13, glm::vec2()));

    ceilWidth = this->width * 0.065f;
    ceilHeight = this->height * 0.065f;

    float paddingX = this->width * 0.93f;

    for (int i = 0; i < 11; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            grid[i][j] = glm::vec2();
        }
    }
}

void Game::LoadResources()
{
    ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "spriteShader");

    // sprites
    ResourceManager::LoadTexture("../textures/map/map.png", false, "map");
    ResourceManager::LoadTexture("../textures/map/stone.png", true, "stone");
    ResourceManager::LoadTexture("../textures/map/brick.png", true, "brick");
}

void Game::Menu()
{
    text->RenderText("MENU", glm::vec2(this->width / 2.0f - 65.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

    text->RenderText("Start", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
    text->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));

    text->RenderText("->", glm::vec2(cursorPos), 1.0f, glm::vec3(1.0f));
}

void Game::ProcessInput(float dt)
{
    if (gmState == ACTIVE) {
        if (this->Keys[GLFW_KEY_SPACE]) gmState = PAUSED;
    }
    else {
        if (this->Keys[GLFW_KEY_UP] && !this->KeysProcessed[GLFW_KEY_UP] && cursorPos.y > this->height / 2.0f) {
            cursorPos.y -= 40.0f;
            this->KeysProcessed[GLFW_KEY_UP] = true;
        }
        else if (this->Keys[GLFW_KEY_DOWN] && !this->KeysProcessed[GLFW_KEY_DOWN] && cursorPos.y < this->height / 2.0f + 40.0f) {
            cursorPos.y += 40.0f;
            this->KeysProcessed[GLFW_KEY_DOWN] = true;
        }
        else if (this->Keys[GLFW_KEY_ENTER]) {
            if (cursorPos.y == this->height / 2.0f) gmState = ACTIVE;
            else if (cursorPos.y == this->height / 2.0f + 40.0f) close = true;
        }
    }
}

void Game::Update(float dt)
{
    if (gmState == ACTIVE) {

        // actions

        // update borders after position changes

        // interactions
    }
}

void Game::Render()
{
    // background/map/stats
    DrawObject(map);

    if (gmState == ACTIVE) {
        // game objects
    }
    else {
        Menu();
    }

}

void Game::DrawObject(GameObject* obj)
{
    ResourceManager::GetShader("spriteShader").Use();
    ResourceManager::GetShader("spriteShader").SetMatrix4("projection", projection);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(obj->GetPos(), 1.0f));

    model = glm::translate(model, glm::vec3(0.5f * obj->GetSize().x, 0.5f * obj->GetSize().y, 0.0f));
    model = glm::rotate(model, glm::radians(obj->GetAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * obj->GetSize().x, -0.5f * obj->GetSize().y, 0.0f));

    model = glm::scale(model, glm::vec3(obj->GetSize(), 1.0f));

    ResourceManager::GetShader("spriteShader").SetMatrix4("model", model);
    ResourceManager::GetShader("spriteShader").SetVector3f("spriteColor", obj->GetColor());

    if (gmState != ACTIVE) ResourceManager::GetShader("spriteShader").SetBool("menu", true);
    else ResourceManager::GetShader("spriteShader").SetBool("menu", false);

    obj->DrawObject();
}

Game::~Game()
{
    delete text;
    delete sound;

    for (auto i : objList)
    {
        delete i;
    }
    objList.clear();
    // -----
}
