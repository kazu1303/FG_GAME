#pragma once
#include <map>
#include "GameScene.h"

class SceneManager
{
private:
	std::map<Scene, GameScene*> scenes;//シーンを保存
	static SceneManager* instance;//インスタンス
	GameScene* currentScene;//処理をするシーン
public:
	SceneManager();
	~SceneManager();
	//インスタンス
	static SceneManager* Instance();
	//初期化処理
	void Initialize();
	//シーン切り替え
	void Change(Scene name);
	//毎フレーム処理
	void Update();
	//描画処理
	void Draw();
	//シーンの追加
	void Add(Scene name,GameScene* scene);
	//現在のシーン
	Scene CurrentScene();
};

