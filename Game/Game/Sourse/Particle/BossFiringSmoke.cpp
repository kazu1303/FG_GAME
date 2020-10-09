#include "BossFiringSmoke.h"
#include "DxLib.h"
#include "Display.h"


BossFiringSmoke::BossFiringSmoke(Vector2* position)
	:Particle(position,40,10)
{
	//進行方向設定
	velocity = new Vector2((float)(GetRand(360) - 180), (float)(GetRand(360) - 180));
	velocity->Normalize();
	speed = 4;
}


BossFiringSmoke::~BossFiringSmoke()
{
}

//毎フレーム処理
void BossFiringSmoke::Update()
{
	position->x += velocity->x * speed;
	position->y += velocity->y * speed;
	hp--;
	//大きさ替え
	scale += addScale;
	if (hp <= 0)
	{
		isDead = true;
	}
	//大きさを最大以上にしない
	if (scale >= maxscale)
	{
		scale = maxscale;
	}
	//スピードを0になるまで減らす
	if (speed > 0)
	{
		speed -= 0.1f;
	}
}

//描画処理
void BossFiringSmoke::Draw()
{
	int alpha = 10;
	int halfAlpha = 128;
	Display::Instance()->SetScreen(BossDust_Screen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, hp * alpha);

	//円の描画
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, halfAlpha);
}


