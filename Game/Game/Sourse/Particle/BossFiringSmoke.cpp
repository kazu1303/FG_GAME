#include "BossFiringSmoke.h"
#include "DxLib.h"
#include "Display.h"


BossFiringSmoke::BossFiringSmoke(Vector2* position)
	:Particle(position,40,10)
{
	//�i�s�����ݒ�
	velocity = new Vector2((float)(GetRand(360) - 180), (float)(GetRand(360) - 180));
	velocity->Normalize();
	speed = 4;
}


BossFiringSmoke::~BossFiringSmoke()
{
}

//���t���[������
void BossFiringSmoke::Update()
{
	position->x += velocity->x * speed;
	position->y += velocity->y * speed;
	hp--;
	//�傫���ւ�
	scale += addScale;
	if (hp <= 0)
	{
		isDead = true;
	}
	//�傫�����ő�ȏ�ɂ��Ȃ�
	if (scale >= maxscale)
	{
		scale = maxscale;
	}
	//�X�s�[�h��0�ɂȂ�܂Ō��炷
	if (speed > 0)
	{
		speed -= 0.1f;
	}
}

//�`�揈��
void BossFiringSmoke::Draw()
{
	int alpha = 10;
	int halfAlpha = 128;
	Display::Instance()->SetScreen(BossDust_Screen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, hp * alpha);

	//�~�̕`��
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, halfAlpha);
}


