#include "GamePlay.h"
#include"DxLib.h"

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{
}

//初期化処理
void GamePlay::Initialize()
{
	isEnd = false;
}

//毎フレーム処理
void GamePlay::Update()
{
	//ゲーム終了の処理
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		isEnd = true;
		//Sound::Instance()->StopBGM();
	}
}

//描画処理
void GamePlay::Draw()
{
}

//次のシーン
Scene GamePlay::Next()
{
	return gameOver;
}

//現在のシーン
Scene GamePlay::CurrentScene()
{
	return gamePlay;
}
