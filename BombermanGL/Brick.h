#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

enum BrickType {
	BRICK_SOLID,
	BRICK_COMMON
};

class Brick : public GameObject
{
public:

	Brick(glm::vec2 position, glm::vec2 size, BrickType type, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->brickType = type;

		if (type == BRICK_SOLID) SetTexture(ResourceManager::GetTexture("stone"));
		else if (type == BRICK_COMMON) SetTexture(ResourceManager::GetTexture("brick"));
	};

	void ChangeColor();
	void BlinkAnimation(float dt);

	BrickType GetBrickType() { return brickType; }
	bool IsBonusBrick() { return containBonus; }

private:

	BrickType brickType;
	bool containBonus = false;
	float blinkAnimationTime = 0.0f, blinkAnimationDelay = 0.4f;

};

#endif // !BRICK_H



