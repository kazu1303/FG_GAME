#include "DeathParticle.h"
#include"DxLib.h"
#include"Display.h"


DeathParticle::DeathParticle(Vector2* position, float sizeX, float sizeY)
	:Particle(position,20,sizeX / 4)
{
	//”š”­‚ðo‚·ˆÊ’u‚ðƒ‰ƒ“ƒ_ƒ€Ý’è
	this->position = new Vector2((float)(position->x - GetRand((int)sizeX) + (sizeX / 2)), (float)(position->y - GetRand((int)sizeY) + (sizeY / 2)));
}


DeathParticle::~DeathParticle()
{
}

//–ˆƒtƒŒ[ƒ€ˆ—
void DeathParticle::Update()
{
	Particle::Update();
}

//•`‰æˆ—
void DeathParticle::Draw()
{
	Display::Instance()->SetScreen(Particle_Screen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 128);

	//‰~‚Ì•`‰æ
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
}


