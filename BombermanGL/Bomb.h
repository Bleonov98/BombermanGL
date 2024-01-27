#ifndef BOMB_H
#define BOMB_H

#include "GameObject.h"
class Bomb : public GameObject
{
public:

	Bomb(glm::vec2 position, glm::vec2 size, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		SetTexture(ResourceManager::GetTexture("bomb"));
	};

	void BombAnimation(float dt);

	float GetExplodeDelay() { return this->bombExplodeDelay; }

	~Bomb() {};

private:

	float bombAnimationInterval = 0.8f, bombAnimationTime = 0.0f, bombExplodeDelay = 3.25f;
	bool sizeAnimationToggle = false;

};

#endif // !BOMB_H