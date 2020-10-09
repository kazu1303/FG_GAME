#include "Smoke.h"
#include "DxLib.h"
#include"Display.h"

Smoke::Smoke(Vector2* position)
	:Particle(position,20,10)
{
	//�ړ��ʂ������_������
	velocity = new Vector2((float)(GetRand(360) - 180), (float)(GetRand(360) - 180));
	velocity->Normalize();
}

Smoke::~Smoke()
{
}

//���t���[������
void Smoke::Update()
{
	Particle::Update();
}

//�`�揈��
void Smoke::Draw()
{
	Display::Instance()->SetScreen(CloudofDust_Screen);
	//hp������ɂ�ď����Ă�������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, hp * 12);
	//�~�̕`��
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(124, 73, 28), 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


