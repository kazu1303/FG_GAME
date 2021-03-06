#include "Locus.h"
#include"DxLib.h"
#include"Display.h"


Locus::Locus(Vector2* position)
	:Particle(position, 50, 3.0f)
{
	//移動量をランダム決定
	velocity = new Vector2((float)(GetRand(5) - 3), (float)(GetRand(5) - 3));
}


Locus::~Locus()
{
}

//毎フレーム処理
void Locus::Update()
{
	Particle::Update();
}

//描画処理
void Locus::Draw()
{
	Display::Instance()->SetScreen(Particle_Screen);
	//円の描画
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
}


