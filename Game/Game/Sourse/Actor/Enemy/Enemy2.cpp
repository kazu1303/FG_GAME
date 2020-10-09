#include "Enemy2.h"
#include "RedSmoke.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"

Enemy2::Enemy2(Vector2* position,float angle)
	:Enemy("meteorite",position,4,2)
{
	this->angle = angle;
	Initialize();
}


Enemy2::~Enemy2()
{
}

//����������
void Enemy2::Initialize()
{
	changedir = false;
}

//���t���[������
void Enemy2::Update()
{
	float speed = 7;
	//�i�ޕ�������
	if (!changedir)
	{
		iniVel = Ratio();
		changedir = true;
	}
	//�ړ��ʌ���
	velocity->x = iniVel.x * speed;
	velocity->y = iniVel.y * speed;
	new RedSmoke(position, 20, 20);
	//�̗͂�0�̎����S����
	if (hp <= 0)
	{
		isDead = true;
		Sound::Instance()->PlaySE("explode");
		//���񂾂�u���b�N�𐶂�
		position->x -= ((int)position->x) % Block::blockSize;
		position->y -= ((int)position->y) % Block::blockSize;
		new CenterBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
	}
	Enemy::Update();
}

//�`�揈��
void Enemy2::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1(Name,position, -angle);
}

//�q�b�g����
void Enemy2::Hit(GameObject * obj)
{
	//�e�Ƀq�b�g������̗͂����炷
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
