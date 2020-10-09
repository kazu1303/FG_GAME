#include "Boss.h"
#include "BossLaser.h"
#include "BossMissile.h"
#include "BossBomb.h"
#include "BossFiringSmoke.h"
#include "DeathParticle.h"
#include "DxLib.h"
#include "Display.h"
#include "Renderer.h"
#include "Sound.h"


Boss::Boss(Vector2* position)
	:Entity("player_leg1",position,boss,true, 13,100)
{
	addScale = 0.05f;
	rigidTimer = Timer(5.0f, false);
	headPos = Vector2(position->x,position->y);
	headVel = Vector2(0, 0);
	headAngle = 0;
	r = 255;
	g = 255;
	b = 255;
	Initialize();
}


Boss::~Boss()
{
}

//初期化
void Boss::Initialize()
{
	once = false;
	moveStart = true;
	moveEnd = false;
	firing = false;
	isDeadFlag = false;
	state = in;
}

//毎フレーム処理
void Boss::Update()
{
	firing = false;
	//行動決め
	if (!moveStart && !isDeadFlag && !isDead)
	{
		state = (BossState)(GetRand(3));
	}
	//行動処理
	if (!moveEnd && !isDeadFlag)
	{
		//フェードアウト処理
		if (state == out)
		{
			moveStart = true;
			FeadOut();
		}
		//フェードイン処理
		if (state == in)
		{
			FeadIn();
		}
		//ミサイル攻撃処理
		if (state == missile)
		{
			moveStart = true;
			Missile();
		}
		//ボム攻撃処理
		if (state == bomb)
		{
			moveStart = true;
			Bomb();
		}
		//レーザー攻撃処理
		if (state == laser)
		{
			moveStart = true;
			Laser();
		}
	}
	//死亡モーション処理
	if (isDeadFlag)
	{
		DeathMotion();
	}
	//硬直の処理
	if (moveEnd)
	{
		state = idle;
		velocity->Zero();
		headVel.Zero();
		rigidTimer.Update();
		r = 100;
		g = 100;
		b = 100;
		//硬直してない状態に戻す
		if (rigidTimer.IsTime())
		{
			moveStart = false;
			moveEnd = false;
			r = 255;
			g = 255;
			b = 255;
			rigidTimer.Reset();
		}
	}
	//頭の座標決定
	headPos.x += headVel.x;
	headPos.y += headVel.y;
	//死亡処置
	if (hp <= 0)
	{
		state = idle;
		isDeadFlag = true;
	}
	GameObject::Update();
}

//描画処理
void Boss::Draw()
{
	//体の描画
	Display::Instance()->SetScreen(BossLeg_Screen);
	SetDrawBright(r, g, b);
	Renderer::Instance()->DrawTexture3(Name,position, &Vector2((float)imageSizeX / 2, (float)imageSizeY / 2), angle, scaleX, scaleY);
	//頭の描画
	Display::Instance()->SetScreen(BossHead_Screen);
	HeadDraw();
	SetDrawBright(255, 255, 255);
}

//ヒット処理
void Boss::Hit(GameObject * obj)
{
	//弾にヒットしたとき体力減らす
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}

//レーザー発射処理
void Boss::Laser()
{
	int bulletNum = 20;
	int lEndCount = 100;
	//弾を発射した後硬直
	if (count >= lEndCount)
	{
		moveEnd = true;
		count = 0;
		rigidTimer.Resetting(4.0f);
	}
	//カウントが設定した玉の数になるまで弾を生成
	else if(count <= bulletNum)
	{
		Sound::Instance()->PlaySE("boss_laser");
		new BossLaser(position,bulletNum - count);
	}
	count++;
}

