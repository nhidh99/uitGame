#include "Scene.h"

// Load các Resource từ Factory trước khi khởi chạy Game
Scene::Scene()
{
	TextureFactory::GetInstance()->LoadResources();
	SpriteFactory::GetInstance()->LoadResources();
}