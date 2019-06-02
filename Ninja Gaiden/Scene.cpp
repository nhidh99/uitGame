#include "Scene.h"

// Load các Resource từ Factory trước khi khởi chạy Game
Scene::Scene()
{
	TextureFactory::GetInstance()->LoadResources();
	SpriteFactory::GetInstance()->LoadResources();
	MapFactory::GetInstance()->LoadResources();
	this->LoadFonts();
}

void Scene::LoadFonts()
{
	//Add các sprite chữ vào SpriteFactory
	int i = 0;
	for (char c = 'A'; c <= 'Z'; c++)
	{
		int left = 9;
		switch (c)
		{
		case 'B':
			left = 28;
			break;
		case 'C':
			left = 46;
			break;
		case 'D':
			left = 62;
			break;
		case 'E':
			left = 81;
			break;
		case 'F':
			left = 99;
			break;
		case 'G':
			left = 117;
			break;
		case 'H':
			left = 135;
			break;
		case 'I':
			left = 155;
			break;
		case 'J':
			left = 171;	
			break;
		case 'K':
			left = 189;
			break;
		case 'L':
			left = 208;
			break;
		case 'M':
			left = 225;
			break;
		case 'N':
			left = 243;
			break;
		case 'O':
			left = 261;
			break;
		case 'P':
			left = 279;
			break;
		case 'Q':
			left = 297;
			break;
		case 'R':
			left = 315;
			break;
		case 'S':
			left = 333;
			break;
		case 'T':
			left = 352;
			break;
		case 'U':
			left = 369;
			break;
		case 'V':
			left = 387;
			break;
		case 'W':
			left = 404;
			break;
		case 'X':
			left = 423;
			break;
		case 'Y':
			left = 441;
			break;
		case 'Z':
			left = 459;
			break;
		}
		int top = 19;
		int right = left + 18;
		int bottom = top + 18;
		SpriteFactory::GetInstance()->AddSprite(new FontSprite(c, left, top, right, bottom));
	}

	//Add các sprite số vào SpriteFactory
	for (char c = '0'; c <= '9'; c++)
	{
		int left = 9 + i * 18;
		int top = 37;
		int right = left + 18;
		int bottom = top + 18;
		SpriteFactory::GetInstance()->AddSprite(new FontSprite(c, left, top, right, bottom));
		i++;
	}

	//Add sprite dấu gạch vào SpriteFactory
	SpriteFactory::GetInstance()->AddSprite(new FontSprite('-', 498, 41, 515, 54));

	//Add health sprite
	SpriteFactory::GetInstance()->AddSprite(new FontSprite('*', 489, 6,	495, 31));
	SpriteFactory::GetInstance()->AddSprite(new FontSprite('*', 533, 6, 539, 31));
}
