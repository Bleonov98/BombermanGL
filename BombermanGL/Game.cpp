#include "Game.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

TextRenderer* text;
ISoundEngine* sound = irrklang::createIrrKlangDevice();

GameObject* map;

Player* player;

// - - - - - Init functions

void Game::Init()
{
    srand(time(NULL));
    LoadResources();

    // tools
    projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    text = new TextRenderer(this->width, this->height); 
    text->Load("../fonts/Garamond.ttf", 24);
    cursorPos = glm::vec2(this->width / 2.0f - 50.0f, this->height / 2.0f);

    // background/map
    map = new GameObject(glm::vec2(0.0f, 80.0f), glm::vec2(this->width, this->height - 80.0f));
    map->SetTexture(ResourceManager::GetTexture("map"));

    InitGrid();
    InitGameObjects();
}

void Game::InitGrid()
{
    grid.resize(11, std::vector<glm::vec2>(13, glm::vec2(0.0f, 0.0f)));
    mData.resize(11, std::vector<int>(13, 0));

    ceilWidth = this->width * 0.063f;
    ceilHeight = this->height * 0.07f;

    float paddingX = this->width * 0.09f;

    for (int i = 0; i < 11; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            grid[i][j] = glm::vec2(paddingX + j * ceilWidth, 82.0f + ceilHeight + i * ceilHeight);
        } 
    }
}

void Game::InitGameObjects()
{
    InitBricks();
    GenerateLevel();

    player = new Player(grid[0][0], glm::vec2(ceilWidth - 10.0f, ceilHeight - 5.0f), 180.0f);
    objList.push_back(player);
    characterList.push_back(player);
}

void Game::InitBricks()
{
    Brick* brick;

    // solid bricks
    for (int i = 0; i < grid.size(); ++i)
    {
        if (i % 2 == 0) continue;
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (j % 2 == 0) continue;

            brick = new Brick(grid[i][j], glm::vec2(ceilWidth, ceilHeight), BRICK_SOLID);
            objList.push_back(brick);
            brickList.push_back(brick);

            mData[i][j] = 99;
        }
    }
}

void Game::GenerateLevel()
{
    Brick* brick;

    for (int i = 0; i < mData.size(); i++)
    {
        for (int j = 0; j < mData[i].size(); j++)
        {
            if (((i == 0 || i == 1) && (j == 0 || j == 1)) || mData[i][j] != 0) continue;

            mData[i][j] = rand() % 2;

            if (mData[i][j] == 1) {
                brick = new Brick(grid[i][j], glm::vec2(ceilWidth, ceilHeight), BRICK_COMMON);
                objList.push_back(brick);
                brickList.push_back(brick);
            }
        }
    }

    brickList[rand() % brickList.size()]->SetBrickBonus();
}

void Game::LoadResources()
{
    ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "spriteShader");

    // sprites
    
    // - - - map, bricks
    ResourceManager::LoadTexture("map/map.png", false, "map");
    ResourceManager::LoadTexture("map/stone.png", false, "stone");
    ResourceManager::LoadTexture("map/brick.png", false, "brick");

    // - - - bonuses
    ResourceManager::LoadTexture("bonuses/bonus_fire.png", false, "bonus_fire");
    ResourceManager::LoadTexture("bonuses/bonus_life.png", false, "bonus_life");
    ResourceManager::LoadTexture("bonuses/bonus_speed.png", false, "bonus_speed");
    ResourceManager::LoadTexture("bonuses/bonus_bomb.png", false, "bonus_bomb");
    ResourceManager::LoadTexture("bonuses/bonus_jacket.png", false, "bonus_jacket");

    // - - - player
    ResourceManager::LoadTexture("player/player_down_0.png", true, "player_down_0");
    ResourceManager::LoadTexture("player/player_down_1.png", true, "player_down_1");
    ResourceManager::LoadTexture("player/player_down_2.png", true, "player_down_2");

    ResourceManager::LoadTexture("player/player_up_0.png", true, "player_up_0");
    ResourceManager::LoadTexture("player/player_up_1.png", true, "player_up_1");
    ResourceManager::LoadTexture("player/player_up_2.png", true, "player_up_2");

    ResourceManager::LoadTexture("player/player_left_0.png", true, "player_left_0");
    ResourceManager::LoadTexture("player/player_left_1.png", true, "player_left_1");
    ResourceManager::LoadTexture("player/player_left_2.png", true, "player_left_2");

    ResourceManager::LoadTexture("player/player_right_0.png", true, "player_right_0");
    ResourceManager::LoadTexture("player/player_right_1.png", true, "player_right_1");
    ResourceManager::LoadTexture("player/player_right_2.png", true, "player_right_2");

    ResourceManager::LoadTexture("player/player_death_0.png", true, "player_death_0");
    ResourceManager::LoadTexture("player/player_death_1.png", true, "player_death_1");
    ResourceManager::LoadTexture("player/player_death_2.png", true, "player_death_2");
    ResourceManager::LoadTexture("player/player_death_3.png", true, "player_death_3");
    ResourceManager::LoadTexture("player/player_death_4.png", true, "player_death_4");
}

// - - - - - Main functions

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

        if (this->Keys[GLFW_KEY_W]) player->Move(dt, CHAR_MOVEUP);
        else if (this->Keys[GLFW_KEY_A]) player->Move(dt, CHAR_MOVELEFT);
        else if (this->Keys[GLFW_KEY_S]) player->Move(dt, CHAR_MOVEDOWN);
        else if (this->Keys[GLFW_KEY_D]) player->Move(dt, CHAR_MOVERIGHT);
        else player->Move(dt, CHAR_STAND);

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

        for (auto i : characterList)
        {
            i->UpdateAABB();
        }

        // interactions
        CheckCollisions();
    }
}

void Game::Render()
{
    // background/map/stats
    DrawObject(map);
    
    for (auto i : brickList)
    {
        DrawObject(i);
    }

    DrawObject(player);

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

void Game::CheckCollisions()
{
    // map/bricks collision
    for (auto character : characterList)
    {
        for (auto brick : brickList)
        {
            character->ProcessCollision(*brick);
        }
    }
}

// - - - - - Others

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

    brickList.clear();
    characterList.clear();
}
