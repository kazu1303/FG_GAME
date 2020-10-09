#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
	instance = this;
	Initialize();
}


SceneManager::~SceneManager()
{
}

//インスタンス
SceneManager* SceneManager::Instance()
{
	return instance;
}

//初期化処理
void SceneManager::Initialize()
{
	if (scenes.empty())
	{
		scenes = std::map<Scene, GameScene*>();
	}
	else
	{
		scenes.clear();
	}
}

//シーン切り替え
void SceneManager::Change(Scene name)
{
	currentScene = scenes[name];
	currentScene->Initialize();
}

//毎フレーム処理
void SceneManager::Update()
{
	currentScene->Update();
	if (currentScene->IsEnd())
	{
		Change(currentScene->Next());
	}
}

//描画処理
void SceneManager::Draw()
{
	currentScene->Draw();
}

//シーンを加える
void SceneManager::Add(Scene name,GameScene* scene)
{
	scenes.insert(std::make_pair(name, scene));
}

//現在のシーン
Scene SceneManager::CurrentScene()
{
	return currentScene->CurrentScene();
}

