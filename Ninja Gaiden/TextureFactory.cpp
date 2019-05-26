#include "TextureFactory.h"

TextureFactory* TextureFactory::_instance = NULL;

// Load các Texture cần dùng cho Game
void TextureFactory::LoadResources()
{
	TextureFactory::GetInstance()->AddTexture(PLAYER, "Resources\\player.png");
	TextureFactory::GetInstance()->AddTexture(ITEM, "Resources\\item.png");
	TextureFactory::GetInstance()->AddTexture(MAP1, "Resources\\tiles1.png");
	TextureFactory::GetInstance()->AddTexture(ENEMY, "Resources\\Enemy.png");
}

// Thêm một Texture vào danh sách, quy định theo Tag
void TextureFactory::AddTexture(Tag tag, const char * filePath)
{
	_textures[tag] = (new Texture(filePath))->GetTexture();
}

TextureFactory* TextureFactory::GetInstance()
{
	if (_instance == NULL)
		_instance = new TextureFactory();
	return _instance;
}

LPDIRECT3DTEXTURE9 TextureFactory::GetTexture(Tag tag)
{
	switch (tag)
	{
	case HOLDER: case ITEM: case WEAPON:
		return _textures[ITEM];
	case ENEMY: case BULLET:
		return _textures[ENEMY];
	default:
		return _textures[tag];
	}
}