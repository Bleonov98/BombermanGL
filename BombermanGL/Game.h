#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <thread>

#include "TextRenderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Brick.h"
#include "Bonus.h"
#include "Portal.h"

#include "Bomb.h"
#include "Explosion.h"

#include "CharacterObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Onion.h"
#include "Blob.h"
#include "Bear.h"

enum GameState {
	MENU,
	ACTIVE,
	END
};

class Game
{
public:

	Game(const int width, const int height) {
		this->width = width, this->height = height;
	}

	// Init
	void Init();
	void InitGrid();

	void InitGameObjects();
	void InitBricks();
	void GenerateLevel();

	void LoadResources();

	// Main functions
	void Menu(bool end);

	void ProcessInput(float dt);
	void Update(float dt);

	void Render();
	void DrawObject(GameObject* obj);
	void DrawStats();
	void Timer();

	void CheckCollisions(float dt);
	void ProcessAnimations(float dt);

	// game

	void ProcessBomb();
	void ProcessExplosion(glm::vec2 bombPosition);

	void SpawnEnemies();
	void SpawnBonus(glm::vec2 position);
	void SpawnPortal();

	void ClearGameData();
	void RestartGameData(bool levelUp);

	// calculations
	glm::vec2 FindNearestCell(GameObject* object);
	glm::vec2 GetFreeRandomCell();
	std::pair<int, int> GetGridPos(GameObject* object);

	// pub vars
	bool Keys[1024], KeysProcessed[1024], close = false;

	// delete, destruct
	void DeleteObjects();

	template <typename T>
	void DeleteObjectFromVector(std::vector<T*>& vector, bool deleteMemory);

	~Game();

private:

	glm::mat4 projection;
	
	// object vectors
	std::vector<GameObject*> objList;

	std::vector<CharacterObject*> characterList;
	std::vector<Enemy*> enemyList;

	std::vector<Brick*> brickList;
	std::vector<Bonus*> bonusList;
	std::vector<Bomb*> bombList;
	std::vector<Explosion*> explosionList;

	int width, height, timeCount = 240;
	float seconds = 0.0f;
	float cellWidth, cellHeight;
	std::vector<std::vector<int>> mData;
	std::vector<std::vector<glm::vec2>> grid;
	int level = 1;
	bool showBonus = false, win = false;

	glm::vec2 cursorPos;

	GameState gmState = MENU;
};

#endif // !GAME_H