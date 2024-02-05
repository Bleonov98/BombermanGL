#include "Bear.h"

void Bear::Move(float dt)
{
	if (!targetPath.empty()) {
		// calculate direction
		unsigned int vert = 2, horiz = 2;

		if (targetPath.back().x + 5.0f < position.x) horiz = 0;
		else if (targetPath.back().x + 5.0f > position.x) horiz = 1;
		if (targetPath.back().y + 5.0f < position.y) vert = 0;
		else if (targetPath.back().y + 5.0f > position.y) vert = 1;

		if (horiz != 2) mDir = (horiz == 0) ? CHAR_MOVELEFT : CHAR_MOVERIGHT;
		else if (vert != 2) mDir = (vert == 0) ? CHAR_MOVEUP : CHAR_MOVEDOWN;

		targetPath.pop_back();
	}
	else if (changePosInterval > 0.0f) {
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