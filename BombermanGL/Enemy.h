#ifndef ENEMY_H
#define ENEMY_H

#include "CharacterObject.h"
class Enemy : public CharacterObject
{
public:

	Enemy(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : CharacterObject(position, size, speed, angle, color) {
		mDir = CHAR_MOVERIGHT;
		lastDir = mDir;
	};

	virtual void MoveAnimation(float dt) = 0;

	void Move(float dt);
	void ChangePosition();
	void SetChangePosInterval(float changePosInterval) { this->changePosInterval = changePosInterval; }

private:

	MoveDirection lastDir;
	float changePosInterval = 0.0f, changePosTime = 0.0f;

};

#endif // !ENEMY_H


