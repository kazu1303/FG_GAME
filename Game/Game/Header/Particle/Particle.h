#pragma once
#include "Vector2.h"


//パーティクルの親クラス
class Particle
{
protected:
	Vector2* position;//座標
	Vector2* velocity;//移動量
	int hp,maxhp;//現在のhp,最大のhp
	float scale,maxscale,addScale;//現在の大きさ、最大の大きさ、大きくなる比率
	bool isDead;//死亡真偽
public:
	Particle(Vector2* position,int maxhp, float scale);
	~Particle();
	//死亡真偽
	bool IsDead();
	//初期化処理
	virtual void Initialize();
	//毎フレーム処理
	virtual void Update();
	//描画処理
	virtual void Draw();
};

