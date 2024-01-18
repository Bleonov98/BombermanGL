#ifndef CHARACTER_H
#define CHARACTER_H

enum MoveDirection {
	CHAR_MOVERIGHT,
	CHAR_MOVELEFT,
	CHAR_MOVEUP,
	CHAR_MOVEDOWN, 
	CHAR_STAND
};

#include "GameObject.h"
class Character : public GameObject
{
public:

	Character(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->speed = speed;
	};

	virtual void MoveAnimation(float dt) = 0;

	void SetSpeed(float speed) { this->speed = speed; }
	float GetSpeed() { return this->speed; }

protected:

	float speed;
	float moveAnimationTime = 0.0f, moveAnimationDelay = 0.2f;
	MoveDirection mDir;

};

#endif // !CHARACTER_H