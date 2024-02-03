#include "Enemy.h"

void Enemy::Move(float dt)
{
	if (changePosInterval > 0.0f) {
		changePosTime += dt;
		if (changePosTime >= changePosInterval) {
			ChangePosition();
			changePosTime = 0.0f;
		}
	}

	if (mDir == CHAR_MOVELEFT) this->position.x -= this->speed * dt;
	else if (mDir == CHAR_MOVERIGHT) this->position.x += this->speed * dt;
	else if (mDir == CHAR_MOVEUP) this->position.y -= this->speed * dt;
	else if (mDir == CHAR_MOVEDOWN) this->position.y += this->speed * dt;

	MoveAnimation(dt);
}

void Enemy::ChangePosition()
{
	srand(time(NULL));
	while (mDir == lastDir) mDir = static_cast<MoveDirection>(rand() % CHAR_STAND);

	lastDir = mDir;
}

void Enemy::FindTarget(std::vector<std::vector<int>> gridData, std::vector<std::vector<glm::vec2>> grid, glm::vec2 nearestCell, glm::vec2 targetCell)
{
	targetPath.clear();
	if (nearestCell == targetCell) return;

	// find grid position for target and enemy
	int eRow, eCol, pRow, pCol;
	for (int i = 0; i < grid.size(); ++i)
	{
		for (int j = 0; j < grid[i].size(); ++j)
		{
			if (grid[i][j] == nearestCell) eRow = i, eCol = j;
			if (grid[i][j] == targetCell) pRow = i, pCol = j;
		
			if (gridData[i][j] > 0) gridData[i][j] = -1; // set all filled cells to -1
		}
	}

	// Wave algorithm
	// set steps to grid
	int c = 0;
	bool found = false;
	gridData[eRow][eCol] = c;
	std::vector<std::pair<int, int>> wave;
	std::vector<std::pair<int, int>> nextWave;
	wave.push_back(std::make_pair(eRow, eCol));

	while (c < findingRange && !wave.empty())
	{
		c++; // lol

		for (int i = 0; i < wave.size(); i++)
		{
			// top cell
			if (wave[i].first - 1 >= 0) {
				if (gridData[wave[i].first - 1][wave[i].second] == 0) {
					nextWave.push_back(std::make_pair(wave[i].first - 1, wave[i].second));
					gridData[wave[i].first - 1][wave[i].second] = c;
				}
			}

			// bottom cell
			if (wave[i].first + 1 < 11) {
				if (gridData[wave[i].first + 1][wave[i].second] == 0) {
					nextWave.push_back(std::make_pair(wave[i].first + 1, wave[i].second));
					gridData[wave[i].first + 1][wave[i].second] = c;
				}
			}

			// right cell
			if (wave[i].second + 1 < 13) {
				if (gridData[wave[i].first][wave[i].second + 1] == 0) {
					nextWave.push_back(std::make_pair(wave[i].first, wave[i].second + 1));
					gridData[wave[i].first][wave[i].second + 1] = c;
				}
			}

			// left cell
			if (wave[i].second - 1 >= 0) {
				if (gridData[wave[i].first][wave[i].second - 1] == 0) {
					nextWave.push_back(std::make_pair(wave[i].first, wave[i].second - 1));
					gridData[wave[i].first][wave[i].second - 1] = c;
				}
			}
		}


		wave.swap(nextWave);
		nextWave.clear();
	}
	if (gridData[pRow][pCol] == c) found = true;
	
	if (found) {
		//while (c > 0) {

		//}
	}
}
