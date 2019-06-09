#include "Scene.h"

// Load các Resource từ Factory trước khi khởi chạy Game
Scene::Scene()
{
	TextureFactory::GetInstance()->LoadResources();
	SpriteFactory::GetInstance()->LoadResources();
	MapFactory::GetInstance()->LoadResources();
	this->LoadFonts();
	this->LoadSound();
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

void Scene::LoadSound()
{
	Sound::getInstance()->loadSound((char*)"Resources/Sound/01.wav", "sound1");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/02.wav", "sound2");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/03.wav", "sound3");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/04.wav", "sound4");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/05.wav", "sound5");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/06.wav", "sound6");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/07.wav", "sound7");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/08.wav", "sound8");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/09.wav", "sound9");//score gain
	Sound::getInstance()->loadSound((char*)"Resources/Sound/10.wav", "sound10");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/11.wav", "sound11");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/12.wav", "sound12");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/13.wav", "sound13");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/14.wav", "sound14");//score gain
	Sound::getInstance()->loadSound((char*)"Resources/Sound/15.wav", "sound15");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/16.wav", "sound16");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/17.wav", "sound17");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/18.wav", "sound18"); //Gunman
	Sound::getInstance()->loadSound((char*)"Resources/Sound/19.wav", "sound19");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/20.wav", "sound20");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/21.wav", "sound21");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/22.wav", "sound22");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/23.wav", "sound23");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/24.wav", "sound24");//gunman
	Sound::getInstance()->loadSound((char*)"Resources/Sound/25.wav", "sound25");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/26.wav", "sound26");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/27.wav", "sound27");//bazokaman
	Sound::getInstance()->loadSound((char*)"Resources/Sound/28.wav", "sound28");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/29.wav", "sound29");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/30.wav", "sound30");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/31.wav", "sound31");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/32.wav", "sound32");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/33.wav", "sound33");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/34.wav", "sound34");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/35.wav", "sound35");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/Stage3-1.wav", "stage3-1");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/Stage3-2.wav", "stage3-2");
	Sound::getInstance()->loadSound((char*)"Resources/Sound/Stage3-3.wav", "stage3-3");
}
