#pragma once
#include "GameObject.h"
//当たり判定を持つオブジェクトのクラス
class Entity :
	public GameObject
{
public:
	Entity(std::string name, Vector2* position, CharaType type, bool entity = true, float scale = 1, int hp = 1);
	~Entity();
	//初期化処理
	virtual void Initialize()override;
	//毎フレーム処理
	virtual void Update()override;
	//描画処理
	virtual void Draw()override;
	//ヒット処理
	virtual void Hit(GameObject* obj)override;
};

