#include "Enemy.h"


Enemy::Enemy(std::string name,Vector2* position,float scale,int hp)
	:Entity(name,position, enemy, true,scale,hp)
{
}


Enemy::~Enemy()
{
}

//��Ƀv���C���[�̍��W���Z�b�g
void Enemy::SetPlayerPos(Vector2 * position, CharaType type)
{
	//�v���C���[�̂ݖړI�n�ɐݒ�
	if (type == player )
	{
		iniPos = Vector2(position->x,position->y);
	}
}

//�ړI�܂ł̃x�N�g���̒P�ʃx�N�g��
Vector2 Enemy::Ratio()
{
	Vector2 ratio;
	ratio.x = iniPos.x - position->x;
	ratio.y = iniPos.y - position->y;
	ratio.Normalize();
	return ratio;
}

//���t���[������
void Enemy::Update()
{
	//�X�|�[���n�_���O�ɏo���玀�S
	if (position->x > 900 ||
		position->y > 820 ||
		position->x < -100 ||
		position->y < -180)
	{
		isDead = true;
	}
	GameObject::Update();
}




