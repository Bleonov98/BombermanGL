#include "Onion.h"

void Onion::MoveAnimation(float dt)
{
	moveAnimationTime += dt;
	if (moveAnimationTime >= moveAnimationInterval) {
		SetTexture(ResourceManager::GetTexture("onion_" + std::to_string(animFrame)));

		if (animToggle) animFrame++;
		else animFrame--;
		
		if (animFrame == 0 || animFrame == 2) animToggle = !animToggle;

		moveAnimationTime = 0.0f;
	}
}

void Onion::DeathAnimation(float dt)
{
	deathDelay -= dt;
	if (deathDelay <= 0.0f) {
		DeleteObject();
		return;
	}

	deathAnimationTime += dt;
	if (deathAnimationTime >= deathAnimationInterval) {
		SetTexture(ResourceManager::GetTexture("onion_death_" + std::to_string(animFrame)));

		if (animFrame < 1) animFrame++;
		deathAnimationTime = 0.0f;
	}
}
