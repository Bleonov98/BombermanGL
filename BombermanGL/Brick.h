#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"

enum BrickType {
	SOLID,
	COMMON
};

enum BrickBonus {
	FIRE,
	BOMB,
	SPEED,
	LIFE
};

class Brick : public GameObject
{
public:

	BrickType GetBrickType() { return brickType; }
	BrickBonus GetBrickBonus() { return brickBonus; }

private:

	BrickType brickType;
	BrickBonus brickBonus;

};

#endif // !BRICK_H