//ミサイル発射処理
void Boss::Missile()
{
	int missileCount = 10;
	//一定countが経過したら発射処理
	if (count >= missileCount)
	{
		//大きさが15になるまで小さくする
		if (scaleX > 15)
		{
			float addScaleX = -0.5f;
			scaleX += addScaleX;
		}
		else
		{
			moveEnd = true;
			Sound::Instance()->PlaySE("boss_firing");
			firing = true;
			new BossMissile(position,headAngle);
			int smokeNum = 20;
			for (int i = 0; i < smokeNum; i++)
			{
				new BossFiringSmoke(position);
			}

			count = 0;
			rigidTimer.Resetting(4.0f);
		}
	}
	//発射演出
	else
	{
		//弾を発射するまでモーション処理
		scaleX += addScale;
		//一定の大きさになったらaddScaleを反転
		if (scaleX >= 18 ||
			(addScale < 0 && scaleX <= 17.8f))
		{
			addScale = -addScale;
			count++;
		}
	}
	//現在のボスのいる場所を求める
	float radian = atan2(position->y - Screen::WinHight / 2, position->x - Screen::WinWidth / 2);
	//大きさの変化
	sizeX = imageSizeX * (scaleX * abs(sin(radian)) + scaleY * abs(cos(radian)));
	sizeY = imageSizeY * (scaleX * abs(cos(radian)) + scaleY * abs(sin(radian)));
}

//爆弾発射処理
void Boss::Bomb()
{
	int bombCount = 20;
	//countがbombCountより大きい場合発射処理
	if (count >= bombCount)
	{
		int maxScale = 15;
		float addScale = -0.5f;
		//最大より小さい場合大きくする
		if (scaleX > maxScale)
		{
			scaleX += addScale;
		}
		//最大より大きくなった場合発射処理
		else
		{
			moveEnd = true;
			firing = true;
			Sound::Instance()->PlaySE("boss_firing");
			new BossBomb(position);
			for (int i = 0; i < 20; i++)
			{
				new BossFiringSmoke(position);
			}
			count = 0;
			rigidTimer.Resetting(4.0f);
		}
	}
	//countがbombCountより小さい場合大きさの変更
	else
	{
		scaleX += addScale;
		//大きさが17の時小さくする
		if (scaleX >= 17)
		{
			addScale = -0.1f;
			count++;
		}
		//addScaleが-で大きさが16.f以下の時大きくする
		else if (addScale < 0 && scaleX <= 16.9f)
		{
			addScale = 0.1f;
		}

	}
	scaleY = scaleX;
	sizeX = imageSizeX * scaleX;
	sizeY = imageSizeY * scaleY;
}

//移動（フェードアウト処理）
void Boss::FeadOut()
{
	int speed = 2;
	//フェードアウトする方向の取得
	float radian = atan2(position->y - Screen::WinHight / 2, position->x - Screen::WinWidth / 2);
	//移動長設定
	velocity->x = cos(radian) * speed;
	velocity->y = sin(radian) * speed;
	headVel.x = cos(radian) * speed;
	headVel.y = sin(radian) * speed;
	//画面外に出たらフェードイン処理に
	if (position->x <= 0 - sizeX / 2 ||
		position->x >= Screen::WinWidth + sizeX / 2 ||
		position->y <= 0 - sizeY / 2 ||
		position->y >= Screen::WinHight + sizeY / 2)
	{
		state = in;
	}
}

//移動（フェードイン処理）
void Boss::FeadIn()
{	
	//一度だけ処理
	if (!once)
	{
		//出現する位置の取得
		int pos;
		do {
			pos = GetRand(3);
		} while (pos == posNum);
		posNum = pos;
		//位置を移動
		float radian = atan2(popPos[posNum].y - Screen::WinHight / 2, popPos[posNum].x - Screen::WinWidth / 2);
		position->ReSetting(popPos[posNum].x - (sizeX * -cos(radian)), popPos[posNum].y - (sizeY * -sin(radian)));
		headPos = Vector2(position->x, position->y);
		//体の向き決め
		angle = radian * 180 / PI + 270;
		headAngle = (int)angle + 90;
		once = true;
	}
	//目的地までの移動量設定
	velocity->x = (popPos[posNum].x - position->x) / 30.0f;
	velocity->y = (popPos[posNum].y - position->y) / 30.0f;
	headVel.x = (popPos[posNum].x - position->x) / 30.0f;
	headVel.y = (popPos[posNum].y - position->y) / 30.0f;
	//目的地付近で停止
	if (abs(popPos[posNum].x - position->x) <= 1 &&
		abs(popPos[posNum].y - position->y) <= 1)
	{
	    once = false;
		moveEnd = true;
		rigidTimer.Resetting(1.0f);
	}
}

