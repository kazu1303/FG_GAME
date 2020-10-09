#include "Enemy3.h"
#include "Renderer.h"
#include "Display.h"
#include "Sound.h"
#include "CenterBlock.h"
#include "AroundBlock.h"
#include "Locus.h"

const float spawnlength = 500;

Enemy3::Enemy3(Vector2* position,float angle)
	:Enemy("bird",position,3,3)
{
	this->angle = angle;

}


Enemy3::~Enemy3()
{
}

//‰Šú‰»ˆ—
void Enemy3::Initialize()
{
	chaseSpeed = 2.0f;
	changedir = false;
}

//–ˆƒtƒŒ[ƒ€ˆ—
void Enemy3::Update()
{
	float addAngle = 2;
	angle+= addAngle;
	if (angle >= 360)
	{
		angle = 0;
	}
	//•ûŒüŒˆ‚ß
	if (!changedir)
	{
		iniVel = Ratio();
		changedir = true;
	}
	//–Ú“I’n‚É’…‚¢‚½‚ç‹t‚Éi‚Þ
	if (abs(iniPos.x - position->x) < 10 && abs(iniPos.y - position->y) < 10)
	{
		chaseSpeed = -2.0f;
	}
	//‰~‚ð•`‚­‚æ‚¤‚ÉˆÚ“®
	Vector2 lengthXY = Vector2(iniPos.x - position->x, iniPos.y - position->y);
	float length = lengthXY.Length();
	velocity->AngleToVector(angle);
	position->x = iniPos.x + velocity->x * (length - chaseSpeed);
	position->y = iniPos.y + velocity->y * (length - chaseSpeed);
	//ƒXƒ|[ƒ“’n“_‚ÌŠO‚Éo‚½‚çŽ€–S
	if (position->x > 900 ||
		position->y > 820 ||
		position->x < -100 ||
		position->y < -180)
	{
		isDead = true;
	}
	new Locus(position);
	//‘Ì—Í‚ª0‚ÌŽžŽ€–Sˆ—
	if (hp <= 0)
	{
		isDead = true;
		Sound::Instance()->PlaySE("explode");
		//Ž€‚ñ‚¾‚çƒuƒƒbƒN¶¬3*3
		position->x -= ((int)position->x) % Block::blockSize;
		position->y -= ((int)position->y) % Block::blockSize;
		new CenterBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x - Block::blockSize / 2), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y - Block::blockSize / 2)));
		new AroundBlock(&Vector2((float)(position->x + Block::blockSize / 2 + Block::blockSize), (float)(position->y + Block::blockSize / 2 + Block::blockSize)));
	}
}

//•`‰æˆ—
void Enemy3::Draw()
{
	Display::Instance()->SetScreen(Enemy_Screen);
	Renderer::Instance()->DrawTexture1(Name,position, -angle + 90.0f, 3.0f);
}

//ƒqƒbƒgˆ—
void Enemy3::Hit(GameObject * obj)
{
	//’e‚Éƒqƒbƒg‚µ‚½‚ç‘Ì—Í‚ðŒ¸‚ç‚·
	if (obj->GetType() == bullet)
	{
		hp--;
	}
}
