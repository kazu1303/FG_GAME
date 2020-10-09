#include "Locus.h"
#include"DxLib.h"
#include"Display.h"


Locus::Locus(Vector2* position)
	:Particle(position, 50, 3.0f)
{
	//�ړ��ʂ������_������
	velocity = new Vector2((float)(GetRand(5) - 3), (float)(GetRand(5) - 3));
}


Locus::~Locus()
{
}

//���t���[������
void Locus::Update()
{
	Particle::Update();
}

//�`�揈��
void Locus::Draw()
{
	Display::Instance()->SetScreen(Particle_Screen);
	//�~�̕`��
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
}


