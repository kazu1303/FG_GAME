#include "Heart.h"
#include "Display.h"
#include "Renderer.h"
#include "Sound.h"


Heart::Heart(Vector2* position)
	:Entity("heal_item",position,heal,true,2 )
{
}


Heart::~Heart()
{
}

//描画処理
void Heart::Draw()
{
	Display::Instance()->SetScreen(Item_Screen);
	Renderer::Instance()->DrawTexture1(Name,position, 0.0f,2.0f);
}

//毎フレーム処理
void Heart::Update()
{
}

//ヒット処理
void Heart::Hit(GameObject * obj)
{
	//ヒットしたのがプレイヤーの場合死亡
	if (obj->GetType() == player)
	{
		isDead = true;
		Sound::Instance()->PlaySE("start");
	}
}
