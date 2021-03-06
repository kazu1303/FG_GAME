#include "FiringSmoke.h"
#include"DxLib.h"
#include"Display.h"


FiringSmoke::FiringSmoke(Vector2* position)
	:Particle(position, 10, 3)
{
	//進行方向決め
	velocity = new Vector2((float)(GetRand(360) - 180), (float)(GetRand(360) - 180));
	velocity->Normalize();
}


FiringSmoke::~FiringSmoke()
{
}

//毎フレーム処理
void FiringSmoke::Update()
{
	Particle::Update();
}

//描画処理
void FiringSmoke::Draw()
{
	int alpha = 25;
	Display::Instance()->SetScreen(Firing_Screen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, hp * alpha);

	//円の描画
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
}


