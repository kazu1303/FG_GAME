#include "Pointer.h"
#include "DxLib.h"



Pointer::Pointer()
{
}


Pointer::~Pointer()
{
}

//�}�E�X�|�C���^�̂����W��Ԃ�
int Pointer::GetPosX()
{
	return mousePosX;
}

//�}�E�X�|�C���^��y���W��Ԃ�
int Pointer::GetPosY()
{
	return mousePosY;
}

//���t���[������
void Pointer::Update()
{
	GetMousePoint(&mousePosX, &mousePosY);
}

//�`�揈��
void Pointer::Draw()
{
	DrawCircle(mousePosX, mousePosY, 10, GetColor(255, 0, 0), 0);
}
