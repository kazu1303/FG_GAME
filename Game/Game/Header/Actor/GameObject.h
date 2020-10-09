#pragma once
#include <string>

#include "Vector2.h"


enum Direction
{
	Top,
	Bottom,
	Right,
	Left
};

enum CharaType
{
	block,
	newblock,
	respawn,
	obstacle,

	player,
	bullet,

	enemy,

	heal,
	start,

	boss,
	bosslaser,
	bossbom,
	bossmissile,
	bombexplosion,
};

//オブジェクトの基底クラス
class GameObject
{
protected:
	Vector2* position = new Vector2(0,0);//座標
	Vector2* velocity = new Vector2(0,0);//移動量
	Vector2* otherPos = new Vector2(0,0);//主にプレイヤーの座標
	float sizeX, sizeY;//サイズ
	int imageSizeX, imageSizeY;//画像のサイズ
	float scaleX,scaleY;//拡縮率
	float angle,drawAngle;//実際の角度、描画の際の角度
	float allarea;//島内のプレイヤー面積
	int hp;//体力
    bool isDead;//死亡真偽
	bool entity;//当たり判定真偽
	std::string Name;//画像の名前
	CharaType type;//キャラクターのタイプ
public:
	GameObject(std::string name,Vector2* position, CharaType type, bool entity, float scale = 1.0f,int hp = 1);
	virtual ~GameObject();
	//初期化処理
	virtual void Initialize();
	//毎フレーム処理
	virtual void Update();
	//描画処理
	virtual void Draw();
	//死亡の真偽
	bool IsDead();
	//ヒット処理
	virtual void Hit(GameObject* obj);
	//同オブジェクトかの真偽
	bool Equal( GameObject* other);
	//基本的な当たり判定（四角形）
	bool IsCollision(GameObject* other);
	//ブロック同士の当たり判定
	bool BBCollision(GameObject* other);
	//島内のプレイヤーの面積計算
	void IsBlock(GameObject* other);
	//島内のプレイヤー面積をリセット
	void ResetIsBlock();
	//ヒットした方向を返す
	Direction CheckDirection( GameObject* other);
	//キャラタイプを返す
	virtual CharaType GetType();
	//当たり判定の真偽
	virtual bool EntityObject();
	//オブジェクトの座標を返す
	Vector2* GetPos();
	//主にプレイヤーの座標を設定する用
	virtual void SetPlayerPos(Vector2* position,CharaType type);
};




