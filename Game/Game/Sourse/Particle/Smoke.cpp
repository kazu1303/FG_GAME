#include "Smoke.h"
#include "DxLib.h"
#include"Display.h"

Smoke::Smoke(Vector2* position)
	:Particle(position,20,10)
{
	//移動量をランダム決定
	velocity = new Vector2((float)(GetRand(360) - 180), (float)(GetRand(360) - 180));
	velocity->Normalize();
}

Smoke::~Smoke()
{
}

//毎フレーム処理
void Smoke::Update()
{
	Particle::Update();
}

//描画処理
void Smoke::Draw()
{
	Display::Instance()->SetScreen(CloudofDust_Screen);
	//hpが減るにつれて消えていく処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, hp * 12);
	//円の描画
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(124, 73, 28), 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


