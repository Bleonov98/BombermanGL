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
class CharacterObject : public GameObject
{
public:

	CharacterObject(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : GameObject(position, size, angle, color) {
		this->speed = speed;
	};

	// basic
	void SetSpeed(float speed) { this->speed = speed; }
	float GetSpeed() { return this->speed; }

	void Kill() { isDead = true, animFrame = 0; }
	bool IsDead() { return isDead; }

	// animations
	virtual void MoveAnimation(float dt) = 0;
	virtual void DeathAnimation(float dt) = 0;

	// collision
	bool ProcessCollision(GameObject& other, float dt);
	bool ProcessMapCollision(float dt);

	virtual ~CharacterObject() {};

protected:

	float speed;

	// - animation
	float moveAnimationTime = 0.0f, moveAnimationInterval = 0.18f;
	float deathAnimationTime = 0.0f, deathAnimationInterval = 0.25f, deathDelay = 0.75f;
	int animFrame = 0;
	bool animToggle = true, isDead = false;

	MoveDirection mDir = CHAR_STAND;

};

#endif // !CHARACTER_H