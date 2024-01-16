#include "Brick.h"

void Brick::ChangeColor()
{
	if (this->color == glm::vec3(1.0f)) this->color = glm::vec3(1.0f, 1.0f, 0.0f);
	else this->color = glm::vec3(1.0f);
}

void Brick::BlinkAnimation(float dt)
{
	blinkAnimationTime += dt;
	if (blinkAnimationTime >= blinkAnimationDelay) {
		ChangeColor();
		blinkAnimationTime = 0.0f;
	}
}
