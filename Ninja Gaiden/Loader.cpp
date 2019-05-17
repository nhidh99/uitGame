#include "Loader.h"

std::vector<Holder*> Loader::LoadHolders()
{
	//Lấy filePath
	std::vector<Holder*> holders;
	std::string filePath = "Resources\\Holder.txt";
	std::ifstream ifile;
	ifile.open(filePath);

	while (!ifile.eof()) {
		//Đọc các thông số của Enemy
		int id, posX, posY, itemID;
		ifile >> id >> posX >> posY >> itemID;

		if (id == 1)
		{
			Holder* holder = new HolderButterfly();
			holder->spawnX = holder->posX = posX;
			holder->spawnY = holder->posY = posY;
			
			holders.push_back(holder);
		}

	}
	ifile.close();
	return holders;
}

std::vector<Enemy*> Loader::LoadEnemies()
{
	//Lấy filePath
	std::vector<Enemy*> enemies;
	std::string filePath = "Resources\\Enemy.txt";
	std::ifstream ifile;
	auto enemyFactory = new EnemyFactory();
	ifile.open(filePath);

	while (!ifile.eof()) {
		//Đọc các thông số của Enemy
		int id, posX, posY, moveSpaceH, moveSpaceT;
		ifile >> id >> posX >> posY >> moveSpaceH >> moveSpaceT;

		Enemy* enemy = enemyFactory->CreateEnemy(id);
		
		enemy->spawnX = enemy->posX = posX;
		enemy->spawnY = enemy->posY = posY;
		enemy->isReverse = true;
		enemy->moveSpaceHead = moveSpaceH;
		enemy->moveSpaceTail = moveSpaceT;
		enemies.push_back(enemy);
	}
	ifile.close();
	return enemies;
}

std::vector<Rect*> Loader::LoadWallsBound()
{
	std::vector<Rect*> walls;
	std::string filePath = "Resources\\Wall.txt";
	std::ifstream ifile;
	ifile.open(filePath);

	while (!ifile.eof()) {
		//Đọc các thông số của Enemy
		int x, y, w, h;
		ifile >> x >> y >> w >> h;
		walls.push_back(new Rect(x, y, w, h));
	}
	ifile.close();
	return walls;
}

std::vector<Rect*> Loader::LoadGroundsBound()
{
	std::vector<Rect*> grounds;
	std::string filePath = "Resources\\Ground.txt";
	std::ifstream ifile;
	ifile.open(filePath);

	while (!ifile.eof()) {
		//Đọc các thông số của Enemy
		int x, y, w, h;
		ifile >> x >> y >> w >> h;
		grounds.push_back(new Rect(x, y, w, h));
	}
	ifile.close();
	return grounds;
}
