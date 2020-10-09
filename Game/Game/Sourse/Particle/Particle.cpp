#include "Particle.h"
#include "ParticleManager.h"
#include "DxLib.h"

Particle::Particle(Vector2* position,int maxhp,float maxscale)
{
	this->position = new Vector2(position->x,position->y);
	velocity = new Vector2(0, 0);
	hp = GetRand(maxhp) + maxhp / 2;
	this->maxscale = maxscale;
	this->scale = 1;
	addScale = this->maxscale / this->hp;
	isDead = false;
	ParticleManager::Instance()->Add(this);
}


Particle::~Particle()
{
	delete position;
	position = nullptr;
	delete velocity;
	velocity = nullptr;
}

//€–S^‹U
bool Particle::IsDead()
{
	return isDead;
}

//‰Šú‰»ˆ—
void Particle::Initialize()
{
}

//–ˆƒtƒŒ[ƒ€ˆ—
void Particle::Update()
{
	position->x += velocity->x;
	position->y += velocity->y;
	hp--;
	scale += addScale;
	//hp‚ªƒ[ƒ‚æ‚è’á‚¢ê‡Á‚·
	if (hp <= 0)
	{
		isDead = true;
	}
	//Å‘å‚Ì‘å‚«‚³‚æ‚èŒ»İ‚Ì‘å‚«‚³‚ª‘å‚«‚¢ê‡Á‚·
	if (scale >= maxscale)
	{
		isDead = true;
	}
}

//•`‰æˆ—
void Particle::Draw()
{
}
