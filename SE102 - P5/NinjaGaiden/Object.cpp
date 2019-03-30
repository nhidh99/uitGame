#include "Object.h"

void Object::SetPosX(float x) { _posX = x; }
void Object::SetPosY(float y) { _posY = y; }
void Object::SetVx(float vx) { _vx = vx; }
void Object::SetVy(float vy) { _vy = vy; }
void Object::SetPosition(float x, float y) { _posX = x; _posY = y; }
void Object::SetVelocity(float vx, float vy) { _vx = vx; _vy = vy; }

void Object::AddPosX(float x)
{
	_posX += x;
}

void Object::AddPosY(float y)
{
	_posY += y;
}

void Object::AddVx(float vx)
{
	_vx += vx;
}

void Object::AddVy(float vy)
{
	_vy += vy;
}

float Object::GetPosX() { return _posX; }
float Object::GetPosY() { return _posY; }
float Object::GetVx() { return _vx; }
float Object::GetVy() { return _vy; }
int Object::GetWidth() { return _width; }
int Object::GetHeight() { return _height; }

void Object::Update(float dt)
{
	_posX += _vx * dt;
	_posY += _vy * dt;
}

void Object::Reverse(bool flag)
{
	_isReverse = flag;
}
