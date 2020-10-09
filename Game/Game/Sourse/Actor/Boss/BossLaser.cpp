#include "BossLaser.h"
#include "Display.h"
#include "Renderer.h"
#include "DxLib.h"


BossLaser::BossLaser(Vector2* position,int count)
	:Entity("laser",position, bosslaser, true,1)
{
	firing = false;
	this->count = count;
	firingTimer = Timer(1.0f, false);
	iniPos = Vector2(position->x, position->y);
}


BossLaser::~BossLaser()
{
}

//初期化処理
void BossLaser::Initialize()
{
}

//毎フレーム処理
void BossLaser::Update()
{
	int speed = 15;
	//溜める処理
	if (count >= 0)
	{
		//大きく
		float addScale = 0.5f;
		scaleX += addScale;
		//常に大砲の先端に
		velocity->x = otherPos->x - position->x;
		velocity->y = otherPos->y - position->y;
		velocity->Normalize();
		//移動方向のアングル取得
		angle = atan2(velocity->y, velocity->x);
		angle = angle * (180.0f / PI) + 90;
		int fixScale = 100;
		position->x = iniPos.x + velocity->x * fixScale;
		position->y = iniPos.y + velocity->y * fixScale;
		velocity->x = velocity->x * speed;
		velocity->y = velocity->y * speed;
	}
	firingTimer.Update();
	//時間経過後発射
	if (firingTimer.IsTime())
	{
		scaleX = 5;
		Entity::Update();
	}
	//画面外で消す
	if (position->x > 900 ||
		position->y > 820 ||
		position->x < -100 ||
		position->y < -180)
	{
		isDead = true;
	}
	count--;
}

//描画処理
void BossLaser::Draw()
{
	Display::Instance()->SetScreen(BossAttack_Screen);
	//発射している間はalhpa200に
	if (firingTimer.IsTime())
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
	}
	//溜めている間はalpha120に
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
	}

	Renderer::Instance()->DrawTexture1(Name, position, angle, scaleX);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
}
