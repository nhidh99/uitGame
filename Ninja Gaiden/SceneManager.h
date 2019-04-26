#pragma once
#include "Scene.h"

class SceneManager
{
private:
	Scene* _curScene;							// Scene hiện tại mà Manager đang giữ
	static SceneManager* _instance;				// Instance (Singleton Pattern)

public:
	SceneManager();
	void ReplaceScene(Scene* scene);			// Thay thế Scene hiện có bằng Scene khác (dùng cho chuyển cảnh)
	Scene* GetCurScene();						// Get Scene hiện tại
	static SceneManager* GetInstance();			// Get Instance (Singleton Pattern)
};