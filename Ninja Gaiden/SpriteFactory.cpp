#include "SpriteFactory.h"

SpriteFactory* SpriteFactory::_instance = NULL;

void SpriteFactory::LoadResources()
{
	auto sprites = SpriteFactory::GetInstance();
	// ======================== PLAYER SPRITE ===========================
	sprites->AddSprite(new PlayerSprite(STANDING, 0, 5, 22, 38));
	sprites->AddSprite(new PlayerSprite(RUNNING, 338, 5, 360, 38));
	sprites->AddSprite(new PlayerSprite(RUNNING, 368, 5, 390, 38));
	sprites->AddSprite(new PlayerSprite(RUNNING, 400, 5, 422, 38));
	sprites->AddSprite(new PlayerSprite(SITTING, 2, 53, 21, 76));
	sprites->AddSprite(new PlayerSprite(JUMPING, 139, 50, 163, 78));
	sprites->AddSprite(new PlayerSprite(JUMPING, 165, 50, 189, 78));
	sprites->AddSprite(new PlayerSprite(JUMPING, 190, 50, 214, 78));
	sprites->AddSprite(new PlayerSprite(JUMPING, 216, 50, 240, 78));
	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 40, 5, 62, 38));
	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 66, 5, 93, 38));
	sprites->AddSprite(new PlayerSprite(ATTACKING_STAND, 110, 5, 133, 38));
	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 35, 53, 57, 76));
	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 58, 53, 82, 76));
	sprites->AddSprite(new PlayerSprite(ATTACKING_SIT, 100, 53, 122, 76));
	sprites->AddSprite(new PlayerSprite(CLINGING, 264, 5, 288, 38));
	sprites->AddSprite(new PlayerSprite(CLIMBING, 286, 5, 310, 38));

	// ======================== Weapon SPRITE ==========================
	sprites->AddSprite(new WeaponSprite(EXPLODED, 357, 10, 374, 30));
	sprites->AddSprite(new WeaponSprite(EXPLODED, 365, 40, 397, 78));
	sprites->AddSprite(new WeaponSprite(EXPLODED, 318, 0, 350, 40));
	sprites->AddSprite(new WeaponSprite(SWORD, 150, 28, 172, 43));
	sprites->AddSprite(new WeaponSprite(SWORD, 170, 35, 187, 41));
	sprites->AddSprite(new WeaponSprite(BLUESHURIKEN, 175, 95, 185, 105));
	sprites->AddSprite(new WeaponSprite(BLUESHURIKEN, 188, 95, 198, 105));
	sprites->AddSprite(new WeaponSprite(FIREWHEEL, 5, 80, 40, 115));
	sprites->AddSprite(new WeaponSprite(FIREWHEEL, 45, 80, 80, 115));
	sprites->AddSprite(new WeaponSprite(FIREWHEEL, 90, 80, 125, 115));
	sprites->AddSprite(new WeaponSprite(FIREWHEEL, 130, 80, 165, 115));
	sprites->AddSprite(new WeaponSprite(REDSHURIKEN, 203, 91, 217, 105));
	sprites->AddSprite(new WeaponSprite(REDSHURIKEN, 220, 91, 234, 105));
	sprites->AddSprite(new WeaponSprite(BIGEXPLODED, 380, 0, 420, 40));

	// ======================== ENEMY SPRITE ====================
	sprites->AddSprite(new EnemySprite(SWORDMAN, 211, 47, 240, 90));
	sprites->AddSprite(new EnemySprite(SWORDMAN, 240, 47, 269, 90));
	sprites->AddSprite(new EnemySprite(SWORDMAN, 278, 47, 307, 90));
	sprites->AddSprite(new EnemySprite(BAZOKAMAN, 383, 61, 414, 90));
	sprites->AddSprite(new EnemySprite(BAZOKAMAN, 414, 61, 444, 90));
	sprites->AddSprite(new EnemySprite(RUNMAN, 0, 56, 20, 86));
	sprites->AddSprite(new EnemySprite(RUNMAN, 21, 56, 41, 86));
	sprites->AddSprite(new EnemySprite(GUNMAN, 51, 56, 77, 87));
	sprites->AddSprite(new EnemySprite(GUNMAN, 77, 56, 103, 87));
	sprites->AddSprite(new EnemySprite(GUNMAN, 129, 56, 159, 87));
	sprites->AddSprite(new EnemySprite(GUNMAN, 159, 56, 189, 87));
	sprites->AddSprite(new EnemySprite(GUNMAN, 190, 62, 206, 73));
	sprites->AddSprite(new EnemySprite(CLOAKMAN, 404, 0, 437, 43));
	sprites->AddSprite(new EnemySprite(CLOAKMAN, 440, 0, 474, 43));
	sprites->AddSprite(new EnemySprite(CLOAKMAN, 488, 0, 518, 43));
	sprites->AddSprite(new EnemySprite(PANTHER, 309, 74, 342, 90));
	sprites->AddSprite(new EnemySprite(PANTHER, 342, 74, 377, 90));
	sprites->AddSprite(new EnemySprite(EAGLE, 471, 54, 497, 92));
	sprites->AddSprite(new EnemySprite(EAGLE, 500, 54, 526, 92));
	sprites->AddSprite(new EnemySprite(EAGLE, 500, 54, 526, 92));
	sprites->AddSprite(new EnemySprite(EAGLE, 500, 54, 526, 92));
	sprites->AddSprite(new EnemySprite(BOSS, 348, 248, 388, 298));
	sprites->AddSprite(new EnemySprite(BOSS, 394, 242, 434, 292));

	// =========================== HOLDER SPRITE ========================
	sprites->AddSprite(new HolderSprite(BUTTERFLY, 83, 55, 96, 70));
	sprites->AddSprite(new HolderSprite(BUTTERFLY, 96, 53, 114, 70));
	sprites->AddSprite(new HolderSprite(BIRD, 116, 50, 136, 70));
	sprites->AddSprite(new HolderSprite(BIRD, 139, 51, 159, 70));

	// =========================== ITEM SPRITE ==============================
	sprites->AddSprite(new ItemSprite(BLUESPIRIT, 0, 7, 20, 24));
	sprites->AddSprite(new ItemSprite(REDSPIRIT, 20, 7, 40, 24));
	sprites->AddSprite(new ItemSprite(GLASSHOUR, 400, 50, 416, 70));
	sprites->AddSprite(new ItemSprite(BLUESHURIKEN, 50, 6, 68, 26));
	sprites->AddSprite(new ItemSprite(REDBAG, 192, 6, 210, 26));
	sprites->AddSprite(new ItemSprite(FIREWHEEL, 110, 6, 128, 26));
	sprites->AddSprite(new ItemSprite(BLUEBAG, 172, 6, 190, 26));
	sprites->AddSprite(new ItemSprite(REDPOTION, 227, 6, 245, 26));
	sprites->AddSprite(new ItemSprite(REDSHURIKEN, 70, 8, 86, 24));

	// ============================= BULLET SPRITE ===========================
	sprites->AddSprite(new BulletSprite(CLOAKMAN, 519, 5, 527, 21));
	sprites->AddSprite(new BulletSprite(CLOAKMAN, 519, 23, 527, 38));
	sprites->AddSprite(new BulletSprite(CLOAKMAN, 534, 7, 550, 17));
	sprites->AddSprite(new BulletSprite(CLOAKMAN, 534, 27, 550, 38));
	sprites->AddSprite(new BulletSprite(GUNMAN, 192, 63, 203, 71));
	sprites->AddSprite(new BulletSprite(BAZOKAMAN, 443, 60, 455, 75));
	sprites->AddSprite(new BulletSprite(BAZOKAMAN, 458, 62, 470, 77));
	sprites->AddSprite(new BulletSprite(BOSS, 435, 265, 445, 275));
}

// Thêm một Sprite vào danh sách các Sprite, quy định theo Tag của Sprite
void SpriteFactory::AddSprite(Sprite* sprite)
{
	_sprites[sprite->tag].push_back(sprite);
}

Sprite* SpriteFactory::GetSprite(Tag tag, int index)
{
	return _sprites[tag][index];
}

// Lấy các Sprite (dùng cho tạo Animation) theo Tag từ vị trí first->last
std::vector<Sprite*> SpriteFactory::GetSprites(Tag tag, int firstIndex, int lastIndex)
{
	auto first = _sprites[tag].begin() + firstIndex;
	auto last = _sprites[tag].begin() + lastIndex;
	return std::vector<Sprite*>(first, last + 1);
}

SpriteFactory* SpriteFactory::GetInstance()
{
	if (_instance == NULL)
		_instance = new SpriteFactory();
	return _instance;
}