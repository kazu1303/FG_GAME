#include "Enemy1.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"
#include "Explode.h"


Enemy1::Enemy1(Vector2* position,float angle)
	:Enemy("dragonfly",position,3,1)
{
	this->angle = angle;
	Initialize();
}

Enemy1::~Enemy1()
{
}

//����������
void Enemy1::Initialize()
{
	stopTimer = Timer(0.2f, true);
	changedir = false;
	stop = false;
}

//���t���[������
void Enemy1::Update()
{
	//1�x�̂ݓG�ƃv���C���[�̍��W������������߂�
	if (!changedir)
	{
		iniVel = Ratio();
		changedir = true;
	}
	stopTimer.Update();
	//��莞�Ԗ��ɒ�~����
	if (stopTimer.IsTime())
	{
		stop = !stop;
	}
	//stop��true�̎������Ȃ�
	if (stop)
	{
		int speed = 0;
		velocity->x = iniVel.x * speed;
		velocity->y = iniVel.y * speed;
	}
	//stop��false�̎�����
	else
	{
		int speed = 5;
		velocity->x = iniVel.x * speed;
		velocity->y = iniVel.y * speed;
	}
	//�̗͂�0�ȉ��̎�
	if (hp <= 0)
	{
		isDead = true;
		//10�A�����̉��𐶐�
		for (int i = 0; i < 10; i++)
		{
			new Explode(position);
		}
		//���񂾂�u���b�N�𐶂�
		Sound::Instance()->PlaySE("explode");
		position->x -= ((int)position->x) % Block::blockSize;
		position->y -= ((int)position->y) % Block::blockSize;
		new CenterBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
	}
	Enemy::Update();
}

//�`�揈��
void Enemy1::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1(Name, position, -angle, 3.0f);
}

//�q�b�g����
void Enemy1::Hit(GameObject * obj)
{
	//�e�Ƀq�b�g������̗͂����炷
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
