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

//����������
void Player::Initialize()
{
	//�^�C�}�[�ݒ�
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

//���t���[������
void Player::Update()
{
	firing = false;
	float speed = 2;
	velocity->Zero();
	pointer->Update();
	//���S����
	if (isDeadFlag)
	{
		deathTimer.Update();
		//deathTimer��false�̎����S���o
		if (!deathTimer.IsTime())
		{
			DeathMotion();
		}
		//deathTimer��true�̎����S
		else
		{
			isDead = true;
		}
		return;
	}

	//���G����
	Invincible();

	//angle��0����360���Ɏ��߂�
	if (angle >= 360) angle = 0;
	else if (angle < 0) angle = 345;

	//��������
	if (drop)
	{
		repel = false;
		Drop();
		return;
	}
	drop = true;
	hitCount = 0;

	//�͂�����鏈��
	if (repel)
	{
		Repel();
		return;
	}

	//�ړ�����
	Move();
	Firing();
		//���������̃p�[�e�B�N��
	if (velocity->x != 0 ||
		velocity->y != 0)
	{
		particleTimer.Update();
		//true�̎����𐶐�
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
	
	//�ʒu�ݒ�
	velocity->x *= speed;
	velocity->y *= speed;
	GameObject::Update();

	//�̗͂�0�ȉ��̎����S����
	if (hp <= 0)
	{
		alpha = 255;
		isDeadFlag = true;
	}
}

//�ړ�
void Player::Move()
{
	//�ړ�����
	float angleSpeed = 15.0f;
	//������ւ̈ړ�
	if (CheckHitKey(KEY_INPUT_W))
	{
		//������Ă���ړ�
		if (angle == 0)
		{
			velocity->y = -1;
		}
		//�ړ������ւ̉�]
		else if (angle >= 180)
		{
			angle += angleSpeed;
		}
		else if (angle < 180)
		{
			angle -= angleSpeed;
		}
	}
	//�������ւ̈ړ�
	else if (CheckHitKey(KEY_INPUT_S))
	{
		//�������Ă�����ړ�
		if (angle == 180)
		{
			velocity->y = 1;
		}
		//�ړ������ւ̉�]
		else if (angle >= 0 && angle < 180)
		{
			angle += angleSpeed;
		}
		else if (angle < 360 && angle > 180)
		{
			angle -= angleSpeed;
		}
	}
	//�E�����ւ̈ړ�
	else if (CheckHitKey(KEY_INPUT_D))
	{
		//�E�����Ă�����ړ�
		if (angle == 90)
		{
			velocity->x = 1;
		}
		//�ړ������ւ̉�]
		else if (angle >= 270 && angle < 360 || angle < 90 && angle >= 0)
		{
			angle += angleSpeed;
		}
		else if (angle < 270 && angle >90)
		{
			angle -= angleSpeed;
		}
	}
	//�������ւ̈ړ�
	else if (CheckHitKey(KEY_INPUT_A))
	{
		//�������Ă�����ړ�
		if (angle == 270)
		{
			velocity->x = -1;
		}
		//�ړ������ւ̉�]
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

//�`�揈��
void Player::Draw()
{
	//�v���C���[�̕`��
	SetDrawBlendMode(DX_BLENDMODE_HALF_ADD, alpha);
	Display::Instance()->SetScreen(PlayerLeg_Screen);
	Renderer::Instance()->DrawTexture1(Name, position, angle, scaleX);
	Display::Instance()->SetScreen(PlayerHead_Screen);
	//���̕`��
	HeadDraw();
	//�̗̓Q�[�W�̕`��
	DrawDamageGauge();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 50);
	Display::Instance()->SetScreen(Particle_Screen);
	pointer->Draw();
}

//�q�b�g����
void Player::Hit(GameObject * obj)
{
	//�G��{�X�̍U���̃q�b�g����
	if (obj->GetType() == enemy ||
		obj->GetType() == bossbom ||
		obj->GetType() == bosslaser ||
		obj->GetType() == bossmissile)
	{
		//���G�łȂ��Ƃ��_���[�W����
		if (!invincible)
		{
			float damage = 5;
			hp -= damage;
			invincible = true;
		}
		//�~�T�C���Ƀq�b�g�����Ƃ��͂������
		if (obj->GetType() == bossmissile)
		{
			RepelDirection(obj->GetPos());
			repel = true;
		}
	}

	//�u���b�N�̊O�ɏo�Ȃ��悤�ɕ␳
	if ((obj->GetType() == block ||
		obj->GetType() == newblock ||
		obj->GetType() == respawn) &&
		hitCount == 0)
	{
		drop = false;
		//�u���b�N�̊O�ɏ����ł��o�Ă���ʒu��߂�
		if (allarea <= sizeX * sizeY - 1)
		{
			position->x -= velocity->x;
			position->y -= velocity->y;
			hitCount++;
		}
	}

	//�񕜏���
	if (obj->GetType() == heal)
	{
		float heal = 10;
		hp += heal;
		//maxhp���񕜂��Ȃ�
		if (hp >= maxHp)
		{
			hp = maxHp;
		}
	}

	//��Q���ɐG�ꂽ�Ƃ��߂�
	if (obj->GetType() == obstacle)
	{
		position->x -= velocity->x;
		position->y -= velocity->y;
	}
}

//HP�Q�[�W�̕`��
void Player::DrawDamageGauge()
{
	//�ő�̗̑̓Q�[�W�̕`��
	float gaugesizex = maxHp;
	int gaugesizey = 5;
	DrawBox((int)(position->x - gaugesizex), (int)(position->y - gaugesizey + sizeY), (int)(position->x + gaugesizex), (int)(position->y + sizeY), GetColor(0, 0, 0), 1);
	//���݂̗̑̓Q�[�W�̕`��
	float rate = hp / maxHp;
	float currentGaugesizex = gaugesizex * rate;
	DrawBox((int)(position->x - gaugesizex), (int)(position->y - gaugesizey + sizeY), (int)(position->x - gaugesizex + currentGaugesizex * 2), (int)(position->y + sizeY), GetColor(255, 200,255), 1);
}

//�C��̕`��
void Player::HeadDraw()
{
	//�}�E�X�Ǝ��@�̍��W����������擾
	float ratioX = pointer->GetPosX() - position->x;
	float ratioY = pointer->GetPosY() - position->y;
	//���̌����̎擾
	float headAngle = atan2(ratioY, ratioX);
	headAngle = (float)(headAngle * (180.0 / PI) + 90);
	float length = sqrtf((ratioX * ratioX) + (ratioY * ratioY));
	int reverse = -1;
	ratioX /= (length * reverse);
	ratioY /= (length * reverse);
	//�e���ˎ������������ɉ�����
	if (firing)
	{
		Renderer::Instance()->DrawTexture1("player_head", new Vector2(position->x + ratioX * 4.0f, position->y + ratioY * 4.0f), headAngle, scaleX);
	}
	//�ʏ펞position�̈ʒu�ɓ���`��
	else
	{
		Renderer::Instance()->DrawTexture1("player_head", position ,headAngle, scaleX);
	}
}

void Player::Firing()
{
	//�e�̔���
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		bulletTimer.Update();
		//bullettimer��true�̎��e�̔��˂Ɖ��o
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
	//�}�E�X��������ĂȂ��Ƃ������ɔ��˂ł���悤��
	else
	{
		bulletTimer.Max();
	}
}

//���G����
void Player::Invincible()
{
	//���G���Ԃ̏���
	if (invincible)
	{
		invincibleTimer.Update();
		//�_�ŏ���
		int addAlpha = 50;
		//addAlpha�̐��l��alpha�ɂ���ĕύX
		if (alpha <= 0)
		{
			addAlpha = 50;
		}
		else if(alpha >= 255)
		{
			addAlpha = -50;
		}
		//invincibleTimer��true�̎����G���ԏI��
		if (invincibleTimer.IsTime())
		{
			invincible = false;
			invincibleTimer.Reset();
		}
		alpha += addAlpha;
	}
	else//���G�łȂ��Ƃ���alpha��255��
	{
		alpha = 255;
	}
}

//���S�̐^�U(���S���o�p)
bool Player::IsDeadFlag()
{
	return isDeadFlag;
}

//���S���̏���
void Player::DeathMotion()
{
	//�����_���Ȏ��Ƀp�[�e�B�N������
	if (GetRand(5) == 0)
	{
		new DeathParticle(position, sizeX, sizeY);
	}
}

//�~�T�C���Ƀq�b�g���̐�����ԕ�������
void Player::RepelDirection(Vector2 * otherPos)
{
	float radian = atan2(position->y - otherPos->y, position->x - otherPos->x);
	int angle = (int)(radian * 180 / PI + 180);
	//�p�x��90�x�̔{���ɕύX
	angle = (angle + 45) / 90 * 90;
	radian = ((float)angle * PI) / 180.0f;
	aimPos = Vector2(position->x + (Block::blockSize * -cos(radian)), position->y + (Block::blockSize * -sin(radian)));
}

//������я���
void Player::Repel()
{
	//�ړ��ʂ̎擾
	velocity->x = (aimPos.x - position->x) / 20.0f;
	velocity->y = (aimPos.y - position->y) / 20.0f;
	GameObject::Update();
	//�ړI�n�t�߂Œ�~
	if (abs(position->x - aimPos.x) < 1 &&
		abs(position->y - aimPos.y) < 1)
	{
		repel = false;
		velocity->Zero();
	}
}

//�C�ɗ������Ƃ��̏���
void Player::Drop()
{
	//���񂾂񏬂���
	float smallScale = 0.05f;
	alpha = 255;
	scaleX -= smallScale;
	scaleY = scaleX;
	//�������Ȃ����烊�X�|�[���n�_�ŕ���
	if (scaleX <= 0 && scaleY <= 0)
	{
		int damege = 5;
		//�X�|�[���n�_�ɐݒ�
		position->ReSetting(360.0f, 360.0f);
		drop = false;
		hp -= damege;
		invincibleTimer.Reset();
		scaleX = 1.5f;
		scaleY = 1.5f;
		invincible = true;
	}
}

