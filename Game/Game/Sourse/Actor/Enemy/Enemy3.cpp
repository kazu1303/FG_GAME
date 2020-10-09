#include "Enemy3.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"
#include "Locus.h"

const float spawnlength = 500;

Enemy3::Enemy3(Vector2* position,float angle)
	:Enemy("bird",position,3,3)
{
	this->angle = angle;

}


Enemy3::~Enemy3()
{
}

//����������
void Enemy3::Initialize()
{
	chaseSpeed = 2.0f;
	changedir = false;
}

//���t���[������
void Enemy3::Update()
{
	float addAngle = 2;
	angle+= addAngle;
	if (angle >= 360)
	{
		angle = 0;
	}
	//��������
	if (!changedir)
	{
		iniVel = Ratio();
		changedir = true;
	}
	//�ړI�n�ɒ�������t�ɐi��
	if (abs(iniPos.x - position->x) < 10 && abs(iniPos.y - position->y) < 10)
	{
		chaseSpeed = -2.0f;
	}
	//�~��`���悤�Ɉړ�
	Vector2 lengthXY = Vector2(iniPos.x - position->x, iniPos.y - position->y);
	float length = lengthXY.Length();
	velocity->AngleToVector(angle);
	position->x = iniPos.x + velocity->x * (length - chaseSpeed);
	position->y = iniPos.y + velocity->y * (length - chaseSpeed);
	//�X�|�[���n�_�̊O�ɏo���玀�S
	if (position->x > 900 ||
		position->y > 820 ||
		position->x < -100 ||
		position->y < -180)
	{
		isDead = true;
	}
	new Locus(position);
	//�̗͂�0�̎����S����
	if (hp <= 0)
	{
		isDead = true;
		Sound::Instance()->PlaySE("explode");
		//���񂾂�u���b�N����3*3
		position->x -= ((int)position->x) % Block::blockSize;
		position->y -= ((int)position->y) % Block::blockSize;
		new CenterBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
	}
}

//�`�揈��
void Enemy3::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1(Name,position, -angle + 90.0f, 3.0f);
}

//�q�b�g����
void Enemy3::Hit(GameObject * obj)
{
	//�e�Ƀq�b�g������̗͂����炷
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
