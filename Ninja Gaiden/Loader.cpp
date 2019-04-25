#include "Loader.h"

Loader::Loader()
{
	enemyFactory = new EnemyFactory();
}

std::vector<Enemy*> Loader::LoadEnemies()
{
	//Lấy filePath
	std::vector<Enemy*> enemies;
	std::string filePath = "Resources\\Enemy.txt";
	std::ifstream ifile;
	ifile.open(filePath);

	while (!ifile.eof()) {
		//Đọc các thông số của Enemy
		int id, posX, posY;
		ifile >> id >> posX >> posY;

		Enemy* enemy = enemyFactory->CreateEnemy(id);
		enemy->spawnX = enemy->posX = posX;
		enemy->spawnY = enemy->posY = posY;
		enemy->vx = 0.01;
		enemy->isReverse = true;
		enemies.push_back(enemy);
	}
	ifile.close();
	return enemies;
}

std::vector<BoundingBox> Loader::LoadWallsBound()
{
	std::vector<BoundingBox> walls;
	std::string filePath = "Resources\\Wall.txt";
	std::ifstream ifile;
	ifile.open(filePath);

	while (!ifile.eof()) {
		//Đọc các thông số của Enemy
		int x, y, w, h;
		ifile >> x >> y >> w >> h;
		walls.push_back(BoundingBox(x, y, w, h));
	}
	ifile.close();
	return walls;
}

std::vector<BoundingBox> Loader::LoadGroundsBound()
{
	std::vector<BoundingBox> grounds;
	std::string filePath = "Resources\\Ground.txt";
	std::ifstream ifile;
	ifile.open(filePath);

	while (!ifile.eof()) {
		//Đọc các thông số của Enemy
		int x, y, w, h;
		ifile >> x >> y >> w >> h;
		grounds.push_back(BoundingBox(x, y, w, h));
	}
	ifile.close();
	return grounds;
}
