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

//������
void Boss::Initialize()
{
	once = false;
	moveStart = true;
	moveEnd = false;
	firing = false;
	isDeadFlag = false;
	state = in;
}

//���t���[������
void Boss::Update()
{
	firing = false;
	//�s������
	if (!moveStart && !isDeadFlag && !isDead)
	{
		state = (BossState)(GetRand(3));
	}
	//�s������
	if (!moveEnd && !isDeadFlag)
	{
		//�t�F�[�h�A�E�g����
		if (state == out)
		{
			moveStart = true;
			FeadOut();
		}
		//�t�F�[�h�C������
		if (state == in)
		{
			FeadIn();
		}
		//�~�T�C���U������
		if (state == missile)
		{
			moveStart = true;
			Missile();
		}
		//�{���U������
		if (state == bomb)
		{
			moveStart = true;
			Bomb();
		}
		//���[�U�[�U������
		if (state == laser)
		{
			moveStart = true;
			Laser();
		}
	}
	//���S���[�V��������
	if (isDeadFlag)
	{
		DeathMotion();
	}
	//�d���̏���
	if (moveEnd)
	{
		state = idle;
		velocity->Zero();
		headVel.Zero();
		rigidTimer.Update();
		r = 100;
		g = 100;
		b = 100;
		//�d�����ĂȂ���Ԃɖ߂�
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
	//���̍��W����
	headPos.x += headVel.x;
	headPos.y += headVel.y;
	//���S���u
	if (hp <= 0)
	{
		state = idle;
		isDeadFlag = true;
	}
	GameObject::Update();
}

//�`�揈��
void Boss::Draw()
{
	//�̂̕`��
	Display::Instance()->SetScreen(BossLeg_Screen);
	SetDrawBright(r, g, b);
	Renderer::Instance()->DrawTexture3(Name,position, &Vector2((float)imageSizeX / 2, (float)imageSizeY / 2), angle, scaleX, scaleY);
	//���̕`��
	Display::Instance()->SetScreen(BossHead_Screen);
	HeadDraw();
	SetDrawBright(255, 255, 255);
}

//�q�b�g����
void Boss::Hit(GameObject * obj)
{
	//�e�Ƀq�b�g�����Ƃ��̗͌��炷
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}

//���[�U�[���ˏ���
void Boss::Laser()
{
	int bulletNum = 20;
	int lEndCount = 100;
	//�e�𔭎˂�����d��
	if (count >= lEndCount)
	{
		moveEnd = true;
		count = 0;
		rigidTimer.Resetting(4.0f);
	}
	//�J�E���g���ݒ肵���ʂ̐��ɂȂ�܂Œe�𐶐�
	else if(count <= bulletNum)
	{
		Sound::Instance()->PlaySE("boss_laser");
		new BossLaser(position,bulletNum - count);
	}
	count++;
}

//�~�T�C�����ˏ���
void Boss::Missile()
{
	int missileCount = 10;
	//���count���o�߂����甭�ˏ���
	if (count >= missileCount)
	{
		//�傫����15�ɂȂ�܂ŏ���������
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
	//���ˉ��o
	else
	{
		//�e�𔭎˂���܂Ń��[�V��������
		scaleX += addScale;
		//���̑傫���ɂȂ�����addScale�𔽓]
		if (scaleX >= 18 ||
			(addScale < 0 && scaleX <= 17.8f))
		{
			addScale = -addScale;
			count++;
		}
	}
	//���݂̃{�X�̂���ꏊ�����߂�
	float radian = atan2(position->y - Screen::WinHight / 2, position->x - Screen::WinWidth / 2);
	//�傫���̕ω�
	sizeX = imageSizeX * (scaleX * abs(sin(radian)) + scaleY * abs(cos(radian)));
	sizeY = imageSizeY * (scaleX * abs(cos(radian)) + scaleY * abs(sin(radian)));
}

//���e���ˏ���
void Boss::Bomb()
{
	int bombCount = 20;
	//count��bombCount���傫���ꍇ���ˏ���
	if (count >= bombCount)
	{
		int maxScale = 15;
		float addScale = -0.5f;
		//�ő��菬�����ꍇ�傫������
		if (scaleX > maxScale)
		{
			scaleX += addScale;
		}
		//�ő���傫���Ȃ����ꍇ���ˏ���
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
	//count��bombCount��菬�����ꍇ�傫���̕ύX
	else
	{
		scaleX += addScale;
		//�傫����17�̎�����������
		if (scaleX >= 17)
		{
			addScale = -0.1f;
			count++;
		}
		//addScale��-�ő傫����16.f�ȉ��̎��傫������
		else if (addScale < 0 && scaleX <= 16.9f)
		{
			addScale = 0.1f;
		}

	}
	scaleY = scaleX;
	sizeX = imageSizeX * scaleX;
	sizeY = imageSizeY * scaleY;
}

//�ړ��i�t�F�[�h�A�E�g�����j
void Boss::FeadOut()
{
	int speed = 2;
	//�t�F�[�h�A�E�g��������̎擾
	float radian = atan2(position->y - Screen::WinHight / 2, position->x - Screen::WinWidth / 2);
	//�ړ����ݒ�
	velocity->x = cos(radian) * speed;
	velocity->y = sin(radian) * speed;
	headVel.x = cos(radian) * speed;
	headVel.y = sin(radian) * speed;
	//��ʊO�ɏo����t�F�[�h�C��������
	if (position->x <= 0 - sizeX / 2 ||
		position->x >= Screen::WinWidth + sizeX / 2 ||
		position->y <= 0 - sizeY / 2 ||
		position->y >= Screen::WinHight + sizeY / 2)
	{
		state = in;
	}
}

//�ړ��i�t�F�[�h�C�������j
void Boss::FeadIn()
{	
	//��x��������
	if (!once)
	{
		//�o������ʒu�̎擾
		int pos;
		do {
			pos = GetRand(3);
		} while (pos == posNum);
		posNum = pos;
		//�ʒu���ړ�
		float radian = atan2(popPos[posNum].y - Screen::WinHight / 2, popPos[posNum].x - Screen::WinWidth / 2);
		position->ReSetting(popPos[posNum].x - (sizeX * -cos(radian)), popPos[posNum].y - (sizeY * -sin(radian)));
		headPos = Vector2(position->x, position->y);
		//�̂̌�������
		angle = radian * 180 / PI + 270;
		headAngle = (int)angle + 90;
		once = true;
	}
	//�ړI�n�܂ł̈ړ��ʐݒ�
	velocity->x = (popPos[posNum].x - position->x) / 30.0f;
	velocity->y = (popPos[posNum].y - position->y) / 30.0f;
	headVel.x = (popPos[posNum].x - position->x) / 30.0f;
	headVel.y = (popPos[posNum].y - position->y) / 30.0f;
	//�ړI�n�t�߂Œ�~
	if (abs(popPos[posNum].x - position->x) <= 1 &&
		abs(popPos[posNum].y - position->y) <= 1)
	{
	    once = false;
		moveEnd = true;
		rigidTimer.Resetting(1.0f);
	}
}

//�C��̕`�揈��
void Boss::HeadDraw()
{
	//��������
	float ratioX = otherPos->x - position->x;
	float ratioY = otherPos->y - position->y;
	float aimRadian = atan2(ratioY, ratioX);
	int aimAngle = (int)(aimRadian * (180.0 / PI) + 180);
	//���[�U�[��������̏���
	if (!(moveStart && state == laser && count >= 20))
	{
		//�A���O�����O�`�R�U�O��
		headAngle = abs(headAngle + 360 * (abs(headAngle / 360)+1)) % 360;
		//��x��������
		//���p�x�ƖړI�p�x�̍���270�x�ȏ�̎��񂷊p�x�𔽑΂�
		if (abs(headAngle - aimAngle) > 270)
		{
			//���p�x�ƖړI�p�x�̍������Ȃ玞�v���ɉ�]
			if (headAngle - aimAngle > 0)
			{
				headAngle++;
			}
			//���p�x�ƖړI�p�x�̍������Ȃ甽���v���ɉ�]
			else if (headAngle - aimAngle < 0)
			{
				headAngle--;
			}
		}
		else
		{
			//�ړI�p�x�Ɠ��p�x�̍������Ȃ玞�v���ɉ�]
			if (aimAngle - headAngle > 0)
			{
				headAngle++;
			}
			//�ړI�p�x�Ɠ��p�x�̍������Ȃ甽���v���ɉ�]
			else if (aimAngle - headAngle < 0)
			{
				headAngle--;
			}
		}
	}
	//�e���ˎ��m�b�N�o�b�N
	if (firing)
	{
		float length = sqrtf((ratioX * ratioX) + (ratioY * ratioY));
		int reverse = -1;
		ratioX /= (length * reverse);
		ratioY /= (length * reverse);
		headPos = Vector2(position->x + ratioX * 50, position->y + ratioY * 50);
	}
	//�ړ��ʎ擾
	int frame = 10;
	headVel.x = (position->x - headPos.x) / frame;
	headVel.y = (position->y - headPos.y) / frame;
	//�ړI�n�t�߂Œ�~
	int range = 1;
	if (abs(headPos.x - position->x) < range &&
		abs(headPos.y - position->y) < range)
	{
		headVel.Zero();
		headPos = Vector2(position->x, position->y);
	}
	//���̈ʒu����
	headPos.x += headVel.x;
	headPos.y += headVel.y;
	Renderer::Instance()->DrawTexture3("player_head", &headPos, new Vector2((float)(imageSizeX / 2), (float)(imageSizeY / 2)), (float)(headAngle - 90), scaleX, scaleY);
}

//���S���̃��[�V��������
void Boss::DeathMotion()
{
	int deadCount = 50;
	new DeathParticle(position,sizeX,sizeY);
	//���S���Ă���isDead��true��
	if (count >= deadCount)
	{
		isDead = true;
	}
	//���̑傫���܂ő傫��������g�k���u���u��������
	else
	{
		//�傫���̕ω�
		scaleX += addScale;
		float maxScale = 16;
		float minScale = 15.9f;
		//���̑傫���ɂȂ����珬��������
		if (scaleX >= maxScale)
		{
			addScale = -0.1f;
			count++;
		}
		//������x�������Ȃ�����傫������
		else if (addScale < 0 && scaleX <= minScale)
		{
			addScale = 0.1f;
		}
	}
	scaleY = scaleX;
	//�Ԃ�����
	r++;
	g--;
	b--;
}

//���S�̐^�U
bool Boss::IsDeadFlag()
{
	return isDeadFlag;
}
