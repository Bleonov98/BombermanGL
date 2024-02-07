#ifndef PLAYER_H
#define PLAYER_H

#include "CharacterObject.h"

class Player : public CharacterObject
{
public:

	Player(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : CharacterObject(position, size, speed, angle, color) {
		deathDelay = 1.05f, deathAnimationInterval = 0.25f;
		SetTexture(ResourceManager::GetTexture("player_down_0"));
	};

	void UpdateAABB() override { hBox.SetBorder(glm::vec2(position.x + 10.0f, position.y + 25.0f), position + glm::vec2(size.x - 10.0f, size.y)); }

	// actions
	void Move(float dt, MoveDirection dir);

	// animations
	void MoveAnimation(float dt) override;
	void DeathAnimation(float dt) override;

	// gameplay
	void Reload() { this->bombCapacity++; }
	void PlaceBomb() { this->bombCapacity--; }
	bool IsReloaded() { return this->bombCapacity > 0; }

	void UpExplosionRange() { this->explosionRange++; }
	int GetExplosionRange() { return this->explosionRange; }

	bool IsOver() { return gameOver; }

	virtual ~Player() {};

private:

	int bombCapacity = 2, explosionRange = 2, life = 2;
	bool gameOver = false;

};

#endif // !PLAYER_H



