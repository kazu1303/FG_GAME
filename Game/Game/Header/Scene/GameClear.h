#pragma once
#include "GameScene.h"

class GameClear :
	public GameScene
{
private:
	bool push;
public:
	GameClear();
	~GameClear();
	//初期化処理
	void Initialize()override;
	//毎フレーム処理
	void Update()override;
	//描画処理
	void Draw() override;
	//次のシーン
	virtual Scene Next() override;
	//現在のシーン
	Scene CurrentScene()override;
};

