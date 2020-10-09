#include "CenterBlock.h"
#include "Heart.h"
#include "DxLib.h"

CenterBlock::CenterBlock(Vector2* position)
	:Block(position,newblock,2,2,false)
{
	typeChange = Timer(0.5f, false);
}


CenterBlock::~CenterBlock()
{
}

//毎フレーム処理
void CenterBlock::Update()
{
	//大きくなる演出処理
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

	//設定した時間経過してないときタイマーの処理
	if (!typeChange.IsTime())
	{
		typeChange.Update();
	}
	//経過した場合キャラタイプを古いのからblockに変更
	else
	{
		type = block;
	}
	Block::Update();
}

//描画処理
void CenterBlock::Draw()
{
	Block::Draw();
}

//ヒット処理
void CenterBlock::Hit(GameObject * obj)
{
	//自身のタイプがnewblockかつ相手がblockの場合アイテムを生み死亡
	if (obj->GetType() == block &&
		this->GetType() == newblock)
	{
		isDead = true;
		//消えるときランダムに回復アイテムを生む
		int itemID = GetRand(3);
		//0の時だけアイテム生成
		if (itemID == 0)
		{
			new Heart(position);
		}
	}
	//ヒットしているのがobstacleなら死亡
	if (obj->GetType() == obstacle)
	{
		isDead = true;
	}
	Block::Hit(obj);
}
