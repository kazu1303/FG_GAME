#include "Pointer.h"
#include "DxLib.h"



Pointer::Pointer()
{
}


Pointer::~Pointer()
{
}

//マウスポインタのｘ座標を返す
int Pointer::GetPosX()
{
	return mousePosX;
}

//マウスポインタのy座標を返す
int Pointer::GetPosY()
{
	return mousePosY;
}

//毎フレーム処理
void Pointer::Update()
{
	GetMousePoint(&mousePosX, &mousePosY);
}

//描画処理
void Pointer::Draw()
{
	DrawCircle(mousePosX, mousePosY, 10, GetColor(255, 0, 0), 0);
}
