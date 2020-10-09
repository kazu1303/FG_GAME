#pragma once
#include <vector>
#include <memory>

#include "GameObject.h"
#include "Player.h"
#include "GameStart.h"
#include "Boss.h"

//オブジェクトを管理するクラス
class GameObjectManager
{
private:
	static GameObjectManager* instance;//インスタンス
	//ブロック以外のオブジェクトを入れるよう
	static std::vector<std::shared_ptr<GameObject>> gameObjects;//キャラを格納
	static std::vector<std::shared_ptr<GameObject>> addgameObjects;//新しく生成したキャラを格納
	//ブロックのオブジェクトを入れるよう
	static std::vector<std::shared_ptr<GameObject>> blockObjects;//地面や壁を格納
	static std::vector<std::shared_ptr<GameObject>> addblockObjects;//新しく生成したブロックを格納
	static Player* sPlayer;//Player監視用
	static GameStart* sStart;//GameStart監視用
	static Boss* sBoss;//Boss監視用
public:
	GameObjectManager();
	//インスタンス
	static GameObjectManager* Instance();
	//初期化処理
	void Initialize();
	//ブロック以外のキャラを配列に加える
	void Add(GameObject* obj);
	//ブロックを配列に加える
	void AddBlock(GameObject* obj);
	//毎フレーム処理
	void Update();
	//描画処理
	void Draw();
	//ブロックの描画処理
	void BlockDraw();
	//ヒット処理
	void HitToObject();
	//プレイヤーが最も近い方向を返す
	int PlayerPos();
	//スタートするか
	bool Start();
	//死んだか
	bool GameOver();
	//クリアしたか
	bool GameClear();
	//クリアしたか
	bool ClearFlag();
	//生成されたブロックの数を返す
	int BlockNum();
	~GameObjectManager();
};