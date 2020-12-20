#include "game_level.h"

#include <fstream>
#include <sstream>


int GameLevel::load(const char* path, unsigned int levelWidth, unsigned int levelHeight) {
	this->bricks.clear();
	unsigned int code;
	std::string line;
	std::ifstream fstream(path);
	std::vector<std::vector<unsigned int>> table;
	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> code)
				row.push_back(code);
			table.push_back(row);
		}
	}
	if (table.size() == 0) return 1; // fail to load game data

	unsigned int rows = table.size();
	unsigned int cols = table[0].size();
	float unit_width = levelWidth / static_cast<float>(cols);
	float unit_height = levelHeight / static_cast<float>(rows);

	for (unsigned int y = 0; y < rows; ++y) {
		for (unsigned int x = 0; x < cols; ++x) {
			glm::vec2 pos(unit_width * x, unit_width * y);
			glm::vec2 size(unit_width, unit_height);
			if (table[y][x] == 0) { 
				// empty 
			}
			else if (table[y][x] == 1) {
				// solid
				glm::vec3 color = glm::vec3(0.8f, 0.8f, 0.7f);
				this->bricks.push_back(BrickObject(pos, size, ResourceManager::GetTexture("block_solid"), color, 0.0f, true));
			}
			else if (table[y][x] == 2) {
				// non-solid
				glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
				this->bricks.push_back(BrickObject(pos, size, ResourceManager::GetTexture("block"), color, 0.0f, false));
			}
		}
	}
	return 0;
}

void GameLevel::Draw(SpriteRenderer& Renderer) {
	for (BrickObject& brick : this->bricks)
		if (!brick.isDestroyed)
			brick.Draw(Renderer);
}

bool GameLevel::isComplete() {
	for (BrickObject& brick : this->bricks)
		if (!brick.isSolid && !brick.isDestroyed)
			return false;
	return true;
}

