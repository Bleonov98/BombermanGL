#ifndef BEAR_H
#define BEAR_H

#include "Enemy.h"

class Bear : public Enemy
{
public:

	Bear(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Enemy(position, size, speed, angle, color) {
		this->changePosInterval = 8.0f;
		this->mType = ALGORITHM;
		SetTexture(ResourceManager::GetTexture("bear_0"));
	};

	void Move(float dt) override;

	void MoveAnimation(float dt) override;
	void DeathAnimation(float dt) override;

private:


};

#endif // !BEAR_H