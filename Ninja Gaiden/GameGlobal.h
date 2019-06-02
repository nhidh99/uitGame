﻿#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>

// Các thông số và biến tổng dùng cho toàn bộ Game
#define WINDOW_CLASS_NAME "Ninja Gaiden"		// Class Windows
#define MAIN_WINDOW_TITLE "Ninja Gaiden"		// Tên cửa sổ
#define SCREEN_WIDTH 312						// Chiều rộng cửa sổ
#define SCREEN_HEIGHT 176						// Chiều dài cửa sổ
#define MAX_FRAME_RATE 90						// FPS
#define BACK_COLOR D3DCOLOR_XRGB(0, 0, 0)		// Màu nền BackBuffer
#define DEFAULT_TPS 150							// Thời gian tồn tại của mỗi Frame (cho Animation)
#define GRAVITY_SPEED 0.014f					// Tốc độ trọng lực
#define KEYBOARD_BUFFER_SIZE 1024
#define NUMBER_MAP_LEVEL 1
#define TILE_SIZE 16
#define GAME_TIMER 150000
#define SCALE_RATE 0.5

// ===== Các thông số cho PLAYER ====
#define player Player::GetInstance()
#define PLAYER_RUNNING_SPEED 0.1f
#define PLAYER_INJURED_SPEED 0.065f
#define PLAYER_JUMPING_SPEED 0.28f
#define PLAYER_FALLING_SPEED 0.25f
#define PLAYER_CLIMBING_SPEED 0.1f
#define PLAYER_WIDTH 24
#define PLAYER_STANDING_HEIGHT 32
#define PLAYER_SITTING_HEIGHT 24
#define PLAYER_ATTACK_SPRITE_WIDTH 34
#define PLAYER_ATTACKING_FORWARD 15
#define PLAYER_SITTING_BACKWARD 7
#define PLAYER_THROW_SPRITE_WIDTH 27
#define PLAYER_THROWING_FORWARD 5

// ===== Các thông số cho WEAPON SWORD ====
#define WEAPON_SWORD_WIDTH 32
#define WEAPON_SWORD_HEIGHT 18
#define WEAPON_BLUESHURIKEN_WIDTH 10
#define WEAPON_BLUESHURIKEN_HEIGHT 10
#define WEAPON_BLUESHURIKEN_SPEED 0.25f
#define WEAPON_SWINGSWORD_WIDTH 18
#define WEAPON_SWINGSWORD_HEIGHT 18
#define WEAPON_BULLET_WIDTH 18
#define WEAPON_BULLET_HEIGHT 12
#define WEAPON_DAGGER_WIDTH 11
#define WEAPON_DAGGER_HEIGHT 23
#define WEAPON_FIREWHEEL_WIDTH 35
#define WEAPON_FIREWHEEL_HEIGHT 35
#define WEAPON_FIREWHEEL_SPEED 0.14f

// ===== CÁC THÔNG SỐ CHO ENEMIES ====
#define ENEMY_FROZEN_TIME 3000
#define ENEMY_SWORDMAN_WIDTH 24
#define ENEMY_SWORDMAN_HEIGHT 40
#define ENEMY_SWORDMAN_SPEED 0.02f
#define ENEMY_GUNMAN_WIDTH 30
#define ENEMY_GUNMAN_HEIGHT 40
#define ENEMY_GUNMAN_SPEED 0.02f
#define ENEMY_GUNMAN_DELAY_TIME 1800
#define ENEMY_CLOAKMAN_WIDTH 24
#define ENEMY_CLOAKMAN_HEIGHT 40
#define ENEMY_CLOAKMAN_SPEED 0.012f
#define ENEMY_CLOAKMAN_DELAY_TIME 1200
#define ENEMY_PANTHER_WIDTH 32
#define ENEMY_PANTHER_HEIGHT 16
#define ENEMY_EAGLE_WIDTH 26
#define ENEMY_EAGLE_HEIGHT 26
#define ENEMY_EAGLE_MIN_SPEEDX 2.5f
#define ENEMY_EAGLE_MIN_SPEEDY 1.5f
#define ENEMY_EAGLE_DELAY_TIME 2000

// ===== CÁC THÔNG SỐ CHO HOLDERS & ITEM ====
#define HOLDER_WIDTH 20
#define HOLDER_HEIGHT 20
#define ITEM_EXISTS_TIME 2000
#define ITEM_WIDTH 20
#define ITEM_HEIGHT 20
#define ITEM_SPEED 0.14f

// ====== BULLET =======
#define BULLET_CLOAKMAN_WIDTH 18
#define BULLET_CLOAKMAN_HEIGHT 18
#define BULLET_CLOAKMAN_JUMPING_SPEED 0.28f
#define BULLET_CLOAKMAN_FALLING_SPEED 0.25f
#define BULLET_CLOAKMAN_SPEED 0.08f
#define BULLET_CLOAKMAN_COUNT 1
#define BULLET_GUNMAN_WIDTH 18
#define BULLET_GUNMAN_HEIGHT 12
#define BULLET_GUNMAN_SPEED 0.15f
#define BULLET_GUNMAN_COUNT 3

// ===== CAMERA =====
#define camera Camera::GetInstance()
#define scoreboard ScoreBoard::GetInstance()
extern HINSTANCE hInstance;										// hInstance của windows hiện tại
extern HWND hWnd;												// hWnd hiện tại
extern LPD3DXSPRITE spriteHandler;								// SpriteHanlder hiện tại
extern LPDIRECT3DDEVICE9 d3ddev;								// Device directX hiện tại (nhằm đại diện card màn hình)
extern LPDIRECT3DSURFACE9 backBuffer;							// BackBuffer
extern bool isGameRunning;										// Kiểm tra trạng thái game đang chạy
extern bool isFrozenEnemies;
extern int frozenEnemiesTime;
extern std::unordered_map<int, bool> keyCode;

// === ENUM dùng định dạng loại Object và State ====

extern enum Tag
{
	PLAYER,
	ITEM,
	WEAPON,
	GROUND,
	MAP1,
	ENEMY,
	HOLDER,
	BULLET,
	FONT,
};

extern enum Type
{
	NONE,
	SWORD,
	SWINGSWORD,
	SWORDMAN,
	BAZOKAMAN,
	GUNMAN,
	PANTHER,
	CLOAKMAN,
	EAGLE,
	BUTTERFLY,
	DAGGER,
	EXPLODED,
	BLUESPIRIT,
	REDSPIRIT,
	GLASSHOUR,
	BLUESHURIKEN,
	REDBAG,
	BLUEBAG,
	FIREWHEEL,
	REDPOTION,
};

extern enum State
{
	MOVING,
	STANDING,
	RUNNING,
	JUMPING,
	FALLING,
	SITTING,
	ATTACKING,
	ATTACKING_STAND,
	ATTACKING_SIT,
	THROWING,
	CLINGING,
	CLIMBING,
	FLYING,
	ACTIVE,
	DEAD,
	INJURED
};

struct Rect
{
	float x, y;
	float width, height;

	Rect() {}
	Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	bool IsContain(Rect r)
	{
		return !((x + width < r.x) || (x > r.x + r.width) || (y < r.y - r.height) || (y - height > r.y));
	}
};

struct Wall
{
	Rect rect;
	bool climbable;
	
	Wall() {}
	Wall(float x, float y, float width, float height, bool climbable)
	{
		this->rect.x = x;
		this->rect.y = y;
		this->rect.width = width;
		this->rect.height = height;
		this->climbable = climbable;
	}
};