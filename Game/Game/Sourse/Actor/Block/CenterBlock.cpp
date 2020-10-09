#include "CenterBlock.h"
#include "Heart.h"
#include "DxLib.h"

CenterBlock::CenterBlock(Vector2* position)
	:Block(position,newblock,2,2,false)
{
	typeChange = Timer(0.5f, false);
}


CenterBlock::~CenterBlock()
{
}

//���t���[������
void CenterBlock::Update()
{
	//�傫���Ȃ鉉�o����
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

	//�ݒ肵�����Ԍo�߂��ĂȂ��Ƃ��^�C�}�[�̏���
	if (!typeChange.IsTime())
	{
		typeChange.Update();
	}
	//�o�߂����ꍇ�L�����^�C�v���Â��̂���block�ɕύX
	else
	{
		type = block;
	}
	Block::Update();
}

//�`�揈��
void CenterBlock::Draw()
{
	Block::Draw();
}

//�q�b�g����
void CenterBlock::Hit(GameObject * obj)
{
	//���g�̃^�C�v��newblock�����肪block�̏ꍇ�A�C�e���𐶂ݎ��S
	if (obj->GetType() == block &&
		this->GetType() == newblock)
	{
		isDead = true;
		//������Ƃ������_���ɉ񕜃A�C�e���𐶂�
		int itemID = GetRand(3);
		//0�̎������A�C�e������
		if (itemID == 0)
		{
			new Heart(position);
		}
	}
	//�q�b�g���Ă���̂�obstacle�Ȃ玀�S
	if (obj->GetType() == obstacle)
	{
		isDead = true;
	}
	Block::Hit(obj);
}
