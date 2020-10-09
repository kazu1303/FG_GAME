#include "FiringSmoke.h"
#include"DxLib.h"
#include"Display.h"


FiringSmoke::FiringSmoke(Vector2* position)
	:Particle(position, 10, 3)
{
	//�i�s��������
	velocity = new Vector2((float)(GetRand(360) - 180), (float)(GetRand(360) - 180));
	velocity->Normalize();
}


FiringSmoke::~FiringSmoke()
{
}

//���t���[������
void FiringSmoke::Update()
{
	Particle::Update();
}

//�`�揈��
void FiringSmoke::Draw()
{
	int alpha = 25;
	Display::Instance()->SetScreen(Firing_Screen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, hp * alpha);

	//�~�̕`��
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
}


