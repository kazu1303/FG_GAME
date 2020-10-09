#include "GameObject.h"
#include "GameObjectManager.h"
#include "DxLib.h"
#include "Renderer.h"

using namespace std;

GameObject::GameObject(string name, Vector2* position, CharaType type, bool entity, float scale, int hp)
{
	this->Name = name;
	this->position = new Vector2(position->x,position->y);
	this->type = type;
	this->entity = entity;
	isDead = false;
	allarea = 0;
	this->hp = hp;
	//ブロックとその他で加える位置を分ける
	if (type == block ||
		type == newblock ||
		type == obstacle ||
		type == respawn)
	{
		GameObjectManager::Instance()->AddBlock(this);
	}
	//ブロック以外画像有の処理
	else
	{
		//画像サイズから大きさ決め
		GetGraphSize(Renderer::Instance()->Texture(Name),&imageSizeX, &imageSizeY);
		sizeX = imageSizeX * scale;
		sizeY = imageSizeY * scale;
		scaleX = scale;
		scaleY = scale;
		GameObjectManager::Instance()->Add(this);
	}
	Initialize();
}

GameObject::~GameObject()
{
	delete position;
	position = nullptr;
	delete velocity;
	velocity = nullptr;
	delete otherPos;
	otherPos = nullptr;
}

//初期化処理
void GameObject::Initialize()
{
	velocity = new Vector2(0, 0);
}

//毎フレーム処理
void GameObject::Update()
{
	position->x += velocity->x;
	position->y += velocity->y;
}

//描画処理
void GameObject::Draw()
{
}

//死亡の真偽
bool GameObject::IsDead()
{
	return isDead;
}

//ヒット処理
void GameObject::Hit(GameObject* obj)
{
}

//同オブジェクトかの真偽
bool GameObject::Equal(GameObject* other)
{
	return this == other;
}

//基本的な当たり判定（四角形）
bool GameObject::IsCollision(GameObject * other)
{
	//現在の距離を求める
	float lengthX = abs(this->position->x - other->position->x);
	float lengthY = abs(this->position->y - other->position->y);
	//	オブジェクトの当たり判定
	if ((lengthX <= (this->sizeX + other->sizeX) / 2) &&
		(lengthY <= (this->sizeY + other->sizeY) / 2))
	{
		return true;
	}
	return false;
}

//ブロック同士の当たり判定
bool GameObject::BBCollision(GameObject * other)
{
	float lengthX = abs(this->position->x - other->position->x);
	float lengthY = abs(this->position->y - other->position->y);
	//XY距離が自分と相手のサイズ/２を足した値より小さい場合はヒットしているのでtrueを返す
	if ((lengthX < (this->sizeX + other->sizeX) / 2 - 1) &&
		(lengthY < (this->sizeY + other->sizeY) / 2 - 1))
	{
		return true;
	}
	return false;
}

//島内のプレイヤーの面積計算
void GameObject::IsBlock(GameObject * other)
{
	float area = 0;
	Vector2 beforePos = Vector2(position->x, position->y);
	if (this->GetType() == player)
	{		
		this->position->x += velocity->x;
		this->position->y += velocity->y;
		//ブロックと自機のXとYの距離を求める
		float lengthX = abs(this->position->x - other->position->x);
		float lengthY = abs(this->position->y - other->position->y);
		//距離がそれぞれのサイズを足したものより小さい場合ヒットしているので面積計算
		if (((lengthX <= (other->sizeX / 2 + this->sizeX)) &&
			(lengthY <= (other->sizeY / 2 + this->sizeY))))
		{			
			//辺を求める
			float neightX = abs(other->sizeX / 2 - lengthX);
			float neightY = abs(other->sizeY / 2 - lengthY);

			//ブロックの大きさの半分より距離が小さい場合辺にプレイヤーの大きさの半分をプラス
			if (lengthX < other->sizeX / 2) neightX += this->sizeX / 2;
			//ブロックの大きさの半分より距離が大きい場合辺にプレイヤーの大きさの半分をプラス
			else if (lengthX >= other->sizeX / 2) neightX -= this->sizeX / 2;
			//ブロックの大きさの半分より距離が小さい場合辺にプレイヤーの大きさの半分をプラス
			if (lengthY < other->sizeY / 2)	neightY += this->sizeY / 2;
			//ブロックの大きさの半分より距離が大きい場合辺にプレイヤーの大きさの半分をプラス
			else if (lengthY >= other->sizeX / 2)neightY -= this->sizeY / 2;
			//辺を自然数に
			neightX = abs(neightX);
			neightY = abs(neightY);
			//サイズより辺の方が大きい場合プレイヤーのサイズに合わせる
			if (sizeX <= neightX)neightX = sizeX;
			if (sizeY <= neightY)neightY = sizeY;
			//ブロック内の面積を取得
			area = neightX * neightY;
			allarea += area;
		}
	}
	//座標をもとに戻す
	this->position->x = beforePos.x;
	this->position->y = beforePos.y;
}

//島内のプレイヤー面積をリセット
void GameObject::ResetIsBlock()
{
	allarea = 0;
}

//ヒットした方向を返す
Direction GameObject::CheckDirection( GameObject * other)
{	
	float lengthX = abs(this->position->x - other->position->x);
	float lengthY = abs(this->position->y - other->position->y);
	//内側からの当たった方向
	if (other->GetType() == block &&
		this->GetType() != block)
	{
		//XよりYの方が遠い場合
		if (lengthX < lengthY)
		{
			//相手より自分がyが大きい場合下に触れている
			if (this->position->y >= other->position->y) return Bottom;
			//相手より自分がyが小さい場合上に触れている
			else if (this->position->y <= other->position->y) return Top;
		}
		//YよりXの方が遠い場合
		else if (lengthY < lengthX)
		{
			//相手より自分がxが小さい場合左に触れている
			if (this->position->x < other->position->x)	return Left;
			//それ以外は右に触れている
			else return Right;
		}
	}
	//外側からの当たった方向
	else
	{
		lengthX -= (this->sizeX + other->sizeX);
		lengthY -= (this->sizeY + other->sizeY);
		//XよりYの方が遠い場合
		if (lengthX < lengthY)
		{
			//相手より自分がyが小さい場合下に触れている
			if (this->position->y < other->position->y) return Bottom;
			//相手より自分がyが大きい場合上に触れている
			else if (this->position->y > other->position->y) return Top;
		}
		//YよりXの方が遠い場合
		else
		{
			//相手より自分がxが大きい場合左に触れている
			if (this->position->x > other->position->x)	return Left;
			//それ以外は右に触れている
			else return Right;
		}
	}
}

//キャラタイプを返す
CharaType GameObject::GetType()
{
	return type;
}

//当たり判定の真偽
bool GameObject::EntityObject()
{
	return entity;
}

//オブジェクトの座標を返す
Vector2* GameObject::GetPos()
{
	return position;
}

//主にプレイヤーの座標を設定する用
void GameObject::SetPlayerPos(Vector2* position, CharaType type)
{
	//プレイヤーの座標だけ保存
	if (type == player)
	{
		otherPos = new Vector2(position->x, position->y);
	}

}




