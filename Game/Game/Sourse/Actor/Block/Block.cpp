#include "Block.h"
#include "DxLib.h"
#include "Display.h"
#include "Screen.h"
const int Block::blockSize = 48;


Block::Block(Vector2* position, CharaType type, float sizeX,float sizeY,bool entity)
	:Entity(" ",position,type,entity)
{
	this->position = new Vector2(floor(position->x), floor(position->y));
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}


Block::~Block()
{
}

//����������
void Block::Initialize()
{
}

//���t���[������
void Block::Update()
{
	//��ʊO�ɂ͐������Ȃ�
	if (position->x > Screen::WinWidth ||
		position->y > Screen::WinHight ||
		position->x < Screen::WinWidth - Screen::WinWidth ||
		position->y < Screen::WinHight - Screen::WinHight)
	{
		isDead = true;
	}
}

//�`�揈��
void Block::Draw()
{
	Display::Instance()->SetScreen(Block_Screen);
	//���݂̃T�C�Y���ݒ肵���T�C�Y��菬�����ꍇ�ݒ�T�C�Y�̎l�p�`��h��Ԃ��Ȃ��`��
	if (sizeX < blockSize)
	{
		DrawBox((int)(position->x - (blockSize / 2)), (int)(position->y - blockSize / 2), (int)(position->x + blockSize / 2 + 1), (int)(position->y + blockSize / 2 + 1), GetColor(0, 255, 0), 0);
	}
	DrawBox((int)(position->x - sizeX / 2), (int)(position->y - sizeY / 2), (int)(position->x + sizeX / 2 + 1), (int)(position->y + sizeY / 2 + 1), GetColor(0, 255, 0), 1);
}

//�q�b�g����
void Block::Hit(GameObject * obj)
{
	//�ŏ����炠��n�ʂɐG�ꂽ�Ƃ����S
	if (obj->GetType() == respawn)
	{
		isDead = true;
	}
	//�u���b�N���d�Ȃ��Ă���V�����u���b�N������
	if (obj->GetType() == block &&
		this->GetType() == newblock)
	{
		isDead = true;		
	}
	//��Q���ɐG�ꂽ�Ƃ����S
	if ((this->GetType() == block || this->GetType() == newblock) && 
		obj->GetType() == obstacle)
	{
		isDead = true;
	}
	//�����Ŏ��S
	if (obj->GetType() == bombexplosion)
	{
		isDead = true;
	}
}

