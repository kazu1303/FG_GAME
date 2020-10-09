#include "Explode.h"
#include"DxLib.h"
#include"Display.h"


Explode::Explode(Vector2* position)
	:Particle(position,50,15)
{
	//ˆÚ“®—Ê‚ðƒ‰ƒ“ƒ_ƒ€‚ÉŒˆ’è
	velocity = new Vector2((float)((GetRand(2) - 1.0f) / 5.0f), (float)((GetRand(2) - 1.0f) / 5.0f));
	drawNum = GetRand(1);
}


Explode::~Explode()
{
}

//–ˆƒtƒŒ[ƒ€ˆ—
void Explode::Update()
{
	Particle::Update();
}

//•`‰æˆ—
void Explode::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_HALF_ADD, 128);
	//—”‚Å•`‰æF‘Ö‚¦
	if (drawNum == 0)
	{
		//‰©F‚Á‚Û‚¢‰~‚Ì•`‰æ
		DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 136, 0), 1);
	}
	if (drawNum == 1)
	{
		//”’‚Á‚Û‚¢‰~‚Ì•`‰æ
		DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(236, 255, 73), 1);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 50);
}


