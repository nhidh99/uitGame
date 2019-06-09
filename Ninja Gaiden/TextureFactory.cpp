#include "TextureFactory.h"

TextureFactory* TextureFactory::_instance = NULL;

// Load các Texture cần dùng cho Game
void TextureFactory::LoadResources()
{
	auto textures = TextureFactory::GetInstance();
	textures->AddTexture(PLAYER, "Resources\\player.png");
	textures->AddTexture(MAP1, "Resources\\tiles1.png");
	textures->AddTexture(MAP2, "Resources\\tiles2.png");
	textures->AddTexture(MAP3, "Resources\\tiles3.png");
	textures->AddTexture(ITEM, "Resources\\item.png");
	textures->AddTexture(ENEMY, "Resources\\enemy.png");
	textures->AddTexture(FONT, "Resources\\font.png");
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