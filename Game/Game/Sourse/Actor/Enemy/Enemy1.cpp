#include "Enemy1.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"
#include "Explode.h"


Enemy1::Enemy1(Vector2* position,float angle)
	:Enemy("dragonfly",position,3,1)
{
	this->angle = angle;
	Initialize();
}

Enemy1::~Enemy1()
{
}

//初期化処理
void Enemy1::Initialize()
{
	stopTimer = Timer(0.2f, true);
	changedir = false;
	stop = false;
}

//毎フレーム処理
void Enemy1::Update()
{
	//1度のみ敵とプレイヤーの座標から方向を決める
	if (!changedir)
	{
		iniVel = Ratio();
		changedir = true;
	}
	stopTimer.Update();
	//一定時間毎に停止する
	if (stopTimer.IsTime())
	{
		stop = !stop;
	}
	//stopがtrueの時動かない
	if (stop)
	{
		int speed = 0;
		velocity->x = iniVel.x * speed;
		velocity->y = iniVel.y * speed;
	}
	//stopがfalseの時動く
	else
	{
		int speed = 5;
		velocity->x = iniVel.x * speed;
		velocity->y = iniVel.y * speed;
	}
	//体力が0以下の時
	if (hp <= 0)
	{
		isDead = true;
		//10個、爆発の煙を生成
		for (int i = 0; i < 10; i++)
		{
			new Explode(position);
		}
		//死んだらブロックを生む
		Sound::Instance()->PlaySE("explode");
		position->x -= ((int)position->x) % Block::blockSize;
		position->y -= ((int)position->y) % Block::blockSize;
		new CenterBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
	}
	Enemy::Update();
}

//描画処理
void Enemy1::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1(Name, position, -angle, 3.0f);
}

//ヒット処理
void Enemy1::Hit(GameObject * obj)
{
	//弾にヒットしたら体力を減らす
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
