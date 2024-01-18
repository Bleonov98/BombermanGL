#pragma once
#include "Character.h"
class Player : public Character
{
public:

	Player(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : Character(position, size, speed, angle, color) {};

	void MoveAnimation(float dt) override;

	void Move(float dt, MoveDirection dir);

private:

	

};

