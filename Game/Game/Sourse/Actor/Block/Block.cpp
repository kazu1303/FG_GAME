#include "Block.h"
#include "DxLib.h"
#include "Display.h"
#include "Screen.h"
const int Block::blockSize = 48;


Block::Block(Vector2* position, CharaType type, float sizeX,float sizeY,bool entity)
	:Entity(" ",position,type,entity)
{
	this->position = new Vector2(floor(position->x), floor(position->y));
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}


Block::~Block()
{
}

//初期化処理
void Block::Initialize()
{
}

//毎フレーム処理
void Block::Update()
{
	//画面外には生成しない
	if (position->x > Screen::WinWidth ||
		position->y > Screen::WinHight ||
		position->x < Screen::WinWidth - Screen::WinWidth ||
		position->y < Screen::WinHight - Screen::WinHight)
	{
		isDead = true;
	}
}

//描画処理
void Block::Draw()
{
	Display::Instance()->SetScreen(Block_Screen);
	//現在のサイズが設定したサイズより小さい場合設定サイズの四角形を塗りつぶしなし描画
	if (sizeX < blockSize)
	{
		DrawBox((int)(position->x - (blockSize / 2)), (int)(position->y - blockSize / 2), (int)(position->x + blockSize / 2 + 1), (int)(position->y + blockSize / 2 + 1), GetColor(0, 255, 0), 0);
	}
	DrawBox((int)(position->x - sizeX / 2), (int)(position->y - sizeY / 2), (int)(position->x + sizeX / 2 + 1), (int)(position->y + sizeY / 2 + 1), GetColor(0, 255, 0), 1);
}

//ヒット処理
void Block::Hit(GameObject * obj)
{
	//最初からある地面に触れたとき死亡
	if (obj->GetType() == respawn)
	{
		isDead = true;
	}
	//ブロックが重なってたら新しいブロックを消す
	if (obj->GetType() == block &&
		this->GetType() == newblock)
	{
		isDead = true;		
	}
	//障害物に触れたとき死亡
	if ((this->GetType() == block || this->GetType() == newblock) && 
		obj->GetType() == obstacle)
	{
		isDead = true;
	}
	//爆発で死亡
	if (obj->GetType() == bombexplosion)
	{
		isDead = true;
	}
}

