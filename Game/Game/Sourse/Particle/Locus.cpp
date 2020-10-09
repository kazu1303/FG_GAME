#include "Locus.h"
#include"DxLib.h"
#include"Display.h"


Locus::Locus(Vector2* position)
	:Particle(position, 50, 3.0f)
{
	//ˆÚ“®—Ê‚ðƒ‰ƒ“ƒ_ƒ€Œˆ’è
	velocity = new Vector2((float)(GetRand(5) - 3), (float)(GetRand(5) - 3));
}


Locus::~Locus()
{
}

//–ˆƒtƒŒ[ƒ€ˆ—
void Locus::Update()
{
	Particle::Update();
}

//•`‰æˆ—
void Locus::Draw()
{
	Display::Instance()->SetScreen(Particle_Screen);
	//‰~‚Ì•`‰æ
	DrawCircle((int)position->x, (int)position->y, (int)scale, GetColor(255, 255, 255), 1);
}


