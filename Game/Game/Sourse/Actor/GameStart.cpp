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

//�`�揈��
void GameStart::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1("attack", new Vector2(position->x, position->y - sizeY /3 * 2) ,0.0f, 3);
	Renderer::Instance()->DrawTexture1(Name, new Vector2((float)Screen::WinWidth / 2, (float)Screen::WinHight/2), 0);
}

//�q�b�g���̏���
void GameStart::Hit(GameObject * obj)
{
	//�v���C���[�̒e�Ƀq�b�g�����ꍇ���S
	if (obj->GetType() == bullet)
	{
		isDead = true;
		Sound::Instance()->PlaySE("start");
	}
}
