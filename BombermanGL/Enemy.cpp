#include "Enemy.h"

void Enemy::Move(float dt)
{
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

void Enemy::ChangePosition()
{
	srand(time(NULL));
	while (mDir == lastDir) mDir = static_cast<MoveDirection>(rand() % CHAR_STAND);

	lastDir = mDir;
}

void Enemy::FindTarget(std::vector<std::vector<int>>& gridData, std::vector<std::vector<glm::vec2>> grid, glm::vec2 nearestCell, glm::vec2 targetCell)
{

}
