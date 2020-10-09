#include "Player.h"
#include "Smoke.h"
#include "PlayerBullet.h"
#include "Display.h"
#include "DxLib.h"
#include "Sound.h"
#include "Renderer.h"
#include "FiringSmoke.h"
#include "DeathParticle.h"
#include "Block.h"

Player::Player(Vector2* position)
	:Entity("player_leg1",position, player, true,1.5f,25)
{
	Initialize();
}

Player::~Player()
{
	delete pointer;
	pointer = nullptr;
}

//初期化処理
void Player::Initialize()
{
	//タイマー設定
	particleTimer = Timer(0.05f, true);
	bulletTimer = Timer(0.1f, true);
	invincibleTimer = Timer(1.0f, true);
	deathTimer = Timer(2.0f, false);

	pointer = new Pointer();
	maxHp = hp;
	angle = 180;
	invincible = false;
	isDeadFlag = false;
	drop = false;
}

//毎フレーム処理
void Player::Update()
{
	firing = false;
	float speed = 2;
	velocity->Zero();
	pointer->Update();
	//死亡処理
	if (isDeadFlag)
	{
		deathTimer.Update();
		//deathTimerがfalseの時死亡演出
		if (!deathTimer.IsTime())
		{
			DeathMotion();
		}
		//deathTimerがtrueの時死亡
		else
		{
			isDead = true;
		}
		return;
	}

	//無敵処理
	Invincible();

	//angleを0から360内に収める
	if (angle >= 360) angle = 0;
	else if (angle < 0) angle = 345;

	//落下処理
	if (drop)
	{
		repel = false;
		Drop();
		return;
	}
	drop = true;
	hitCount = 0;

	//はじかれる処理
	if (repel)
	{
		Repel();
		return;
	}

	//移動処理
	Move();
	Firing();
		//動いた時のパーティクル
	if (velocity->x != 0 ||
		velocity->y != 0)
	{
		particleTimer.Update();
		//trueの時煙を生成
		if (particleTimer.IsTime())
		{
			for (int i = 0; i < 5; i++)
			{
				new Smoke(position);
			}
		}
	}
	else
	{
		particleTimer.Max();
	}
	
	//位置設定
	velocity->x *= speed;
	velocity->y *= speed;
	GameObject::Update();

	//体力が0以下の時死亡処理
	if (hp <= 0)
	{
		alpha = 255;
		isDeadFlag = true;
	}
}

//移動
void Player::Move()
{
	//移動処理
	float angleSpeed = 15.0f;
	//上方向への移動
	if (CheckHitKey(KEY_INPUT_W))
	{
		//上向いてたら移動
		if (angle == 0)
		{
			velocity->y = -1;
		}
		//移動方向への回転
		else if (angle >= 180)
		{
			angle += angleSpeed;
		}
		else if (angle < 180)
		{
			angle -= angleSpeed;
		}
	}
	//下方向への移動
	else if (CheckHitKey(KEY_INPUT_S))
	{
		//下向いていたら移動
		if (angle == 180)
		{
			velocity->y = 1;
		}
		//移動方向への回転
		else if (angle >= 0 && angle < 180)
		{
			angle += angleSpeed;
		}
		else if (angle < 360 && angle > 180)
		{
			angle -= angleSpeed;
		}
	}
	//右方向への移動
	else if (CheckHitKey(KEY_INPUT_D))
	{
		//右向いていたら移動
		if (angle == 90)
		{
			velocity->x = 1;
		}
		//移動方向への回転
		else if (angle >= 270 && angle < 360 || angle < 90 && angle >= 0)
		{
			angle += angleSpeed;
		}
		else if (angle < 270 && angle >90)
		{
			angle -= angleSpeed;
		}
	}
	//左方向への移動
	else if (CheckHitKey(KEY_INPUT_A))
	{
		//左向いていたら移動
		if (angle == 270)
		{
			velocity->x = -1;
		}
		//移動方向への回転
		else if (angle >= 90 && angle < 270)
		{
			angle += angleSpeed;
		}
		else if (angle < 90 && angle >= 0 || angle > 270 && angle <= 360)
		{
			angle -= angleSpeed;
		}
	}
}

//描画処理
void Player::Draw()
{
	//プレイヤーの描画
	SetDrawBlendMode(DX_BLENDMODE_HALF_ADD, alpha);
	Display::Instance()->SetScreen(PlayerLeg_Screen);
	Renderer::Instance()->DrawTexture1(Name, position, angle, scaleX);
	Display::Instance()->SetScreen(PlayerHead_Screen);
	//頭の描画
	HeadDraw();
	//体力ゲージの描画
	DrawDamageGauge();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 50);
	Display::Instance()->SetScreen(Particle_Screen);
	pointer->Draw();
}

//ヒット処理
void Player::Hit(GameObject * obj)
{
	//敵やボスの攻撃のヒット処理
	if (obj->GetType() == enemy ||
		obj->GetType() == bossbom ||
		obj->GetType() == bosslaser ||
		obj->GetType() == bossmissile)
	{
		//無敵でないときダメージ処理
		if (!invincible)
		{
			float damage = 5;
			hp -= damage;
			invincible = true;
		}
		//ミサイルにヒットしたときはじかれる
		if (obj->GetType() == bossmissile)
		{
			RepelDirection(obj->GetPos());
			repel = true;
		}
	}

	//ブロックの外に出ないように補正
	if ((obj->GetType() == block ||
		obj->GetType() == newblock ||
		obj->GetType() == respawn) &&
		hitCount == 0)
	{
		drop = false;
		//ブロックの外に少しでも出てたら位置を戻す
		if (allarea <= sizeX * sizeY - 1)
		{
			position->x -= velocity->x;
			position->y -= velocity->y;
			hitCount++;
		}
	}

	//回復処理
	if (obj->GetType() == heal)
	{
		float heal = 10;
		hp += heal;
		//maxhpより回復しない
		if (hp >= maxHp)
		{
			hp = maxHp;
		}
	}

	//障害物に触れたとき戻す
	if (obj->GetType() == obstacle)
	{
		position->x -= velocity->x;
		position->y -= velocity->y;
	}
}

