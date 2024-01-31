#pragma once
#include "Enemy.h"
class Onion : public Enemy
{
public:

	Onion(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Enemy(position, size, speed, angle, color) {
		SetTexture(ResourceManager::GetTexture("onion_0"));
	};

	void MoveAnimation(float dt) override;

private:

};

