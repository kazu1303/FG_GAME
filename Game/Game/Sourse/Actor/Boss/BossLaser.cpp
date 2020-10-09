#include "BossLaser.h"
#include "Display.h"
#include "Renderer.h"
#include "DxLib.h"


BossLaser::BossLaser(Vector2* position,int count)
	:Entity("laser",position, bosslaser, true,1)
{
	firing = false;
	this->count = count;
	firingTimer = Timer(1.0f, false);
	iniPos = Vector2(position->x, position->y);
}


BossLaser::~BossLaser()
{
}

//����������
void BossLaser::Initialize()
{
}

//���t���[������
void BossLaser::Update()
{
	int speed = 15;
	//���߂鏈��
	if (count >= 0)
	{
		//�傫��
		float addScale = 0.5f;
		scaleX += addScale;
		//��ɑ�C�̐�[��
		velocity->x = otherPos->x - position->x;
		velocity->y = otherPos->y - position->y;
		velocity->Normalize();
		//�ړ������̃A���O���擾
		angle = atan2(velocity->y, velocity->x);
		angle = angle * (180.0f / PI) + 90;
		int fixScale = 100;
		position->x = iniPos.x + velocity->x * fixScale;
		position->y = iniPos.y + velocity->y * fixScale;
		velocity->x = velocity->x * speed;
		velocity->y = velocity->y * speed;
	}
	firingTimer.Update();
	//���Ԍo�ߌ㔭��
	if (firingTimer.IsTime())
	{
		scaleX = 5;
		Entity::Update();
	}
	//��ʊO�ŏ���
	if (position->x > 900 ||
		position->y > 820 ||
		position->x < -100 ||
		position->y < -180)
	{
		isDead = true;
	}
	count--;
}

//�`�揈��
void BossLaser::Draw()
{
	Display::Instance()->SetScreen(BossAttack_Screen);
	//���˂��Ă���Ԃ�alhpa200��
	if (firingTimer.IsTime())
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
	}
	//���߂Ă���Ԃ�alpha120��
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
	}

	Renderer::Instance()->DrawTexture1(Name, position, angle, scaleX);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 128);
}
