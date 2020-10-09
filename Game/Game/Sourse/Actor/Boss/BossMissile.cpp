#include "BossMissile.h"
#include "Display.h"
#include "Block.h"
#include "Obstacle.h"
#include "DxLib.h"


BossMissile::BossMissile(Vector2* position,int angle)
	:Entity("laser",position, bossmissile, false,6)
{
	this->angle = (float)angle;
	aimPos = Vector2(0.0f, 0.0f);
}


BossMissile::~BossMissile()
{
}

void BossMissile::Initialize()
{
}

void BossMissile::Update()
{	
	int speed = 2;
	//発射の方向、移動量決め
	if (!changedir)
	{
		//目的地取得
		aimPos = Vector2(otherPos->x - ((int)otherPos->x % Block::blockSize), otherPos->y - ((int)otherPos->y % Block::blockSize));
		aimPos = Vector2((float)(aimPos.x + Block::blockSize / 2), (float)(aimPos.y + Block::blockSize / 2));	
		velocity->x = aimPos.x - position->x;
		velocity->y = aimPos.y - position->y;
		velocity->Normalize();
		//初期位置設定
		int fixScale = 100;
		position->x = position->x + velocity->x * fixScale;
		position->y = position->y + velocity->y * fixScale;
		Vector2 iniVel(aimPos.x - position->x, aimPos.y - position->y);
		iniLength = iniVel.Length();
		changedir = true;
	}
	//目的地までの距離の取得
	float currentLength = sqrtf(((aimPos.x - position->x)* (aimPos.x - position->x)) + ((aimPos.y - position->y) * (aimPos.y - position->y)));
	
	//目的地付近で止まり障害物生成
	if (abs(aimPos.x - position->x) < 1 &&
		abs(aimPos.y - position->y) < 1)
	{
		//目的地付近で停止、ブロック生成
		position->x -= ((int)position->x) % Block::blockSize;
		position->y -= ((int)position->y) % Block::blockSize;
		new Obstacle(&Vector2((float)(position->x + Block::blockSize / 2),(float)(position->y + Block::blockSize / 2)));
		entity = true;
		isDead = true;
	}
	//目的地付近にいない場合移動量と大きさ取得
	else
	{
		//距離の比率から大きさを変える
		scaleX += 0.5f * ((currentLength - iniLength / 2) / iniLength / 2);
	}
	Entity::Update();
	scaleY = scaleX;
	sizeX = imageSizeX * scaleX;
	sizeY = imageSizeY * scaleY;
}

//描画処理
void BossMissile::Draw()
{
	Display::Instance()->SetScreen(BossAttack_Screen);
	//DrawCircle(position->x, position->y, imageSizeX * scaleX, GetColor(128, 128, 128), 1, 1);
	DrawBox((int)(position->x - sizeX / 2),(int)( position->y - sizeY / 2), (int)(position->x + sizeX / 2 + 1), (int)(position->y + sizeY / 2 + 1), GetColor(255, 0, 0), 1);
}

//ヒット処理
void BossMissile::Hit(GameObject * obj)
{
}
