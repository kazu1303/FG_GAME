#include "TitleEnemy.h"
#include "GameStart.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"
#include "Explode.h"
#include "Screen.h"

TitleEnemy::TitleEnemy(Vector2* position, int enemyNum)
	:Enemy("dragonfly",position,3,1)
{
	this->enemyNum = enemyNum;
	Initialize();
}

TitleEnemy::~TitleEnemy()
{
}

//����������
void TitleEnemy::Initialize()
{
	//�o��������G�l�~�[�ݒ�
	//Enemy1�̐ݒ�
	if (enemyNum == 1)
	{
		sizeX = 51;
		sizeY = 51;
		scaleX = 3;
		Name = "dragonfly";
		hp = 1;
	}
	//Enemy2�̐ݒ�
	else if (enemyNum == 2)
	{
		sizeX = 32;
		sizeY = 32;
		scaleX = 4;
		Name = "meteorite";
		hp = 2;
	}
	//Enmey3�̐ݒ�
	else if (enemyNum == 3)
	{
		sizeX = 27;
		sizeY = 27;
		scaleX = 3;
		Name = "bird";
		hp = 3;
	}
	angle = 0;
}

//���t���[������
void TitleEnemy::Update()
{
	//�̗͂�0�ȉ��̎����S
	if (hp <= 0)
	{
		isDead = true;
	}
	//���S����
	if (isDead)
	{
		//���񂾂甚��
		for (int i = 0; i < 10; i++)
		{
			new Explode(position);
		}
		//���񂾂�G�l�~�[�ɍ��킹���u���b�N�𐶐�
		Sound::Instance()->PlaySE("explode");
		position->x -= (int)(position->x) % Block::blockSize;
		position->y -= (int)(position->y) % Block::blockSize;
		new CenterBlock(new Vector2(position->x + Block::blockSize / 2, position->y + Block::blockSize / 2));
		//Enemy1�̎��S���u���b�N����
		if (enemyNum == 1)
		{
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
			new TitleEnemy(new Vector2((float)(Block::blockSize * 8 + Block::blockSize / 2), (float)(Block::blockSize * 10 + Block::blockSize / 2)), 2);
		}
		//Enemy2�̎��S���u���b�N����
		else if (enemyNum == 2)
		{
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
			new TitleEnemy(new Vector2((float)(Block::blockSize * 11 + Block::blockSize / 2), (float)(Block::blockSize * 9 + Block::blockSize / 2)), 3);
		}
		//Enemy3�̎��S���u���b�N����
		else if (enemyNum == 3)
		{
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
			new AroundBlock(new Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
			new GameStart(new Vector2((float)(Screen::WinWidth / 2), (float)(Screen::WinHight / 2)));
		}
	}
}

//�`�揈��
void TitleEnemy::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1("attack", new Vector2(position->x + sizeX / 2, position->y - sizeY), 0.0f,1);
	//Enemy1�̕`��
	if (enemyNum == 1)
	{
		Renderer::Instance()->DrawTexture1(Name, position, angle, scaleX);
	}
	//Enemy2�̕`��
	else if (enemyNum == 2)
	{
		Renderer::Instance()->DrawTexture1(Name, position, angle);
	}
	//Enemy3�̕`��
	else if (enemyNum == 3)
	{
		Renderer::Instance()->DrawTexture1(Name, position, angle + 90.0f, scaleX);
	}
}

//�q�b�g����
void TitleEnemy::Hit(GameObject * obj)
{
	//�e�Ƀq�b�g������̗͂����炷
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
