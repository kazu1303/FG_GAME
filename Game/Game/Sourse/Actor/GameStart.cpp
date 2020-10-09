#include "GameStart.h"
#include "Display.h"
#include "Renderer.h"
#include "Screen.h"
#include "Sound.h"


GameStart::GameStart(Vector2* position)
	:Entity("start",position, start, true,4)
{
}


GameStart::~GameStart()
{
}

//•`‰æˆ—
void GameStart::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1("attack", new Vector2(position->x, position->y - sizeY /3 * 2) ,0.0f, 3);
	Renderer::Instance()->DrawTexture1(Name, new Vector2((float)Screen::WinWidth / 2, (float)Screen::WinHight/2), 0);
}

//ƒqƒbƒgŽž‚Ìˆ—
void GameStart::Hit(GameObject * obj)
{
	//ƒvƒŒƒCƒ„[‚Ì’e‚Éƒqƒbƒg‚µ‚½ê‡Ž€–S
	if (obj->GetType() == bullet)
	{
		isDead = true;
		Sound::Instance()->PlaySE("start");
	}
}
