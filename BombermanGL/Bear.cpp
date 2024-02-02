#include "Bear.h"

void Bear::Move(float dt)
{
	if (!targetPath.empty()) {

		// calculate direction
	}

	if (changePosInterval > 0.0f) {
		changePosTime += dt;
		if (changePosTime >= changePosInterval) {
			ChangePosition();
			changePosTime = 0.0f;
		}
	}

	if (mDir == CHAR_MOVELEFT) this->position.x -= this->speed * dt;
	else if (mDir == CHAR_MOVERIGHT) this->position.x += this->speed * dt;
	else if (mDir == CHAR_MOVEUP) this->position.y -= this->speed * dt;
	else if (mDir == CHAR_MOVEDOWN) this->position.y += this->speed * dt;

	MoveAnimation(dt);
}

void Bear::MoveAnimation(float dt)
{
	moveAnimationTime += dt;
	if (moveAnimationTime >= moveAnimationInterval) {
		SetTexture(ResourceManager::GetTexture("bear_" + std::to_string(animFrame)));

		if (animToggle) animFrame++;
		else animFrame--;

		if (animFrame == 0 || animFrame == 2) animToggle = !animToggle;

		moveAnimationTime = 0.0f;
	}
}

void Bear::DeathAnimation(float dt)
{
	deathDelay -= dt;
	if (deathDelay <= 0.0f) {
		DeleteObject();
		return;
	}

	deathAnimationTime += dt;
	if (deathAnimationTime >= deathAnimationInterval) {
		SetTexture(ResourceManager::GetTexture("bear_death_" + std::to_string(animFrame)));

		if (animFrame < 1) animFrame++;
		deathAnimationTime = 0.0f;
	}
}