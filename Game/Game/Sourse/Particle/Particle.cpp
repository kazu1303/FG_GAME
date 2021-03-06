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

//死亡真偽
bool Particle::IsDead()
{
	return isDead;
}

//初期化処理
void Particle::Initialize()
{
}

//毎フレーム処理
void Particle::Update()
{
	position->x += velocity->x;
	position->y += velocity->y;
	hp--;
	scale += addScale;
	//hpがゼロより低い場合消す
	if (hp <= 0)
	{
		isDead = true;
	}
	//最大の大きさより現在の大きさが大きい場合消す
	if (scale >= maxscale)
	{
		isDead = true;
	}
}

//描画処理
void Particle::Draw()
{
}
