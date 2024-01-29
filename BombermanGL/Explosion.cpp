#include "Explosion.h"

void Explosion::ExplosionAnimation(float dt)
{
	if (animFrame > 3) return;

	explosionAnimationTime += dt;
	if (explosionAnimationTime >= explosionAnimationInterval) {
		SetTexture(ResourceManager::GetTexture("explosion_" + std::to_string(animFrame)));
		animFrame++;
		explosionAnimationTime = 0.0f;
	}
}

void Explosion::ExplosionCollision(GameObject* other)
{
}
