#include "SpriteFactory.h"

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
	SpriteFactory::GetInstance()->AddSprite(new PlayerSprite(JUMPING, 190, 50,	214, 78));
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

	// ======================== ENEMY SPRITE ================================
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(SWORDMAN, 209, 47, 235, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(SWORDMAN, 240, 47, 264, 90));
	SpriteFactory::GetInstance()->AddSprite(new EnemySprite(SWORDMAN, 273, 47, 303, 90));
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