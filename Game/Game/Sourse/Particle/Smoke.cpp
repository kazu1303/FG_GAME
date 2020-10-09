#include "Smoke.h"
#include "DxLib.h"
#include"Display.h"

Smoke::Smoke(Vector2* position)
	:Particle(position,20,10)
{
	//ˆÚ“®—Ê‚ðƒ‰ƒ“ƒ_ƒ€Œˆ’è
	velocity = new Vector2((float)(GetRand(360) - 180), (float)(GetRand(360) - 180));
	velocity->Normalize();
}

Smoke::~Smoke()
{
}

//–ˆƒtƒŒ[ƒ€ˆ—
void Smoke::Update()
{
	Particle::Update();
}

//•`‰æˆ—
void Smoke::Draw()
{
	Display::Instance()->SetScreen(CloudofDust_Screen);
	//hp‚ªŒ¸‚é‚É‚Â‚ê‚ÄÁ‚¦‚Ä‚¢‚­ˆ—
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, hp * 12);
	//‰~‚Ì•`‰æ
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(124, 73, 28), 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


