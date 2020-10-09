#include "BombExplosion.h"
#include "DxLib.h"
#include "Block.h"
#include "Display.h"


BombExplosion::BombExplosion(Vector2* position, int X,int Y)
	:Entity("laser",position, bombexplosion,true, 2, 40 + GetRand(10))
{
	maxHp = hp;
	aimPos = new Vector2(position->x + Block::blockSize * X, position->y + Block::blockSize * Y);
}


BombExplosion::~BombExplosion()
{
}

//����������
void BombExplosion::Initialize()
{
}

//���t���[������
void BombExplosion::Update()
{
	//�ڕW���W�܂ł̈ړ��ʌ���
	velocity->x = (aimPos->x - position->x) / hp;
	velocity->y = (aimPos->y - position->y) / hp;
	velocity->Normalize();
	Entity::Update();
	hp--;
	if (hp <= 0)
	{
		isDead = true;
	}
	sizeX = imageSizeX * scaleX;
}

//�`�揈��
void BombExplosion::Draw()
{
	Display::Instance()->SetScreen(Particle_Screen);
	DrawCircle((int)(position->x), (int)(position->y), (int)sizeX, GetColor(255, 255, 255), 1, 1);
}

//�q�b�g����
void BombExplosion::Hit(GameObject * obj)
{
}
