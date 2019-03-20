#pragma once
#include "SpriteFactory.h"
#include "Animation.h"

class Object
{
protected:
	Tag _tag;					// Tag định loại Object
	float _posX, _posY;			// Vị trí (đồng thời là tâm của Object đó)
	float _vx, _vy;				// Vận tốc
	int _width, _height;		// Kích thước
	bool _isReverse;			// Kiểm tra lật hình theo chiều dọc

public:
	Object() {}
	virtual void SetPosX(float x);
	virtual void SetPosY(float y);
	virtual void SetPosition(float x, float y);
	virtual void SetVx(float vx);
	virtual void SetVy(float vy);
	virtual void SetVelocity(float vx, float vy);
	virtual void AddPosX(float x);
	virtual void AddPosY(float y);
	virtual void AddVx(float vx);
	virtual void AddVy(float vy);

	virtual float GetPosX();
	virtual float GetPosY();
	virtual float GetVx();
	virtual float GetVy();
	virtual int GetWidth();
	virtual int GetHeight();

	virtual void Update(float dt);				// Update thông số của Object sau khoảng thời gian delta-time
	virtual void Reverse(bool flag)	;			// Lật Object
	virtual void Render() = 0;					// Render Object
	virtual void Render(float x, float y) {}
};