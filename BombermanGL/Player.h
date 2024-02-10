#ifndef PLAYER_H
#define PLAYER_H

#include "CharacterObject.h"
#include "Bonus.h"

class Player : public CharacterObject
{
public:

	Player(glm::vec2 position, glm::vec2 size, float speed, float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) : CharacterObject(position, size, speed, angle, color) {
		deathDelay = 1.05f, deathAnimationInterval = 0.25f;
		SetTexture(ResourceManager::GetTexture("player_down_0"));
	};

	void UpdateAABB() override { hBox.SetBorder(glm::vec2(position.x + 10.0f, position.y + 25.0f), position + glm::vec2(size.x - 10.0f, size.y)); }
	bool EnemyCollision(GameObject& object);

	// actions
	void Move(float dt, MoveDirection dir);

	// animations
	void MoveAnimation(float dt) override;
	void DeathAnimation(float dt) override;

	// gameplay
	void Reload() { if (this->ammo < bombCapacity) this->ammo++; }
	void PlaceBomb() { if (ammo > 0) this->ammo--; }
	bool IsReloaded() { return this->ammo > 0; }

	void ProcessBonus(BonusType bonusType);
	int GetExplosionRange() { return this->explosionRange; }
	int GetLifes() { return this->life; }
	void AddScore() { score += 100; }
	int GetScore() { return this->score; }

	bool IsOver() { return gameOver; }
	bool IsRespawned() { return respawn; }
	void Spawn();

	virtual ~Player() {};

private:

	AABB enHBox;

	int bombCapacity = 1, ammo = 1, explosionRange = 2, life = 2, score = 0;
	bool gameOver = false, respawn = false;

};

#endif // !PLAYER_H



