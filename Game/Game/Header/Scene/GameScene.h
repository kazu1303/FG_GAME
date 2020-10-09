#pragma once

enum Scene
{
	title,
	gamePlay,
	gameClear,
	gameOver,
	load
};

//シーンの親クラス
class GameScene
{
protected:
	bool isEnd;
public:
	GameScene();
	~GameScene();
	//初期化処理
	virtual void Initialize();
	//毎フレーム処理
	virtual void Update();
	//描画処理
	virtual void Draw();
	//シーン終了
	virtual bool IsEnd();
	//次のシーン
	virtual Scene Next();
	//現在のシーン
	virtual Scene CurrentScene();
};

