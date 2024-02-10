#include "Game.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

TextRenderer* text;
ISoundEngine* sound = irrklang::createIrrKlangDevice();
ISoundSource* music;

GameObject* map;
GameObject* field;
GameObject* stats;

Player* player;
Portal* portal;

// - - - - - Init functions

void Game::Init()
{
    srand(time(NULL));
    LoadResources();

    // sounds
    music = sound->addSoundSourceFromFile("../sounds/music.mp3");
    music->setDefaultVolume(0.5f);

    sound->play2D(music, true);

    // tools
    projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    text = new TextRenderer(this->width, this->height); 
    text->Load("../fonts/Garamond.ttf", 24);
    cursorPos = glm::vec2(this->width / 2.0f - 50.0f, this->height / 2.0f);

    // background/map
    map = new GameObject(glm::vec2(0.0f, 80.0f), glm::vec2(this->width, this->height - 80.0f));
    map->SetTexture(ResourceManager::GetTexture("map"));
    field = new GameObject(glm::vec2(0.0f, 80.0f), glm::vec2(this->width, this->height - 80.0f));
    field->SetTexture(ResourceManager::GetTexture("field"));
    stats = new GameObject(glm::vec2(0.0f, 0.0f), glm::vec2(this->width, 80.0f));
    stats->SetTexture(ResourceManager::GetTexture("stats"));

    InitGrid();
    InitGameObjects();

    player = new Player(grid[0][0], glm::vec2(cellWidth, cellHeight + 20.0f), 180.0f);
    objList.push_back(player);
    characterList.push_back(player);
}

void Game::InitGrid()
{
    grid.resize(11, std::vector<glm::vec2>(13, glm::vec2(0.0f, 0.0f)));
    mData.resize(11, std::vector<int>(13, 0));

    cellWidth = this->width * 0.063f;
    cellHeight = this->height * 0.07f;

    float paddingX = this->width * 0.09f;

    for (int i = 0; i < 11; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            grid[i][j] = glm::vec2(paddingX + j * cellWidth, 82.0f + cellHeight + i * cellHeight);
        } 
    }
}

void Game::InitGameObjects()
{
    InitBricks();
    GenerateLevel();
    SpawnEnemies();
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

            brick = new Brick(grid[i][j], glm::vec2(cellWidth, cellHeight), BRICK_SOLID);
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
                brick = new Brick(grid[i][j], glm::vec2(cellWidth, cellHeight), BRICK_COMMON);
                objList.push_back(brick);
                brickList.push_back(brick);
            }
        }
    }

    for (int i = 0; i < 2;)
    {
        int randNum = rand() % brickList.size();
        if (!brickList[randNum]->IsBonusBrick() && brickList[randNum]->GetBrickType() == BRICK_COMMON) brickList[randNum]->SetBrickBonus(), i++;
    }
    
}

