#include "Enemy.h"


Enemy::Enemy(std::string name,Vector2* position,float scale,int hp)
	:Entity(name,position, enemy, true,scale,hp)
{
}


Enemy::~Enemy()
{
}

//主にプレイヤーの座標をセット
void Enemy::SetPlayerPos(Vector2 * position, CharaType type)
{
	//プレイヤーのみ目的地に設定
	if (type == player )
	{
		iniPos = Vector2(position->x,position->y);
	}
}

//目的までのベクトルの単位ベクトル
Vector2 Enemy::Ratio()
{
	Vector2 ratio;
	ratio.x = iniPos.x - position->x;
	ratio.y = iniPos.y - position->y;
	ratio.Normalize();
	return ratio;
}

//毎フレーム処理
void Enemy::Update()
{
	//スポーン地点より外に出たら死亡
	if (position->x > 900 ||
		position->y > 820 ||
		position->x < -100 ||
		position->y < -180)
	{
		isDead = true;
	}
	GameObject::Update();
}




