#include "Brick.h"

void Brick::ChangeColor()
{
	if (this->color == glm::vec3(1.0f)) this->color = glm::vec3(1.0f, 1.0f, 0.0f);
	else this->color = glm::vec3(1.0f);
}

void Brick::BlinkAnimation(float dt)
{
	blinkAnimationTime += dt;
	if (blinkAnimationTime >= blinkAnimationInterval) {
		ChangeColor();
		blinkAnimationTime = 0.0f;
	}
}

void Brick::DestroyAnimation(float dt)
{
	if (animFrame > 4) {
		DeleteObject();
		return;
	}

	destroyAnimationTime += dt;
	if (destroyAnimationTime >= destroyAnimationInterval) {
		SetTexture(ResourceManager::GetTexture("brick_" + std::to_string(animFrame)));

		destroyAnimationTime = 0.0f;

		animFrame++;
	}
}
