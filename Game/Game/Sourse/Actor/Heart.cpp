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

//�`�揈��
void Heart::Draw()
{
	Display::Instance()->SetScreen(Item_Screen);
	Renderer::Instance()->DrawTexture1(Name,position, 0.0f,2.0f);
}

//���t���[������
void Heart::Update()
{
}

//�q�b�g����
void Heart::Hit(GameObject * obj)
{
	//�q�b�g�����̂��v���C���[�̏ꍇ���S
	if (obj->GetType() == player)
	{
		isDead = true;
		Sound::Instance()->PlaySE("start");
	}
}