//HPゲージの描画
void Player::DrawDamageGauge()
{
	//最大の体力ゲージの描画
	float gaugesizex = maxHp;
	int gaugesizey = 5;
	DrawBox((int)(position->x - gaugesizex), (int)(position->y - gaugesizey + sizeY), (int)(position->x + gaugesizex), (int)(position->y + sizeY), GetColor(0, 0, 0), 1);
	//現在の体力ゲージの描画
	float rate = hp / maxHp;
	float currentGaugesizex = gaugesizex * rate;
	DrawBox((int)(position->x - gaugesizex), (int)(position->y - gaugesizey + sizeY), (int)(position->x - gaugesizex + currentGaugesizex * 2), (int)(position->y + sizeY), GetColor(255, 200,255), 1);
}

//砲台の描画
void Player::HeadDraw()
{
	//マウスと自機の座標から向きを取得
	float ratioX = pointer->GetPosX() - position->x;
	float ratioY = pointer->GetPosY() - position->y;
	//頭の向きの取得
	float headAngle = atan2(ratioY, ratioX);
	headAngle = (float)(headAngle * (180.0 / PI) + 90);
	float length = sqrtf((ratioX * ratioX) + (ratioY * ratioY));
	int reverse = -1;
	ratioX /= (length * reverse);
	ratioY /= (length * reverse);
	//弾発射時頭を少し後ろに下げる
	if (firing)
	{
		Renderer::Instance()->DrawTexture1("player_head", new Vector2(position->x + ratioX * 4.0f, position->y + ratioY * 4.0f), headAngle, scaleX);
	}
	//通常時positionの位置に頭を描画
	else
	{
		Renderer::Instance()->DrawTexture1("player_head", position ,headAngle, scaleX);
	}
}

void Player::Firing()
{
	//弾の発射
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		bulletTimer.Update();
		//bullettimerがtrueの時弾の発射と演出
		if (bulletTimer.IsTime())
		{
			Sound::Instance()->PlaySE("firing");
			new PlayerBullet(position, (float)pointer->GetPosX(), (float)pointer->GetPosY());
			for (int i = 0; i < 10; i++)
			{
				new FiringSmoke(position);
			}
			firing = true;
		}
	}
	//マウスが押されてないときすぐに発射できるように
	else
	{
		bulletTimer.Max();
	}
}

//無敵処理
void Player::Invincible()
{
	//無敵時間の処理
	if (invincible)
	{
		invincibleTimer.Update();
		//点滅処理
		int addAlpha = 50;
		//addAlphaの数値をalphaによって変更
		if (alpha <= 0)
		{
			addAlpha = 50;
		}
		else if(alpha >= 255)
		{
			addAlpha = -50;
		}
		//invincibleTimerがtrueの時無敵時間終了
		if (invincibleTimer.IsTime())
		{
			invincible = false;
			invincibleTimer.Reset();
		}
		alpha += addAlpha;
	}
	else//無敵でないときはalphaを255に
	{
		alpha = 255;
	}
}

//死亡の真偽(死亡演出用)
bool Player::IsDeadFlag()
{
	return isDeadFlag;
}

//死亡時の処理
void Player::DeathMotion()
{
	//ランダムな時にパーティクル生成
	if (GetRand(5) == 0)
	{
		new DeathParticle(position, sizeX, sizeY);
	}
}

//ミサイルにヒット時の吹き飛ぶ方向決め
void Player::RepelDirection(Vector2 * otherPos)
{
	float radian = atan2(position->y - otherPos->y, position->x - otherPos->x);
	int angle = (int)(radian * 180 / PI + 180);
	//角度を90度の倍数に変更
	angle = (angle + 45) / 90 * 90;
	radian = ((float)angle * PI) / 180.0f;
	aimPos = Vector2(position->x + (Block::blockSize * -cos(radian)), position->y + (Block::blockSize * -sin(radian)));
}

//吹っ飛び処理
void Player::Repel()
{
	//移動量の取得
	velocity->x = (aimPos.x - position->x) / 20.0f;
	velocity->y = (aimPos.y - position->y) / 20.0f;
	GameObject::Update();
	//目的地付近で停止
	if (abs(position->x - aimPos.x) < 1 &&
		abs(position->y - aimPos.y) < 1)
	{
		repel = false;
		velocity->Zero();
	}
}

//海に落ちたときの処理
void Player::Drop()
{
	//だんだん小さく
	float smallScale = 0.05f;
	alpha = 255;
	scaleX -= smallScale;
	scaleY = scaleX;
	//小さくなったらリスポーン地点で復活
	if (scaleX <= 0 && scaleY <= 0)
	{
		int damege = 5;
		//スポーン地点に設定
		position->ReSetting(360.0f, 360.0f);
		drop = false;
		hp -= damege;
		invincibleTimer.Reset();
		scaleX = 1.5f;
		scaleY = 1.5f;
		invincible = true;
	}
}