//砲台の描画処理
void Boss::HeadDraw()
{
	//向き決め
	float ratioX = otherPos->x - position->x;
	float ratioY = otherPos->y - position->y;
	float aimRadian = atan2(ratioY, ratioX);
	int aimAngle = (int)(aimRadian * (180.0 / PI) + 180);
	//レーザー撃った後の処理
	if (!(moveStart && state == laser && count >= 20))
	{
		//アングルを０～３６０に
		headAngle = abs(headAngle + 360 * (abs(headAngle / 360)+1)) % 360;
		//一度ずつ動かす
		//頭角度と目的角度の差が270度以上の時回す角度を反対に
		if (abs(headAngle - aimAngle) > 270)
		{
			//頭角度と目的角度の差が正なら時計回りに回転
			if (headAngle - aimAngle > 0)
			{
				headAngle++;
			}
			//頭角度と目的角度の差が負なら反時計回りに回転
			else if (headAngle - aimAngle < 0)
			{
				headAngle--;
			}
		}
		else
		{
			//目的角度と頭角度の差が正なら時計回りに回転
			if (aimAngle - headAngle > 0)
			{
				headAngle++;
			}
			//目的角度と頭角度の差が負なら反時計回りに回転
			else if (aimAngle - headAngle < 0)
			{
				headAngle--;
			}
		}
	}
	//弾発射時ノックバック
	if (firing)
	{
		float length = sqrtf((ratioX * ratioX) + (ratioY * ratioY));
		int reverse = -1;
		ratioX /= (length * reverse);
		ratioY /= (length * reverse);
		headPos = Vector2(position->x + ratioX * 50, position->y + ratioY * 50);
	}
	//移動量取得
	int frame = 10;
	headVel.x = (position->x - headPos.x) / frame;
	headVel.y = (position->y - headPos.y) / frame;
	//目的地付近で停止
	int range = 1;
	if (abs(headPos.x - position->x) < range &&
		abs(headPos.y - position->y) < range)
	{
		headVel.Zero();
		headPos = Vector2(position->x, position->y);
	}
	//頭の位置決定
	headPos.x += headVel.x;
	headPos.y += headVel.y;
	Renderer::Instance()->DrawTexture3("player_head", &headPos, new Vector2((float)(imageSizeX / 2), (float)(imageSizeY / 2)), (float)(headAngle - 90), scaleX, scaleY);
}

//死亡時のモーション処理
void Boss::DeathMotion()
{
	int deadCount = 50;
	new DeathParticle(position,sizeX,sizeY);
	//死亡してたらisDeadをtrueに
	if (count >= deadCount)
	{
		isDead = true;
	}
	//一定の大きさまで大きくしたら拡縮しブルブルさせる
	else
	{
		//大きさの変化
		scaleX += addScale;
		float maxScale = 16;
		float minScale = 15.9f;
		//一定の大きさになったら小さくする
		if (scaleX >= maxScale)
		{
			addScale = -0.1f;
			count++;
		}
		//ある程度小さくなったら大きくする
		else if (addScale < 0 && scaleX <= minScale)
		{
			addScale = 0.1f;
		}
	}
	scaleY = scaleX;
	//赤を強く
	r++;
	g--;
	b--;
}

//死亡の真偽
bool Boss::IsDeadFlag()
{
	return isDeadFlag;
}
