#ifndef BLOB_H
#define BLOB_H

#include "Enemy.h"

class Blob : public Enemy
{
public:

	Blob(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Enemy(position, size, speed, angle, color) {
		this->changePosInterval = 30.0f;
		this->deathAnimationInterval = 0.15f;
		SetTexture(ResourceManager::GetTexture("blob_0"));
	};

	void MoveAnimation(float dt) override;
	void DeathAnimation(float dt) override;

private:

};

#endif // !BLOB_H