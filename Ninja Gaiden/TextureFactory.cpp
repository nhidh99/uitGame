#include "TextureFactory.h"

TextureFactory* TextureFactory::instance = NULL;

// Load các Texture cần dùng cho Game
void TextureFactory::LoadResources()
{
	auto textures = TextureFactory::GetInstance();
	textures->AddTexture(PLAYER, "Resources\\Textures\\player.png");
	textures->AddTexture(MAP1, "Resources\\Textures\\tiles1.png");
	textures->AddTexture(MAP2, "Resources\\Textures\\tiles2.png");
	textures->AddTexture(MAP3, "Resources\\Textures\\tiles3.png");
	textures->AddTexture(ITEM, "Resources\\Textures\\item.png");
	textures->AddTexture(ENEMY, "Resources\\Textures\\enemy.png");
	textures->AddTexture(FONT, "Resources\\Textures\\font.png");
	textures->AddTexture(INTROSCENE, "Resources\\Textures\\intro.png");
	textures->AddTexture(ENDSCENE, "Resources\\Textures\\end.png");
}

// Thêm một Texture vào danh sách, quy định theo Tag
void TextureFactory::AddTexture(Tag tag, const char * filePath)
{
	textures[tag] = (new Texture(filePath))->GetTexture();
}

TextureFactory* TextureFactory::GetInstance()
{
	if (instance == NULL)
		instance = new TextureFactory();
	return instance;
}

LPDIRECT3DTEXTURE9 TextureFactory::GetTexture(Tag tag)
{
	switch (tag)
	{
	case HOLDER: case ITEM: case WEAPON:
		return textures[ITEM];
	case ENEMY: case BULLET:
		return textures[ENEMY];
	default:
		return textures[tag];
	}
}