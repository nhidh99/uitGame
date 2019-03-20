#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Sprites.h"


using namespace std;

class CGameObject
{
protected:

	float x;
	float y;
	float vx;
	float vy;
	LPANIMATION animation;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetVx(float vx) { this->vx = vx; }
	void SetVy(float vy) { this->vy = vy; }
	void AddPosX(float x) { this->x += x; }
	void AddPosY(float y) { this->y += y; }
	void SetAnimation(LPANIMATION anim) { animation = anim; }
	
	int GetWidth() { return animation->GetWidth(); }
	int GetHeight() { return animation->GetHeight(); }
	int GetPosX() { return x; }
	int GetPosY() { return y; }
	float GetVx() { return vx; }
	float GetVy() { return vy; }

	RECT GetBound()
	{
		RECT bound;
		bound.top = y - (animation->GetHeight() >> 1) + 1;
		bound.bottom = bound.top + animation->GetHeight() - 1;
		bound.left = x - (animation->GetWidth() >> 1) + 1;
		bound.right = bound.left + animation->GetWidth() - 1;
		return bound;
	}

	bool Collision(CGameObject* obj)
	{
		RECT dest;
		return IntersectRect(&dest, &this->GetBound(), &obj->GetBound());
	}

	CGameObject();
	void Update(DWORD dt);
	void Render();
	~CGameObject();
};