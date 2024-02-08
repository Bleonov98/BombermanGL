#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.h"
class Explosion : public GameObject
{
public:

	Explosion(glm::vec2 position, glm::vec2 size, int radius, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->radius = radius;
		SetTexture(ResourceManager::GetTexture("explosion_0"));
	};

	float GetExplosionDuration() { return explosionDuration; }
	void ExplosionAnimation(float dt);

	void SetAABB(std::vector<std::vector<int>>& gridData, std::vector<std::vector<glm::vec2>> grid, glm::vec2 gridPos);
	bool ExplosionCollision(GameObject& other);

	~Explosion() {};

private:

	float explosionAnimationInterval = 0.1f, explosionAnimationTime = 0.0f;
	float explosionDuration = 0.35f;
	int animFrame = 1, radius;
	AABB hBox2;

};

#endif // !EXPLOSION_H