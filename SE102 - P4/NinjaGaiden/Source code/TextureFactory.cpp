#include "TextureFactory.h"

TextureFactory* TextureFactory::_instance = NULL;

// Load các Texture cần dùng cho Game
void TextureFactory::LoadResources()
{
	TextureFactory::GetInstance()->AddTexture(PLAYER, "player.png");
	TextureFactory::GetInstance()->AddTexture(ITEM, "item.png");
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
	return _textures[tag];
}