#include "GameObjectManager.h"

using namespace std;

vector<shared_ptr<GameObject>> GameObjectManager::gameObjects;
vector<shared_ptr<GameObject>> GameObjectManager::addgameObjects;
vector<shared_ptr<GameObject>> GameObjectManager::blockObjects;
vector<shared_ptr<GameObject>> GameObjectManager::addblockObjects;
Player* GameObjectManager::sPlayer;
GameStart* GameObjectManager::sStart;
Boss* GameObjectManager::sBoss;

vector<GameObject*>::iterator itr;

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager::GameObjectManager()
{
	instance = this;
	Initialize();
}

//インスタンス
GameObjectManager * GameObjectManager::Instance()
{
	return instance;
}

//初期化処理
void GameObjectManager::Initialize()
{
	//すべてのvectorをクリアしサイズを合わせる
	gameObjects.clear();
	addgameObjects.clear();
	gameObjects.shrink_to_fit();
	addgameObjects.shrink_to_fit();
	blockObjects.clear();
	addblockObjects.clear();
	blockObjects.shrink_to_fit();
	addblockObjects.shrink_to_fit();
	//監視用変数をnullptrに
	sPlayer = nullptr;
	sStart = nullptr;
	sBoss = nullptr;
}

//ブロック以外のキャラを配列に加える
void GameObjectManager::Add(GameObject* obj)
{
	//playerは監視用変数に入れる
	if (obj->GetType() == player)
	{
		sPlayer = (Player*)obj;
	}
	//startは監視用変数に入れる
	if (obj->GetType() == start)
	{
		sStart = (GameStart*)obj;
	}
	//bossは監視用変数に入れる
	if (obj->GetType() == boss)
	{
		sBoss = (Boss*)obj;
	}
	shared_ptr<GameObject> addobj(obj);
	addgameObjects.push_back(addobj);
}

//ブロックを配列に加える
void GameObjectManager::AddBlock(GameObject* obj)
{
	shared_ptr<GameObject> addblock(obj);
	addblockObjects.push_back(addblock);
}

//毎フレーム処理
void GameObjectManager::Update()
{
	//新しく生成されたオブジェクトの追加
	blockObjects.insert(blockObjects.begin(), addblockObjects.begin(),addblockObjects.end());
	gameObjects.insert(gameObjects.end(), addgameObjects.begin(), addgameObjects.end());
	addgameObjects.clear();
	addblockObjects.clear();

	//アップデート
	for (auto obj1 : gameObjects)
	{
		for (auto obj2 : gameObjects)
		{
			obj1->SetPlayerPos(obj2->GetPos(), obj2->GetType());
		}
	}
	//キャラクターの毎フレーム処理
	for (auto itr : gameObjects)
	{
		itr->Update();
	}
	//ブロック類の毎フレーム処理
	for (auto itr : blockObjects)
	{
		itr->Update();
	}
	HitToObject();
	//死亡判定
	//キャラクターの死亡処理
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); )
	{
		//死亡してたらvectorから消す
		if ((*itr)->IsDead())
		{
		    itr  = gameObjects.erase(itr);
		}
		//死亡してなかったら次のオブジェクトを見る
		else
		{
			itr++;
		}
	}
	//ブロック類の死亡処理
	for (auto itr = blockObjects.begin(); itr != blockObjects.end(); )
	{
		//死亡してたらvectorから消す
		if ((*itr)->IsDead())
		{
			itr = blockObjects.erase(itr);
		}
		//死亡してなかったら次のオブジェクトを見る
		else
		{
			itr++;
		}
	}

	//サイズを合わせる
	gameObjects.shrink_to_fit();
	blockObjects.shrink_to_fit();
}

//描画処理
void GameObjectManager::Draw()
{
	for (auto itr : gameObjects)
	{
		itr->Draw();
	}
}

//ブロックの描画処理
void GameObjectManager::BlockDraw()
{
	for (auto itr : blockObjects)
	{
		itr->Draw();
	}
}

