#include "Explosion.h"

void Explosion::ExplosionAnimation(float dt)
{
	if (animFrame > 3) return;

	explosionAnimationTime += dt;
	if (explosionAnimationTime >= explosionAnimationInterval) {
		SetTexture(ResourceManager::GetTexture("explosion_" + std::to_string(animFrame)));
		animFrame++;
		explosionAnimationTime = 0.0f;
	}
}

void Explosion::SetAABB(std::vector<std::vector<int>>& gridData, std::vector<std::vector<glm::vec2>> grid, glm::vec2 gridPos)
{
	// find explosion position point in view of field cell size (100/60)
	glm::vec2 FirstStartPos = glm::vec2(position.x + size.x / 2.0f - 45.0f, position.y + 5.0f);
	glm::vec2 FirstEndPos = glm::vec2(position.x + size.x / 2.0f + 45.0f, position.y + size.y - 5.0f);
	glm::vec2 SecondStartPos = glm::vec2(position.x + 5.0f, position.y + size.y / 2.0f - 25.0f);
	glm::vec2 SecondEndPos = glm::vec2(position.x + size.x - 5.0f, position.y + size.y / 2.0f + 25.0f);

	// set side length depending on map data
	std::pair<int, int> gridNum;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == gridPos) gridNum = std::make_pair(i, j);
		}
	}

	// "slice" unwanted part of explosion if there is block
	bool checker[4]{ 0 };
	for (int i = 1; i < radius; i++) 
	{
		if (gridNum.first + i <= grid.size() - 1)
			if (gridData[gridNum.first + i][gridNum.second] != 0 && checker[0] == 0) {
				checker[0] = 1;

				FirstEndPos.y -= 63.0f * (radius - i) - 15.0f;
				if (gridData[gridNum.first + i][gridNum.second] == 1) gridData[gridNum.first + i][gridNum.second] = 0;
			}

		if (gridNum.first - i >= 0)
			if (gridData[gridNum.first - i][gridNum.second] != 0 && checker[1] == 0) {
				checker[1] = 1;

				FirstStartPos.y += 63.0f * (radius - i) - 15.0f;
				if (gridData[gridNum.first - i][gridNum.second] == 1) gridData[gridNum.first - i][gridNum.second] = 0;
			}

		if (gridNum.second + i <= grid[0].size() - 1)
			if (gridData[gridNum.first][gridNum.second + i] != 0 && checker[2] == 0) {
				checker[2] = 1;

				SecondEndPos.x -= 100.0f * (radius - i) - 15.0f;
				if (gridData[gridNum.first][gridNum.second + i] == 1) gridData[gridNum.first][gridNum.second + i] = 0;
			}
		
		if (gridNum.second - i >= 0)
			if (gridData[gridNum.first][gridNum.second - i] != 0 && checker[3] == 0) {
				checker[3] = 1;

				SecondStartPos.x += 100.0f * (radius - i) - 15.0f;
				if (gridData[gridNum.first][gridNum.second - i] == 1) gridData[gridNum.first][gridNum.second - i] = 0;
			}
	}
	
	// set aabbs
	hBox.SetBorder(FirstStartPos, FirstEndPos);
	hBox2.SetBorder(SecondStartPos, SecondEndPos);
}

bool Explosion::ExplosionCollision(GameObject& other)
{
	if (ObjectCollision(hBox, other)) return true;
	else if (ObjectCollision(hBox2, other)) return true;
	
	return false;
}
