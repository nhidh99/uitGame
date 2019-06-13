#include "Sprite.h"

// Constructor khởi tạo Sprite từ loại Object và tọa độ khung hình chữ nhật bao quanh Sprite
Sprite::Sprite(Tag tag, int left, int top, int right, int bottom)
{
	this->tag = tag;
	texture = TextureFactory::GetInstance()->GetTexture(tag);
	rect.top = top;
	rect.left = left;
	rect.right = right;
	rect.bottom = bottom;
	center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
}

// Render Sprite lên màn hình tại tọa độ x,y kèm theo vector tịnh tuyến
// Update: Có thể cải biên hàm nếu Object đòi hỏi thêm các thuộc tính như xoay, lật...
void Sprite::Render(float x, float y, float translateX, float translateY)
{
	// Các thông số dùng cho hàm vẽ Sprite và biến đổi ma trận (nếu có) để thực hiện phép biến hình
	// Với tâm phép biến hình và tâm Sprite sẽ lấy tại điểm chính giữa của Sprite
	auto pPosition = D3DXVECTOR3(x, y, 0);
	auto pRotationCenter = D3DXVECTOR2(center.x, center.y);
	auto pScalingCenter = D3DXVECTOR2(x, y);
	auto pTranslation = D3DXVECTOR2(translateX, translateY);
	auto pScaling = D3DXVECTOR2(isReverse ? -1 : 1, 1);

	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, &pTranslation);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	spriteHandler->Draw(texture, &rect, &center, &pPosition, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}

void Sprite::ScaleRender(float x, float y, float scaleX, float scaleY, float translateX, float translateY)
{
	auto pPosition = D3DXVECTOR3(x, y, 0);
	auto pRotationCenter = D3DXVECTOR2(center.x, center.y);
	auto pScalingCenter = D3DXVECTOR2(x, y);
	auto pTranslation = D3DXVECTOR2(translateX, translateY);
	auto pScaling = D3DXVECTOR2(scaleX,scaleY);

	D3DXMATRIX oldMatrix, curMatrix;
	D3DXMatrixTransformation2D(&curMatrix, &pScalingCenter, 0, &pScaling, &pRotationCenter, 0, &pTranslation);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&curMatrix);
	spriteHandler->Draw(texture, &rect, &center, &pPosition, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMatrix);
}
