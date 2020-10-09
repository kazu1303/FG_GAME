#pragma once
#include "GameScene.h"

class GameOver :
	public GameScene
{
private:
	bool push;
public:
	GameOver();
	~GameOver();
	//初期化処理
	void Initialize();
	//毎フレーム処理
	void Update();
	//描画処理
	void Draw() override;
	//次のシーン
	virtual Scene Next() override;
	//現在のシーン
	Scene CurrentScene()override;
};

