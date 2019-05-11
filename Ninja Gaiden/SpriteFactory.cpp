﻿#include "SpriteFactory.h"

SpriteFactory* SpriteFactory::_instance = NULL;

void SpriteFactory::LoadResources()
{
	// ======================== PLAYER SPRITE ===========================s
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(STANDING, 0, 5, 22, 38));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(RUNNING, 338, 5, 360, 38));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(RUNNING, 368, 5, 390, 38));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(RUNNING, 400, 5, 422, 38));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(SITTING, 2, 53, 21, 76));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(JUMPING, 139, 50, 163, 78));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(JUMPING, 165, 50, 189, 78));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(JUMPING, 190, 50, 214, 78));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(JUMPING, 216, 50, 240, 78));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(ATTACKING_STAND, 40, 5, 62, 38));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(ATTACKING_STAND, 66, 5, 93, 38));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(ATTACKING_STAND, 110, 5, 133, 38));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(ATTACKING_SIT, 35, 53, 57, 76));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(ATTACKING_SIT, 58, 53, 82, 76));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(ATTACKING_SIT, 100, 53, 122, 76));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(CLINGING, 264, 5, 288, 38));
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(CLIMBING, 286, 5, 310, 38));

	// ======================== ObjectItem SPRITE ==========================
	SpriteFactory::GetInstance()->AddSprite(new ObjectItemSprite(SWORD, 150, 28, 172, 43));
	SpriteFactory::GetInstance()->AddSprite(new ObjectItemSprite(SWORD, 170, 35, 187, 41));
	SpriteFactory::GetInstance()->AddSprite(new ObjectItemSprite(SHURIKEN, 265, 13, 273, 20));
	SpriteFactory::GetInstance()->AddSprite(new ObjectItemSprite(SWINGSWORD, 188, 29, 198, 47));
	SpriteFactory::GetInstance()->AddSprite(new ObjectItemSprite(SWINGSWORD, 206, 37, 224, 47));
	SpriteFactory::GetInstance()->AddSprite(new ObjectItemSprite(SWINGSWORD, 228, 29, 241, 47));
	SpriteFactory::GetInstance()->AddSprite(new ObjectItemSprite(SWINGSWORD, 244, 35, 262, 47));
	SpriteFactory::GetInstance()->AddSprite(new ObjectItemSprite(BULLET, 189, 62, 206, 73));

	// ======================== ENEMY SPRITE ================================
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(SWORDMAN, 211, 47, 240, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(SWORDMAN, 240, 47, 269, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(SWORDMAN, 278, 47, 307, 90));

	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(BAZOKAMAN, 383, 61, 414, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(BAZOKAMAN, 415, 61, 446, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(BAZOKAMAN, 446, 59, 453, 78));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(BAZOKAMAN, 460, 61, 471, 71));

	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(GUNMAN, 51, 55, 77, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(GUNMAN, 77, 55, 103, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(GUNMAN, 129, 55, 159, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(GUNMAN, 159, 55, 189, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(GUNMAN, 189, 62, 206, 73));

	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(CLOAKMAN, 409, 0, 435, 49));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(CLOAKMAN, 445, 0, 471, 49));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(CLOAKMAN, 487, 0, 515, 49));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(CLOAKMAN, 517, 0, 531, 23));

	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(PANTHER, 309, 74, 342, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(PANTHER, 342, 74, 377, 90));

	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(EAGLE, 471, 54, 497, 92));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(EAGLE, 500, 54, 526, 92));

	// =========================== HOLDER SPRITE ========================================
	SpriteFactory::GetInstance()->AddSprite(new HolderSprite(BUTTERFLY, 63, 42, 84, 61));
	SpriteFactory::GetInstance()->AddSprite(new HolderSprite(BUTTERFLY, 84, 41, 105, 60));
	SpriteFactory::GetInstance()->AddSprite(new HolderSprite(SANDWATCH, 100, 0, 110, 17));
	SpriteFactory::GetInstance()->AddSprite(new HolderSprite(BLUESHURIKEN, 0, 23, 17, 43));
	SpriteFactory::GetInstance()->AddSprite(new HolderSprite(ORANGEBOTTLE, 57, 0, 78, 18));
	SpriteFactory::GetInstance()->AddSprite(new HolderSprite(ORANGESHURIKEN, 0, 88, 16, 104));
}

// Thêm một Sprite vào danh sách các Sprite, quy định theo Tag của Sprite
void SpriteFactory::AddSprite(Sprite * sprite)
{
	_sprites[sprite->tag].push_back(sprite);
}

Sprite * SpriteFactory::GetSprite(Tag tag, int index)
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

SpriteFactory * SpriteFactory::GetInstance()
{
	if (_instance == NULL)
		_instance = new SpriteFactory();
	return _instance;
}