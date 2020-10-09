#include "RedSmoke.h"
#include"DxLib.h"
#include"Display.h"


RedSmoke::RedSmoke(Vector2* position, int maxhp, float scale = 1)
	:Particle(position, maxhp, scale)
{
	//ˆÚ“®—Ê‚ðƒ‰ƒ“ƒ_ƒ€Œˆ’è
	velocity = new Vector2((float)(GetRand(2) - 1), (float)(GetRand(2) - 1));
}


RedSmoke::~RedSmoke()
{
}

//–ˆƒtƒŒ[ƒ€ˆ—
void RedSmoke::Update()
{
	Particle::Update();
}

//•`‰æˆ—
void RedSmoke::Draw()
{
	Display::Instance()->SetScreen(Particle_Screen);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 128);

	//‰~‚Ì•`‰æ
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 0, 0), 1);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 50);
}


