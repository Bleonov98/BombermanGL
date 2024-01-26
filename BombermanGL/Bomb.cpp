#include "Bomb.h"

void Bomb::BombAnimation(float dt)
{
	bombAnimationTime += dt;
	if (bombAnimationTime >= bombAnimationInterval) {

		sizeAnimationToggle ? size -= 1.0f : size += 1.0f;
		sizeAnimationToggle = !sizeAnimationToggle;

		bombAnimationTime = 0.0f;
	}
}
