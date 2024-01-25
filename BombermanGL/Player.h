#ifndef PLAYER_H
#define PLAYER_H

#include "CharacterObject.h"

class Player : public CharacterObject
{
public:

	Player(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : CharacterObject(position, size, speed, angle, color) {
		SetTexture(ResourceManager::GetTexture("player_down_0"));
	};

	// actions
	void Move(float dt, MoveDirection dir);

	// diff
	void MoveAnimation(float dt) override;
	void UpdateAABB() override { hBox.SetBorder(glm::vec2(position.x + 10.0f, position.y + 25.0f), position + glm::vec2(size.x - 10.0f, size.y)); }

	// gameplay
	void Reload() { bombCapacity++; }
	void PlaceBomb() { bombCapacity--; }
	bool IsReloaded() { return bombCapacity > 0; }

	virtual ~Player() {};

private:

	int bombCapacity = 1;

};

#endif // !PLAYER_H



