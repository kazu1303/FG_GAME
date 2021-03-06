#include "Enemy3.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"
#include "Locus.h"

const float spawnlength = 500;

Enemy3::Enemy3(Vector2* position,float angle)
	:Enemy("bird",position,3,3)
{
	this->angle = angle;

}


Enemy3::~Enemy3()
{
}

//初期化処理
void Enemy3::Initialize()
{
	chaseSpeed = 2.0f;
	changedir = false;
}

//毎フレーム処理
void Enemy3::Update()
{
	float addAngle = 2;
	angle+= addAngle;
	if (angle >= 360)
	{
		angle = 0;
	}
	//方向決め
	if (!changedir)
	{
		iniVel = Ratio();
		changedir = true;
	}
	//目的地に着いたら逆に進む
	if (abs(iniPos.x - position->x) < 10 && abs(iniPos.y - position->y) < 10)
	{
		chaseSpeed = -2.0f;
	}
	//円を描くように移動
	Vector2 lengthXY = Vector2(iniPos.x - position->x, iniPos.y - position->y);
	float length = lengthXY.Length();
	velocity->AngleToVector(angle);
	position->x = iniPos.x + velocity->x * (length - chaseSpeed);
	position->y = iniPos.y + velocity->y * (length - chaseSpeed);
	//スポーン地点の外に出たら死亡
	if (position->x > 900 ||
		position->y > 820 ||
		position->x < -100 ||
		position->y < -180)
	{
		isDead = true;
	}
	new Locus(position);
	//体力が0の時死亡処理
	if (hp <= 0)
	{
		isDead = true;
		Sound::Instance()->PlaySE("explode");
		//死んだらブロック生成3*3
		position->x -= ((int)position->x) % Block::blockSize;
		position->y -= ((int)position->y) % Block::blockSize;
		new CenterBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
	}
}

//描画処理
void Enemy3::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1(Name,position, -angle + 90.0f, 3.0f);
}

//ヒット処理
void Enemy3::Hit(GameObject * obj)
{
	//弾にヒットしたら体力を減らす
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
