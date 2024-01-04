#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

enum BrickType {
	SOLID,
	COMMON
};

enum BrickBonus {
	FIRE,
	BOMB,
	SPEED,
	LIFE,
	NONE
};

class Brick : public GameObject
{
public:

	Brick(glm::vec2 position, glm::vec2 size, BrickType type, BrickBonus bonusType, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->brickType = type;
		this->brickBonus = bonusType;

		if (type == SOLID) SetTexture(ResourceManager::GetTexture("stone"));
		else if (type == COMMON) SetTexture(ResourceManager::GetTexture("brick"));
	};

	BrickType GetBrickType() { return brickType; }
	BrickBonus GetBrickBonus() { return brickBonus; }

private:

	BrickType brickType;
	BrickBonus brickBonus;

};

#endif // !BRICK_H



