#include <d3dx9.h>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

// Khởi tạo một Object Game (cụ thể ở đây là Ball)
CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
}

// Update tọa độ của Object sau mỗi delta-time nhất định theo vector v = (vx, vy)
void CGameObject::Update(DWORD dt)
{
	x += vx*dt;
	y += vy*dt;
	x = min(max(animation->GetWidth() >> 1, x), SCREEN_WIDTH - (animation->GetWidth() >> 1));
	y = min(max(animation->GetHeight() >> 1, y), SCREEN_HEIGHT - animation->GetHeight());
}

void CGameObject::Render()
{
	animation->Render(x, y);
}