//ヒット処理
void GameObjectManager::HitToObject()
{
	//ブロック内のプレイヤーの面積を求める
	for (auto obj1 : gameObjects)
	{
		//プレイヤーの面積だけを求める
		if (obj1->GetType() != player)
		{
			continue;
		}
		//ブロックすべてと当たり判定処理
		for (auto obj2 : blockObjects)
		{
			//障害物は面積を含まない
			if (obj2->GetType() == obstacle)
			{
				continue;
			}
			//プレイヤーとヒットしているブロックだけ面積処理
			if (obj1->IsCollision(obj2.get()))
			{
				obj1->IsBlock(obj2.get());
			}

		}
	}
	//ヒット判定
	for (auto obj1 : gameObjects)
	{
		//当たり判定がない場合処理しない
		if (!obj1->EntityObject())
		{
			continue;
		}
		for (auto obj2 : gameObjects)
		{
			//同じものと当たり判定がないものは処理しない
			if (obj1->Equal(obj2.get()) ||
				!obj2->EntityObject())
			{
				continue;
			}
			//ヒットしていたらヒット時の処理
			if (obj1->IsCollision(obj2.get()))
			{
				obj1->Hit(obj2.get());
			}
		}
	}
	//ブロック同士の当たり判定
	for (auto obj1 : blockObjects)
	{
		//当たり判定がない、または新しいブロックと障害物は当たり判定処理しない
		if (!obj1->EntityObject() ||
			(obj1->GetType() != newblock &&
				obj1->GetType() != obstacle))
		{
			continue;
		}
		for (auto obj2 : blockObjects)
		{
			//同じものと新しいブロックは処理しない
			if (obj1->Equal(obj2.get()) ||
				obj2->GetType() == newblock)
			{
				continue;
			}
			//ヒットしていたらヒット時の処理
			if (obj1->BBCollision(obj2.get()))
			{
				obj1->Hit(obj2.get());
				obj2->Hit(obj1.get());
			}
		}
	}
	//オブジェクトとブロックの当たり判定
	for (auto obj1 : gameObjects)
	{
		//当たり判定がない,またはプレイヤーとボムの爆発以外はブロックとの当たり判定処理しない
		if (!obj1->EntityObject() ||
			(obj1->GetType() != player &&
				obj1->GetType() != bombexplosion))
		{
			continue;
		}
		for (auto obj2 : blockObjects)
		{
			//当たり判定がない場合処理しない
			if (!obj2->EntityObject())
			{
				continue;
			}
			//ヒットしていたらヒット時の処理
			if (obj1->IsCollision(obj2.get()))
			{
				obj1->Hit(obj2.get());
				obj2->Hit(obj1.get());
			}
		}
	}
	//面積のリセット
	for (auto itr : gameObjects)
	{
		itr->ResetIsBlock();
	}
}

int GameObjectManager::PlayerPos()
{
	//プレイヤーが上下左右、どこに近いか返す
	if (sPlayer != nullptr && sPlayer->GetPos()->y < Screen::WinHight / 2)
	{
		if (sPlayer->GetPos()->x < Screen::WinWidth / 2)
		{
			return 2;
		}
		return 1;
	}
	else
	{
		if (sPlayer == nullptr && sPlayer->GetPos()->x < Screen::WinWidth / 2)
		{
			return 3;
		}
		return 0;
	}
}

//スタートするか
bool GameObjectManager::Start()
{
	//sStartが死んでたらゲームをスタートする
	if (sStart != nullptr &&
		sStart->IsDead())
	{
		return true;
	}
	return false;
}

//死んだか
bool GameObjectManager::GameOver()
{
	//sPlayerが死んでたらゲームオーバーにする
	if (sPlayer != nullptr && sPlayer->IsDead())
	{
		return true;
	}
	return false;
}

//クリアしたか（ゲームプレイに返す用）
bool GameObjectManager::GameClear()
{
	//sBossが死んでたらゲームクリアにする
	if (sBoss != nullptr && sBoss->IsDead())
	{
		return true;
	}
	return false;
}

//クリアしたか（このクラス内で使うよう）
bool GameObjectManager::ClearFlag()
{
	//sBossが死んでたらクリアフラグを立てる(ボスの死亡演出のため)
	if (sBoss != nullptr && sBoss->IsDeadFlag())
	{
		return true;
	}
	return false;
}

//生成されたブロックの数を返す
int GameObjectManager::BlockNum()
{
	return blockObjects.size();
}

GameObjectManager::~GameObjectManager()
{
}
