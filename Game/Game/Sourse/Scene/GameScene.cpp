#include "GameScene.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

//初期化処理
void GameScene::Initialize()
{
}

//毎フレーム処理
void GameScene::Update()
{
}

//描画処理
void GameScene::Draw()
{
}

//シーン終了
bool GameScene::IsEnd()
{
	return isEnd;
}

//次のシーン
Scene GameScene::Next()
{
	return Scene();
}

//現在のシーン
Scene GameScene::CurrentScene()
{
	return Scene();
}
