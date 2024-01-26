#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"
class Explosion : public GameObject
{
public:

	Explosion(glm::vec2 position, glm::vec2 size, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {};

	float GetExplosionDuration() { return explosionDuration; }

private:

	float explosionDuration = 1.0f;

};

#endif // !EXPLOSION_H