#pragma once
#include "GameObject.h"
class Bomb : public GameObject
{
public:

	Bomb(glm::vec2 position, glm::vec2 size, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) { 
		SetTexture(ResourceManager::GetTexture("bomb"));
	};

private:



};

