#include "Player.h"

void Player::MoveAnimation(float dt)
{
	if (mDir == CHAR_MOVELEFT) {

	}
	else if (mDir == CHAR_MOVERIGHT) {

	}
	else if (mDir == CHAR_MOVEUP) {

	}
	else if (mDir == CHAR_MOVEDOWN) {

	}
	else if (mDir == CHAR_STAND) {

	}
}

void Player::Move(float dt, MoveDirection dir)
{
	this->mDir = dir;

	if (dir == CHAR_MOVELEFT) this->position.x -= this->speed * dt;
	else if (dir == CHAR_MOVERIGHT) this->position.x += this->speed * dt;
	else if (dir == CHAR_MOVEUP) this->position.y -= this->speed * dt;
	else if (dir == CHAR_MOVEDOWN) this->position.x += this->speed * dt;

	MoveAnimation(dt);
}
