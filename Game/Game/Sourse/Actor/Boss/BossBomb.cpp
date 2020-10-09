#include "BossBomb.h"
#include "BombExplosion.h"
#include "Display.h"
#include "DxLib.h"
#include "Sound.h"
#include "Block.h"


BossBomb::BossBomb(Vector2* position)
	:Entity("laser", position, bossbom,false, 4)
{
	bomTimer = Timer(2.0f, false);
	red = 0;
	green = 255;
	blue = 255;
	color = 0;
	addscale = 0.3f;
}


BossBomb::~BossBomb()
{
}

//����������
void BossBomb::Initialize()
{
}

//���t���[������
void BossBomb::Update()
{
	int speed = 2;
	//���˂̕����A�ړ��ʌ���
	if (!changedir)
	{
		//�ړI�n�擾
		aimPos = Vector2(otherPos->x - ((int)otherPos->x % Block::blockSize), otherPos->y - ((int)otherPos->y % Block::blockSize));
		aimPos = Vector2((float)(aimPos.x + Block::blockSize / 2), (float)(aimPos.y + Block::blockSize / 2));
		velocity->x = aimPos.x - position->x;
		velocity->y = aimPos.y - position->y;
		velocity->Normalize();
		//�����ʒu�ݒ�
		int fixScale = 100;
		position->x = position->x + velocity->x * fixScale;
		position->y = position->y + velocity->y * fixScale;
		Vector2 iniVel(aimPos.x - position->x, aimPos.y - position->y);
		iniLength = iniVel.Length();
		changedir = true;
	}
	//�ړI�n�܂ł̋����̎擾
	float currentLength = sqrtf(((aimPos.x - position->x)* (aimPos.x - position->x)) + ((aimPos.y - position->y) * (aimPos.y - position->y)));
	
	//�ړI�n�ɂ����甚������
	if (abs(aimPos.x - position->x) < 1 &&
		abs(aimPos.y - position->y) < 1)
	{
		//�ړI�n�t�߂Œ�~�A��������
		entity = true;
		bomTimer.Update();
		velocity->x = 0;
		velocity->y = 0;
		red += 3;
		int maxRed = 255;
		if (red >= maxRed)
		{
			red = 255;
			//color��0�Ȃ�1��
			if (color == 0)
			{
				color = 1;
			}
			//color��1�Ȃ�0��
			else if (color == 1)
			{
				color= 0;
			}
		}
		//bomTimer��true�Ȃ甚�����Ď��S
		if (bomTimer.IsTime())
		{
			isDead = true;
		}
	}
	//����ȊO�͑傫����ς���
	else
	{
		//�����̔䗦����傫����ς���
		scaleX += 0.5f * ((currentLength - iniLength / 2) / iniLength / 2);
	}
	Entity::Update();
	
	//����ł���p�[�e�B�N������
	if (isDead)
	{
		Sound::Instance()->PlaySE("bome");
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				new BombExplosion(position, i, j);
			}
		}
	}
	sizeX = imageSizeX * scaleX;
	sizeY = imageSizeY * scaleY;
}

//�`�揈��
void BossBomb::Draw()
{
	float r = sizeX;
	Display::Instance()->SetScreen(BossAttack_Screen);
	SetDrawBright(red, green * color, blue * color);
    DrawCircle((int)(position->x), (int)(position->y),(int)(r / 2), GetColor(255, 255, 255), 1, 1);
	SetDrawBright(255, 255, 255);
}

//�q�b�g����
void BossBomb::Hit(GameObject * obj)
{
}
