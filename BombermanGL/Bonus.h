#ifndef BONUS_H
#define BONUS_H

#include "GameObject.h"

enum BonusType {
	BONUS_FIRE,
	BONUS_BOMB,
	BONUS_SPEED,
	BONUS_LIFE
};

class Bonus : public GameObject
{
public:

	Bonus(glm::vec2 position, glm::vec2 size, BonusType type, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->bonusType = type;

		if (type == BONUS_FIRE) SetTexture(ResourceManager::GetTexture("stone"));
		else if (type == BONUS_BOMB) SetTexture(ResourceManager::GetTexture("brick"));
		else if (type == BONUS_SPEED) SetTexture(ResourceManager::GetTexture("brick"));
		else if (type == BONUS_LIFE) SetTexture(ResourceManager::GetTexture("brick"));
		else if (type == BONUS_LIFE) SetTexture(ResourceManager::GetTexture("brick"));
	};

	BonusType GetBonusType() { return bonusType; }

private:

	BonusType bonusType;

};

#endif // !BONUS_H
