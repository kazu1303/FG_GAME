#include "PlayerBullet.h"
#include "Explode.h"
#include "Screen.h"
#include "Display.h"
#include "Renderer.h"

PlayerBullet::PlayerBullet(Vector2* position,float mousePosX,float mousePosY)
	:Entity("bullet",position, bullet)
{
	endPos = Vector2(mousePosX, mousePosY);
	velocity->x = endPos.x - position->x;
	velocity->y = endPos.y - position->y;
	velocity->Normalize();
	angle = atan2(velocity->y, velocity->x);
	angle = angle * (180.0f / PI) + 90;
	float speed = 15;
	velocity->x *= speed;
	velocity->y *= speed;
}


PlayerBullet::~PlayerBullet()
{
}

//初期化処理
void PlayerBullet::Initialize()
{
}

//毎フレーム処理
void PlayerBullet::Update()
{
	//画面外に出たら死亡
	if (position->x > Screen::WinWidth ||
		position->y > Screen::WinHight ||
		position->x < Screen::WinWidth - Screen::WinWidth ||
		position->y < Screen::WinHight - Screen::WinHight)
	{
		isDead = true;
	}
	Entity::Update();
}

//描画処理
void PlayerBullet::Draw()
{
	Display::Instance()->SetScreen(PlayerBullet_Screen);
	Renderer::Instance()->DrawTexture1(Name,position, angle, 1.0f);
}

//ヒット処理
void PlayerBullet::Hit(GameObject * obj)
{
	//ヒットしたのがenemy,bossの場合爆発して死亡
	if (obj->GetType() == enemy ||
		obj->GetType() == boss)
	{
		isDead = true;
		for (int i = 0; i < 10; i++)
		{
			//ヒット時爆発
			new Explode(position);
		}
	}
}
