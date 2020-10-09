#include "AroundBlock.h"

AroundBlock::AroundBlock(Vector2* position)
	:Block(position,newblock,2.0f,2.0f,false)
{
	typeChange = Timer(0.05f, false);
}

AroundBlock::~AroundBlock()
{
}

//毎フレーム処理
void AroundBlock::Update()
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
void AroundBlock::Draw()
{
	Block::Draw();
}
