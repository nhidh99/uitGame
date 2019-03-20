﻿#pragma once
#include "Sprite.h"
#include "PlayerSprite.h"
#include "ObjectItemAxeSprite.h"

// Chứa tất cả các Sprite cần dùng cho Game, khởi tạo trước khi vào vòng lặp Game (Run)
// Dùng Singleton Pattern

class SpriteFactory
{
private:
	static SpriteFactory* _instance;
	std::unordered_map<Tag, std::vector<Sprite*>> _sprites;	// Các Sprite theo Tag của Object cho trước

public:
	void LoadResources();
	void AddSprite(Sprite* sprite);
	std::vector<Sprite*> GetSprites(Tag tag, int firstIndex, int lastIndex);
	static SpriteFactory* GetInstance();
};