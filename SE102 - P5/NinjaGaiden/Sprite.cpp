#include "Sprite.h"

// Constructor khởi tạo Sprite từ loại Object và tọa độ khung hình chữ nhật bao quanh Sprite
Sprite::Sprite(Tag tag, int left, int top, int right, int bottom)
{
	_tag = tag;
	_isFlipHorizontal = false;

	// Kích thước RECT dùng để "cắt" một phần Texture tạo Sprite
	_rect.top = top;
	_rect.left = left;
	_rect.right = right;
	_rect.bottom = bottom;

	// Kích thước Sprite (có thể định lại tùy nhân vật vì RECT đã đủ dùng cho Sprite)
	_width = right - left;
	_height = bottom - top;
}

void Sprite::SetWidth(int width)
{
	_width = width;
}

void Sprite::SetHeight(int height)
{
	_height = height;
}

int Sprite::GetWidth()
{
	return _width;
}

int Sprite::GetHeight()
{
	return _height;
}

// Render Sprite lên màn hình tại tọa độ x,y kèm theo vector tịnh tuyến
// Update: Có thể cải biên hàm nếu Object đòi hỏi thêm các thuộc tính như xoay, lật...
void Sprite::Render(float x, float y, float translateX, float translateY)
{
	// Các thông số dùng cho hàm vẽ Sprite và biến đổi ma trận (nếu có) để thực hiện phép biến hình
	// Với tâm phép biến hình và tâm Sprite sẽ lấy tại điểm chính giữa của Sprite
	auto texture = TextureFactory::GetInstance()->GetTexture(_tag);
	auto pCenter = D3DXVECTOR3(_width >> 1, _height >> 1, 0);
	auto pPosition = D3DXVECTOR3(x, y, 0);
	auto pRotationCenter = D3DXVECTOR2(_width >> 1, _height >> 1);
	auto pScalingCenter = D3DXVECTOR2(x, y);
	auto pTranslation = D3DXVECTOR2(translateX, translateY);
	auto pScaling = D3DXVECTOR2(_isFlipHorizontal ? -1 : 1, 1);

	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, &pTranslation);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	spriteHandler->Draw(texture, &_rect, &pCenter, &pPosition, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}

void Sprite::FlipHorizontal(bool flag)
{
	_isFlipHorizontal = flag;
}

RECT Sprite::GetRect()
{
	return _rect;
}

Tag Sprite::GetTag()
{
	return _tag;
}