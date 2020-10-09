#include "Enemy2.h"
#include "RedSmoke.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"

Enemy2::Enemy2(Vector2* position,float angle)
	:Enemy("meteorite",position,4,2)
{
	this->angle = angle;
	Initialize();
}


Enemy2::~Enemy2()
{
}

//初期化処理
void Enemy2::Initialize()
{
	changedir = false;
}

//毎フレーム処理
void Enemy2::Update()
{
	float speed = 7;
	//進む方向決め
	if (!changedir)
	{
		iniVel = Ratio();
		changedir = true;
	}
	//移動量決め
	velocity->x = iniVel.x * speed;
	velocity->y = iniVel.y * speed;
	new RedSmoke(position, 20, 20);
	//体力が0の時死亡処理
	if (hp <= 0)
	{
		isDead = true;
		Sound::Instance()->PlaySE("explode");
		//死んだらブロックを生む
		position->x -= ((int)position->x) % Block::blockSize;
		position->y -= ((int)position->y) % Block::blockSize;
		new CenterBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
	}
	Enemy::Update();
}

//描画処理
void Enemy2::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1(Name,position, -angle);
}

//ヒット処理
void Enemy2::Hit(GameObject * obj)
{
	//弾にヒットしたら体力を減らす
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
