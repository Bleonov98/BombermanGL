#include "Player.h"

void Player::MoveAnimation(float dt)
{
	moveAnimationTime += dt;
	if (moveAnimationTime >= moveAnimationInterval) {

		if (mDir == CHAR_MOVELEFT) {
			SetTexture(ResourceManager::GetTexture("player_left_" + std::to_string(animFrame)));
		}
		else if (mDir == CHAR_MOVERIGHT) {
			SetTexture(ResourceManager::GetTexture("player_right_" + std::to_string(animFrame)));
		}
		else if (mDir == CHAR_MOVEUP) {
			SetTexture(ResourceManager::GetTexture("player_up_" + std::to_string(animFrame)));
		}
		else if (mDir == CHAR_MOVEDOWN) {
			SetTexture(ResourceManager::GetTexture("player_down_" + std::to_string(animFrame)));
		}
		else if (mDir == CHAR_STAND) {
			SetTexture(ResourceManager::GetTexture("player_down_0"));
		}

		if (animToggle) animFrame++;
		else animFrame--;

		if (animFrame == 0 || animFrame == 2) animToggle = !animToggle;
		
		moveAnimationTime = 0.0f;
	}
}

void Player::DeathAnimation(float dt)
{
	deathDelay -= dt;
	if (deathDelay <= 0.0f) {
		deathDelay = 0.75f;
		if (life > 0) life--, isDead = false, respawn = true;
		else gameOver = true;
		return;
	}

	deathAnimationTime += dt;
	if (deathAnimationTime >= deathAnimationInterval) {
		SetTexture(ResourceManager::GetTexture("player_death_" + std::to_string(animFrame)));

		if (animFrame < 3) animFrame++;
		deathAnimationTime = 0.0f;
	}
}

void Player::ProcessBonus(BonusType bonusType)
{
	if (bonusType == BONUS_FIRE) explosionRange++;
	else if (bonusType == BONUS_BOMB) bombCapacity++, ammo++;
	else if (bonusType == BONUS_SPEED) speed += 30.0f;
	else if (bonusType == BONUS_LIFE) life++;
}

void Player::Spawn()
{
	position = glm::vec2(120.0f, 100.0f);
	respawn = false;
}

bool Player::EnemyCollision(GameObject& object)
{
	glm::vec2 centerPos = position + size / 2.0f;
	enHBox.SetBorder(centerPos - 15.0f, centerPos + 15.0f);

	return ObjectCollision(enHBox, object);
}

void Player::Move(float dt, MoveDirection dir)
{ 
	if (this->mDir != dir) animFrame = 0, animToggle = true;
	this->mDir = dir;

	if (mDir == CHAR_MOVELEFT) this->position.x -= this->speed * dt;
	else if (mDir == CHAR_MOVERIGHT) this->position.x += this->speed * dt;
	else if (mDir == CHAR_MOVEUP) this->position.y -= this->speed * dt;
	else if (mDir == CHAR_MOVEDOWN) this->position.y += this->speed * dt;

	MoveAnimation(dt);
}