void Game::LoadResources()
{
    ResourceManager::LoadShader("../shaders/vShader.vx", "../shaders/fShader.ft", "spriteShader");

    // sprites
    
    // - - - map, bricks
    ResourceManager::LoadTexture("map/map.png", true, "map");
    ResourceManager::LoadTexture("map/field.png", true, "field");
    ResourceManager::LoadTexture("map/stone.png", true, "stone");
    ResourceManager::LoadTexture("map/portal.png", true, "portal");
    ResourceManager::LoadTexture("map/stats.png", true, "stats");

    ResourceManager::LoadTexture("map/brick.png", false, "brick");
    ResourceManager::LoadTexture("map/brick_0.png", true, "brick_0");
    ResourceManager::LoadTexture("map/brick_1.png", true, "brick_1");
    ResourceManager::LoadTexture("map/brick_2.png", true, "brick_2");
    ResourceManager::LoadTexture("map/brick_3.png", true, "brick_3");
    ResourceManager::LoadTexture("map/brick_4.png", true, "brick_4");

    // - - - bonuses
    ResourceManager::LoadTexture("bonuses/bonus_fire.png", true, "bonus_fire");
    ResourceManager::LoadTexture("bonuses/bonus_life.png", true, "bonus_life");
    ResourceManager::LoadTexture("bonuses/bonus_speed.png", true, "bonus_speed");
    ResourceManager::LoadTexture("bonuses/bonus_bomb.png", true, "bonus_bomb");
    ResourceManager::LoadTexture("bonuses/bonus_jacket.png", true, "bonus_jacket");

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

    // - - - bomb
    ResourceManager::LoadTexture("bomb/bomb.png", true, "bomb");

    ResourceManager::LoadTexture("bomb/explosion_0.png", true, "explosion_0");
    ResourceManager::LoadTexture("bomb/explosion_1.png", true, "explosion_1");
    ResourceManager::LoadTexture("bomb/explosion_2.png", true, "explosion_2");
    ResourceManager::LoadTexture("bomb/explosion_3.png", true, "explosion_3");

    // - - - onion
    ResourceManager::LoadTexture("onion/onion_0.png", true, "onion_0");
    ResourceManager::LoadTexture("onion/onion_1.png", true, "onion_1");
    ResourceManager::LoadTexture("onion/onion_2.png", true, "onion_2");
    ResourceManager::LoadTexture("onion/onion_death_0.png", true, "onion_death_0");
    ResourceManager::LoadTexture("onion/onion_death_1.png", true, "onion_death_1");

    // - - - blob
    ResourceManager::LoadTexture("blob/blob_0.png", true, "blob_0");
    ResourceManager::LoadTexture("blob/blob_1.png", true, "blob_1");
    ResourceManager::LoadTexture("blob/blob_2.png", true, "blob_2");
    ResourceManager::LoadTexture("blob/blob_death_0.png", true, "blob_death_0");
    ResourceManager::LoadTexture("blob/blob_death_1.png", true, "blob_death_1");
    ResourceManager::LoadTexture("blob/blob_death_2.png", true, "blob_death_2");
    ResourceManager::LoadTexture("blob/blob_death_3.png", true, "blob_death_3");

    // - - - bear
    ResourceManager::LoadTexture("bear/bear_0.png", true, "bear_0");
    ResourceManager::LoadTexture("bear/bear_1.png", true, "bear_1");
    ResourceManager::LoadTexture("bear/bear_2.png", true, "bear_2");
    ResourceManager::LoadTexture("bear/bear_death_0.png", true, "bear_death_0");
    ResourceManager::LoadTexture("bear/bear_death_1.png", true, "bear_death_1");

}

// - - - - - Main functions

void Game::Menu(bool end)
{
    if (end) {
        if (win) text->RenderText("YOU'VE WON!", glm::vec2(this->width / 2.0f - 125.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));
        else text->RenderText("YOU'VE LOST!", glm::vec2(this->width / 2.0f - 135.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

        text->RenderText("PRESS ENTER TO EXIT", glm::vec2(this->width / 2.0f - 140.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));
    }
    else {
        text->RenderText("MENU", glm::vec2(this->width / 2.0f - 65.0f, this->height / 2.0f - 116.0f), 1.75f, glm::vec3(0.75f));

        text->RenderText("Start", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f), 1.0f, glm::vec3(1.0f));
        text->RenderText("Exit", glm::vec2(this->width / 2.0f - 20.0f, this->height / 2.0f + 40.0f), 1.0f, glm::vec3(1.0f));

        text->RenderText("->", glm::vec2(cursorPos), 1.0f, glm::vec3(1.0f));
    }
}

void Game::ProcessInput(float dt)
{
    if (gmState == ACTIVE) {

        if (!player->IsDead()) {
            if (this->Keys[GLFW_KEY_W]) player->Move(dt, CHAR_MOVEUP);
            else if (this->Keys[GLFW_KEY_A]) player->Move(dt, CHAR_MOVELEFT);
            else if (this->Keys[GLFW_KEY_S]) player->Move(dt, CHAR_MOVEDOWN);
            else if (this->Keys[GLFW_KEY_D]) player->Move(dt, CHAR_MOVERIGHT);
            else player->Move(dt, CHAR_STAND);
        }

        if (this->Keys[GLFW_KEY_SPACE] && !KeysProcessed[GLFW_KEY_SPACE] && player->IsReloaded()) {
            ProcessBomb();
            KeysProcessed[GLFW_KEY_SPACE] = true;
        }

        if (this->Keys[GLFW_KEY_M] && !KeysProcessed[GLFW_KEY_M]) {
            gmState = MENU;
            KeysProcessed[GLFW_KEY_M] = true;
        }
    }
    else if (gmState == MENU) {
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
            else if (cursorPos.y == this->height / 2.0f + 40.0f);
        }
    }
    else if (gmState == END && this->Keys[GLFW_KEY_ENTER]) close = true;
}

