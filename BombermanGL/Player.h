#ifndef PLAYER_H
#define PLAYER_H

#include "CharacterObject.h"

class Player : public CharacterObject
{
public:

	Player(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : CharacterObject(position, size, speed, angle, color) {
		SetTexture(ResourceManager::GetTexture("player_down_0"));
	};

	void MoveAnimation(float dt) override;

	void Move(float dt, MoveDirection dir);

	virtual ~Player() {};

private:



};

#endif // !PLAYER_H



