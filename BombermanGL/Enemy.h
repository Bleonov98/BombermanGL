#ifndef ENEMY_H
#define ENEMY_H

enum MoveType {
	COMMON,
	ALGORITHM
};

#include "CharacterObject.h"
class Enemy : public CharacterObject
{
public:

	Enemy(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : CharacterObject(position, size, speed, angle, color) {
		mDir = CHAR_MOVERIGHT;
		lastDir = mDir;

		moveAnimationInterval = 0.4f;
	};

	virtual void MoveAnimation(float dt) = 0;
	virtual void DeathAnimation(float dt) = 0;

	virtual void Move(float dt);
	virtual void ChangePosition();
	void FindTarget(std::vector<std::vector<int>> gridData, std::vector<std::vector<glm::vec2>> grid, glm::vec2 nearestCell, glm::vec2 targetCell);

	MoveType GetMoveType() { return this->mType; }

protected:

	MoveDirection lastDir;
	MoveType mType = COMMON;

	float changePosInterval = 0.0f, changePosTime = 0.0f;
	int findingRange = 4;
	std::vector<glm::vec2> targetPath;

};

#endif // !ENEMY_H


