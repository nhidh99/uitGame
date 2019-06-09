#pragma once
#include "TextureFactory.h"
#include "SpriteFactory.h"
#include "MapFactory.h"
#include "Sound.h"

class Scene
{
public:
	Scene();
	virtual void LoadResources() {};			// Tải resources trước khi tạo Scene
	virtual void Update(float dt) {};			// Update các thông số sau khoảng delta-time
	virtual void Render() {};					// Render các UI Components lên Scene
	virtual void OnKeyDown(int keyCode) {};		// Xử lí Scene khi nhấn phím
	virtual void OnKeyUp(int keyCode) {};		// Xử lí Scene khi thả phím
	virtual void LoadFonts();
	virtual void LoadSound();
};