void Game::Update(float dt)
{
    if (gmState == ACTIVE) {

        Timer();
        if (timeCount == 0) player->Kill();

        // actions
        for (auto i : bombList)
        {
            if (i->Exploded()) {
                ProcessExplosion(i->GetPos());
                i->DeleteObject();
                sound->play2D("../sounds/explosion.wav");
            }
        }

        for (auto i : enemyList)
        {
            if (i->IsDead()) continue;

            if (i->GetMoveType() == ALGORITHM) i->FindTarget(mData, grid, FindNearestCell(i), FindNearestCell(player));

            if (i->ChangePositionTime()) {
                i->ResetChangeTime();
                i->ChangePosition(mData, GetGridPos(i));
            }

            i->Move(dt);
        }

        ProcessAnimations(dt);

        for (auto i : characterList)
        {
            i->UpdateAABB();
        }

        // interactions
        CheckCollisions(dt);

        // Game Conditions
        if (!player->IsDead() && player->IsRespawned()) {
            ClearGameData();
            RestartGameData(0);
            player->Spawn();
        }
        else if (player->IsDead() && player->IsOver()) win = false, gmState = END;
            
        if (enemyList.empty() && !showBonus) {
            SpawnPortal();
            showBonus = true;
        }

        // deleting objects if they're done
        DeleteObjects();
    }
}

