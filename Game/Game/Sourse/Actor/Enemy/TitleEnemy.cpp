#include "TitleEnemy.h"
#include "GameStart.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"
#include "Explode.h"
#include "Screen.h"

TitleEnemy::TitleEnemy(Vector2* position, int enemyNum)
	:Enemy("dragonfly",position,3,1)
{
	this->enemyNum = enemyNum;
	Initialize();
}

TitleEnemy::~TitleEnemy()
{
}

//初期化処理
void TitleEnemy::Initialize()
{
	//出現させるエネミー設定
	//Enemy1の設定
	if (enemyNum == 1)
	{
		sizeX = 51;
		sizeY = 51;
		scaleX = 3;
		Name = "dragonfly";
		hp = 1;
	}
	//Enemy2の設定
	else if (enemyNum == 2)
	{
		sizeX = 32;
		sizeY = 32;
		scaleX = 4;
		Name = "meteorite";
		hp = 2;
	}
	//Enmey3の設定
	else if (enemyNum == 3)
	{
		sizeX = 27;
		sizeY = 27;
		scaleX = 3;
		Name = "bird";
		hp = 3;
	}
	angle = 0;
}

//毎フレーム処理
void TitleEnemy::Update()
{
	//体力が0以下の時死亡
	if (hp <= 0)
	{
		isDead = true;
	}
	//死亡処理
	if (isDead)
	{
		//死んだら爆発
		for (int i = 0; i < 10; i++)
		{
			new Explode(position);
		}
		//死んだらエネミーに合わせたブロックを生成
		Sound::Instance()->PlaySE("explode");
		position->x -= (int)(position->x) % Block::blockSize;
		position->y -= (int)(position->y) % Block::blockSize;
		new CenterBlock(new Vector2(position->x + Block::blockSize / 2, position->y + Block::blockSize / 2));
		//Enemy1の死亡時ブロック生成
		if (enemyNum == 1)
		{
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
			new TitleEnemy(new Vector2((float)(Block::blockSize * 8 + Block::blockSize / 2), (float)(Block::blockSize * 10 + Block::blockSize / 2)), 2);
		}
		//Enemy2の死亡時ブロック生成
		else if (enemyNum == 2)
		{
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
			new TitleEnemy(new Vector2((float)(Block::blockSize * 11 + Block::blockSize / 2), (float)(Block::blockSize * 9 + Block::blockSize / 2)), 3);
		}
		//Enemy3の死亡時ブロック生成
		else if (enemyNum == 3)
		{
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new GameStart(new Vector2((float)(Screen::WinWidth / 2), (float)(Screen::WinHight / 2)));
		}
	}
}

//描画処理
void TitleEnemy::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1("attack", new Vector2(position->x + sizeX / 2, position->y - sizeY), 0.0f,1);
	//Enemy1の描画
	if (enemyNum == 1)
	{
		Renderer::Instance()->DrawTexture1(Name, position, angle, scaleX);
	}
	//Enemy2の描画
	else if (enemyNum == 2)
	{
		Renderer::Instance()->DrawTexture1(Name, position, angle);
	}
	//Enemy3の描画
	else if (enemyNum == 3)
	{
		Renderer::Instance()->DrawTexture1(Name, position, angle + 90.0f, scaleX);
	}
}

//ヒット処理
void TitleEnemy::Hit(GameObject * obj)
{
	//弾にヒットしたら体力を減らす
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
