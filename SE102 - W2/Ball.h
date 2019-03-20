#pragma once
#include "GameObject.h"

class CBall : public CGameObject
{
public: 
	void Update(DWORD dt);
	void Render();
	void AddPosX(int x);
};