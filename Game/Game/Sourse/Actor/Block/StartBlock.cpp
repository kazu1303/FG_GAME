#include "StartBlock.h"
#include "Display.h"
#include "DxLib.h"


StartBlock::StartBlock(Vector2* position)
	:Block(position,respawn, 48, 48)
{
}

StartBlock::~StartBlock()
{
}

//���t���[������
void StartBlock::Update()
{
}

//�`�揈��
void StartBlock::Draw()
{
	Display::Instance()->SetScreen(Block_Screen);
	SetDrawBright(100, 100, 100);
	DrawBox((int)(position->x - blockSize / 2), (int)(position->y - blockSize / 2), (int)(position->x + blockSize / 2 + 1), (int)(position->y + blockSize / 2 + 1), GetColor(0, 255,0), 1);
	SetDrawBright(255, 255, 255);
}

//�q�b�g����
void StartBlock::Hit(GameObject * obj)
{
}
