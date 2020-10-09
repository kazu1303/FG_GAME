#include "Obstacle.h"
#include "DisPlay.h"
#include "DxLib.h"


Obstacle::Obstacle(Vector2* position)
	:Block(position,obstacle,2,2,false)
{
}


Obstacle::~Obstacle()
{
}

//毎フレーム処理
void Obstacle::Update()
{
	//出現時大きく
	if (sizeX < blockSize)
	{
		sizeX += 2;
		sizeY += 2;
	}
	//サイズが定められた大きさになったら当たり判定をつける
	else
	{
		entity = true;
	}
	Block::Update();
}

//描画処理
void Obstacle::Draw()
{
	Display::Instance()->SetScreen(Block_Screen);
	DrawBox((int)(position->x - sizeX / 2), (int)(position->y - sizeY / 2), (int)(position->x + sizeX / 2 + 1), (int)(position->y + sizeY / 2 + 1), GetColor(255, 0, 0), 1);
}

//ヒット処理
void Obstacle::Hit(GameObject * obj)
{
	//ヒットしているオブジェクトのタイプがrespawnとbombexplosionなら死亡
	if (obj->GetType() == respawn ||
		obj->GetType() == bombexplosion)
	{
		isDead = true;
	}
}
