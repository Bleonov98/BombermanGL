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
	void DestroyAnimation(float dt);

	BrickType GetBrickType() { return brickType; }

	void SetBrickBonus() { this->containBonus = true; }
	bool IsBonusBrick() { return containBonus; }
	
	void DestroyBrick() { this->destroyed = true; }
	bool IsDestroyed() { return destroyed; }

	virtual ~Brick() {};

private:

	BrickType brickType;
	bool containBonus = false, destroyed = false;
	float blinkAnimationTime = 0.0f, blinkAnimationInterval = 0.4f;
	float destroyAnimationTime = 0.0f, destroyAnimationInterval = 0.04f;
	int animFrame = 0;

};

#endif // !BRICK_H



