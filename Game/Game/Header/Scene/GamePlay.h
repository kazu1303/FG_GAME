#pragma once
#include "GameScene.h"
#include "Timer.h"

class GamePlay:
	public GameScene
{
private:
	bool boss;
	Timer enemy1Summon;//トンボの生成間隔
	Timer enemy2Summon;//隕石の生成間隔
	Timer enemy3Summon;//鳥の生成間隔
public:
	GamePlay();
	~GamePlay();
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