void Game::Render()
{
    // background/map/stats
    DrawObject(field);
    DrawObject(stats);
    if (portal != nullptr) DrawObject(portal);
    
    for (auto i : explosionList)
    {
        DrawObject(i);
    }
    DrawObject(map);

    for (auto i : brickList)
    {
        DrawObject(i);
    }

    for (auto i : bonusList)
    {
        DrawObject(i);
    }

    for (auto i : bombList)
    {
        DrawObject(i);
    }

    for (auto i : characterList)
    {
        DrawObject(i);
    }

    DrawStats();

    if (gmState == MENU) Menu(false);
    else if (gmState == END) Menu(true);
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

void Game::DrawStats()
{
    text->RenderText(std::to_string(player->GetScore()), glm::vec2(450.0f, 30.0f), 1.0f);
    text->RenderText(std::to_string(player->GetLifes()), glm::vec2(975.0f, 30.0f), 1.0f);

    text->RenderText(std::to_string(timeCount % 60), glm::vec2(785.0f, 30.0f), 1.0f);
    text->RenderText(std::to_string(static_cast<int>(std::floor(timeCount / 60))), glm::vec2(685.0f, 30.0f), 1.0f);
}

void Game::Timer()
{
    std::time_t currentTime = std::time(nullptr);

    std::tm timeinfo;
    localtime_s(&timeinfo, &currentTime);

    float newSeconds = static_cast<float>(timeinfo.tm_sec);

    if (newSeconds > seconds) timeCount--;
    seconds = newSeconds;
}

void Game::CheckCollisions(float dt)
{
    // map/bricks collisions
        // Enemies
    for (auto enemy : enemyList)
    {
        for (auto brick : brickList)
        {
            if (enemy->ProcessCollision(*brick, dt)) enemy->ChangePosition(mData, GetGridPos(enemy));
        }

        for (auto bomb : bombList)
        {
            if (enemy->ProcessCollision(*bomb, dt)) enemy->ChangePosition(mData, GetGridPos(enemy));
        }

        if (enemy->ProcessMapCollision(dt)) enemy->ChangePosition(mData, GetGridPos(enemy));
    }
        // - - - - - -

        // Player collision
    player->ProcessMapCollision(dt);

    for (auto brick : brickList)
    {
        player->ProcessCollision(*brick, dt);
    }

    for (auto bomb : bombList)
    {
        player->ProcessCollision(*bomb, dt);
    }

    for (auto bonus : bonusList)
    {
        if (player->ObjectCollision(*bonus)) {
            player->ProcessBonus(bonus->GetBonusType());
            bonus->DeleteObject();
            sound->play2D("../sounds/item.wav");
        }
    }

    for (auto enemy : enemyList)
    {
        if (player->EnemyCollision(*enemy) && !player->IsDead()) player->Kill();
    }

    if (portal != nullptr && player->ObjectCollision(*portal)) {
        ClearGameData();
        RestartGameData(1);
    }
        // - - - - - - - - -

    // explosion collision
    for (auto i : explosionList)
    {
        for (auto brick : brickList)
        {
            if (i->ExplosionCollision(*brick) && brick->GetBrickType() == BRICK_COMMON && !brick->IsDestroyed()) {
                brick->DestroyBrick();
                if (brick->IsBonusBrick()) SpawnBonus(brick->GetPos());
            }
        }

        for (auto character : characterList)
        {
            if (i->ExplosionCollision(*character) && !character->IsDead()) character->Kill(), player->AddScore();
        }

        for (auto bomb : bombList)
        {
            if (i->ExplosionCollision(*bomb) && !bomb->Exploded()) {
                player->Reload();
                bomb->Explode();
            }
        }
    }
    // - - - - - - - - - - - 
}

void Game::ProcessAnimations(float dt)
{
    for (auto i : brickList)
    {
        if (i->IsDestroyed()) i->DestroyAnimation(dt);
    }

    for (auto i : bombList)
    {
        i->BombAnimation(dt);
    }

    for (auto i : explosionList)
    {
        i->ExplosionAnimation(dt);
    }
    
    for (auto i : characterList)
    {
        if (i->IsDead()) i->DeathAnimation(dt);
    }

    if (showBonus) {
        for (auto i : brickList)
        {
            if (i->IsBonusBrick()) i->BlinkAnimation(dt);
        }
    }
        
}

// - - - - - Game 

void Game::ProcessBomb()
{
    player->PlaceBomb();

    // add object
    Bomb* bomb = new Bomb(FindNearestCell(player), glm::vec2(cellWidth - 5.0f, cellHeight - 5.0f));
    objList.push_back(bomb);
    bombList.push_back(bomb);

    std::pair<int, int> gridPos = GetGridPos(bomb);

    std::thread bombDelay([&, bomb, gridPos]() {
        mData[gridPos.first][gridPos.second] = 99;

        std::this_thread::sleep_for(std::chrono::duration<float>(bomb->GetExplodeDelay()));

        if (bomb->Exploded()) {
            mData[gridPos.first][gridPos.second] = 0;
            return;
        }

        player->Reload();
        bomb->Explode();
        mData[gridPos.first][gridPos.second] = 0;
    });
    bombDelay.detach();
}

void Game::ProcessExplosion(glm::vec2 bombPosition)
{
    glm::vec2 explosionSize = glm::vec2(cellWidth, cellHeight) * static_cast<float>(player->GetExplosionRange() * 1.5f);
    glm::vec2 explosionPosition = glm::vec2(bombPosition.x - explosionSize.x * 0.5f + cellWidth * 0.5f, bombPosition.y - explosionSize.y * 0.5f + cellHeight * 0.5f);

    Explosion* explosion = new Explosion(explosionPosition, explosionSize, player->GetExplosionRange());
    explosion->SetAABB(mData, grid, bombPosition);
    objList.push_back(explosion);
    explosionList.push_back(explosion);

    std::thread explosionTh([&, explosion]() {
        std::this_thread::sleep_for(std::chrono::duration<float>(explosion->GetExplosionDuration()));
        explosion->DeleteObject();
    });
    explosionTh.detach();
}

void Game::SpawnEnemies()
{
    Onion* onion;
    Blob* blob;
    Bear* bear;

    if (level == 1) {
        for (int i = 0; i < 3; ++i)
        {
            onion = new Onion(GetFreeRandomCell() + glm::vec2(5.0f), glm::vec2(cellWidth, cellHeight) - glm::vec2(10.0f), 150.0f);
            objList.push_back(onion);
            characterList.push_back(onion);
            enemyList.push_back(onion);
        }
    }
    else if (level == 2) {
        for (int i = 0; i < 2; ++i)
        {
            onion = new Onion(GetFreeRandomCell() + glm::vec2(5.0f), glm::vec2(cellWidth, cellHeight) - glm::vec2(10.0f), 150.0f);
            objList.push_back(onion);
            characterList.push_back(onion);
            enemyList.push_back(onion);
        }

        blob = new Blob(GetFreeRandomCell() + glm::vec2(5.0f), glm::vec2(cellWidth, cellHeight) - glm::vec2(10.0f), 150.0f);
        objList.push_back(blob);
        characterList.push_back(blob);
        enemyList.push_back(blob);
    }
    else if (level == 3) {
        onion = new Onion(GetFreeRandomCell() + glm::vec2(5.0f), glm::vec2(cellWidth, cellHeight) - glm::vec2(10.0f), 150.0f);
        objList.push_back(onion);
        characterList.push_back(onion);
        enemyList.push_back(onion);

        blob = new Blob(GetFreeRandomCell() + glm::vec2(5.0f), glm::vec2(cellWidth, cellHeight) - glm::vec2(10.0f), 150.0f);
        objList.push_back(blob);
        characterList.push_back(blob);
        enemyList.push_back(blob);

        bear = new Bear(GetFreeRandomCell() + glm::vec2(5.0f), glm::vec2(cellWidth, cellHeight) - glm::vec2(10.0f), 200.0f);
        objList.push_back(bear);
        characterList.push_back(bear);
        enemyList.push_back(bear);
    }
    



}

void Game::SpawnBonus(glm::vec2 position)
{
    static int bonusCnt = 0;

    Bonus* bonus = new Bonus(position, glm::vec2(cellWidth - 5.0f, cellHeight - 5.0f), static_cast<BonusType>(bonusCnt));
    objList.push_back(bonus);
    bonusList.push_back(bonus);

    bonusCnt++;
}

void Game::SpawnPortal()
{
    portal = new Portal(grid[0][0], glm::vec2(cellWidth, cellHeight));
    objList.push_back(portal);
}

void Game::ClearGameData()
{
    for (auto i : objList)
    {
        if (i != player) i->DeleteObject();
    }

    DeleteObjects();

    portal = nullptr;
    showBonus = false;
}

void Game::RestartGameData(bool levelUp)
{
    if (levelUp && level < 3) level++;
    else if (levelUp && level >= 3) gmState = END, win = true;

    mData.assign(11, std::vector<int>(13, 0));
    InitGameObjects();
    timeCount = 240;
}

glm::vec2 Game::FindNearestCell(GameObject* object)
{
    glm::vec2 nearestCell;
    float minLength = 0.0f;
    bool firstCheck = true;

    for (auto i : grid)
    {
        for (auto j : i)
        {
            glm::vec2 diffVec = abs((object->GetPos() + object->GetSize() / 3.5f) - j);
            float diffLength = sqrt(powf(diffVec.x, 2) + powf(diffVec.y, 2));

            if (firstCheck) {
                minLength = diffLength;
                firstCheck = false;
                nearestCell = j;
            }
            else if (diffLength < minLength) {
                minLength = diffLength;
                nearestCell = j;
            }

        }
    }

    return nearestCell;
}

glm::vec2 Game::GetFreeRandomCell()
{
    int row = rand() % 11, col = rand() % 13;
    glm::vec2 freeCell;

    while (true) {
        row = rand() % 11, col = rand() % 13;
        if (mData[row][col] == 0 && (row + col > 2)) {
            freeCell = grid[row][col];
            break;
        }
    }

    return freeCell;
}

std::pair<int, int> Game::GetGridPos(GameObject* object)
{
    glm::vec2 nearestCell = FindNearestCell(object);

    int row = 0, col = 0;

    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == nearestCell) row = i, col = j;
        }
    }

    return std::pair<int, int>(std::make_pair(row, col));
}

// - - - - - Others

void Game::DeleteObjects()
{
    DeleteObjectFromVector(characterList, false);
    DeleteObjectFromVector(enemyList, false);

    DeleteObjectFromVector(brickList, false);
    DeleteObjectFromVector(bonusList, false);
    DeleteObjectFromVector(bombList, false);
    DeleteObjectFromVector(explosionList, false);

    DeleteObjectFromVector(objList, true);
}

template <typename T>
void Game::DeleteObjectFromVector(std::vector<T*>& vector, bool deleteMemory)
{
    for (auto i = vector.begin(); i != vector.end();)
    {
        if ((*i)->IsDeleted()) {
            if (deleteMemory) delete* i;
            i = vector.erase(i);
        }
        else ++i;
    }
}

Game::~Game()
{
    delete text;
    delete sound;
    delete map;
    delete field;

    for (auto i : objList)
    {
        delete i;
    }
    objList.clear();
    // -----

    characterList.clear();
    enemyList.clear();
    bonusList.clear();
    bombList.clear();
    brickList.clear(); 
    explosionList.clear();
}

// stats, fix;
