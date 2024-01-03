#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TextRenderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Brick.h"

enum GameState {
	MENU,
	ACTIVE,
	PAUSED
};

class Game
{
public:

	Game(const int width, const int height) {
		this->width = width, this->height = height;
	}

	// basics
	void Init();
	void InitGrid();

	void InitGameObjects();
	void InitBricks();

	void LoadResources();

	void Menu();

	void ProcessInput(float dt);
	void Update(float dt);

	void Render();
	void DrawObject(GameObject* obj);
	//void DrawStats();

	// game

	// pub vars
	bool Keys[1024], KeysProcessed[1024], close = false;

	~Game();

private:

	glm::mat4 projection;

	std::vector<GameObject*> objList;
	std::vector<Brick*> brickList;

	int width, height;

	float ceilWidth, ceilHeight;
	glm::vec2 ceilPos;
	std::vector<int> mData;
	std::vector<std::vector<glm::vec2>> grid;

	glm::vec2 cursorPos;

	GameState gmState = MENU;
};

#endif // !GAME_H