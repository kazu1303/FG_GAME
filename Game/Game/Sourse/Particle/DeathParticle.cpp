#include "DeathParticle.h"
#include"DxLib.h"
#include"Display.h"


DeathParticle::DeathParticle(Vector2* position, float sizeX, float sizeY)
	:Particle(position,20,sizeX / 4)
{
	//�������o���ʒu�������_���ݒ�
	this->position = new Vector2((float)(position->x - GetRand((int)sizeX) + (sizeX / 2)), (float)(position->y - GetRand((int)sizeY) + (sizeY / 2)));
}


DeathParticle::~DeathParticle()
{
}

//���t���[������
void DeathParticle::Update()
{
	Particle::Update();
}

//�`�揈��
void DeathParticle::Draw()
{
	Display::Instance()->SetScreen(Particle_Screen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 128);

	//�~�̕`��
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
}


