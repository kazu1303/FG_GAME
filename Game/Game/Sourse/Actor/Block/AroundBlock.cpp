#include "AroundBlock.h"

AroundBlock::AroundBlock(Vector2* position)
	:Block(position,newblock,2.0f,2.0f,false)
{
	typeChange = Timer(0.05f, false);
}

AroundBlock::~AroundBlock()
{
}

//���t���[������
void AroundBlock::Update()
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
void AroundBlock::Draw()
{
	Block::Draw();
}
