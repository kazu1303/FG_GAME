#include "Obstacle.h"
#include "DisPlay.h"
#include "DxLib.h"


Obstacle::Obstacle(Vector2* position)
	:Block(position,obstacle,2,2,false)
{
}


Obstacle::~Obstacle()
{
}

//���t���[������
void Obstacle::Update()
{
	//�o�����傫��
	if (sizeX < blockSize)
	{
		sizeX += 2;
		sizeY += 2;
	}
	//�T�C�Y����߂�ꂽ�傫���ɂȂ����瓖���蔻�������
	else
	{
		entity = true;
	}
	Block::Update();
}

//�`�揈��
void Obstacle::Draw()
{
	Display::Instance()->SetScreen(Block_Screen);
	DrawBox((int)(position->x - sizeX / 2), (int)(position->y - sizeY / 2), (int)(position->x + sizeX / 2 + 1), (int)(position->y + sizeY / 2 + 1), GetColor(255, 0, 0), 1);
}

//�q�b�g����
void Obstacle::Hit(GameObject * obj)
{
	//�q�b�g���Ă���I�u�W�F�N�g�̃^�C�v��respawn��bombexplosion�Ȃ玀�S
	if (obj->GetType() == respawn ||
		obj->GetType() == bombexplosion)
	{
		isDead = true;
	}
}
