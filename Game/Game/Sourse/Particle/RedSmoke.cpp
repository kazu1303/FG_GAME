#include "RedSmoke.h"
#include"DxLib.h"
#include"Display.h"


RedSmoke::RedSmoke(Vector2* position, int maxhp, float scale = 1)
	:Particle(position, maxhp, scale)
{
	//�ړ��ʂ������_������
	velocity = new Vector2((float)(GetRand(2) - 1), (float)(GetRand(2) - 1));
}


RedSmoke::~RedSmoke()
{
}

//���t���[������
void RedSmoke::Update()
{
	Particle::Update();
}

//�`�揈��
void RedSmoke::Draw()
{
	Display::Instance()->SetScreen(Particle_Screen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 128);

	//�~�̕`��
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 0, 0), 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 50);
}


