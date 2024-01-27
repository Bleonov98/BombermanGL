#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"
class Explosion : public GameObject
{
public:

	Explosion(glm::vec2 position, glm::vec2 size, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		SetTexture(ResourceManager::GetTexture("explosion_0"));
	};

	float GetExplosionDuration() { return explosionDuration; }

	void ExplosionAnimation(float dt);

	~Explosion() {};

private:

	float explosionAnimationInterval = 0.12f, explosionAnimationTime = 0.0f;
	float explosionDuration = 0.6f;
	int animFrame = 1;

};

#endif // !EXPLOSION_H