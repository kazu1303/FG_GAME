#include "Renderer.h"
#include "DxLib.h"
using namespace std;

Renderer* Renderer::instance = nullptr;

Renderer::Renderer()
{
	instance = this;
	textures = map<string, int>();
}

Renderer::~Renderer()
{
}

//ƒCƒ“ƒXƒ^ƒ“ƒX‚ğ•Ô‚·
Renderer* Renderer::Instance()
{
	return instance;
}

//‰æ‘œ‚Ìƒ[ƒh
void Renderer::Load()
{
	for (int i = 0; i < texNum; i++)
	{
		LoadContent(Textures::Date[i][0], Textures::Date[i][1], "Content/Texture/");
	}
}

//‰æ‘œ“Ç‚İ‚İ
void Renderer::LoadContent(string assetName,string failPath, string Path)
{
	string fName = Path + assetName + failPath;
	LoadContent(assetName, LoadGraph(fName.c_str()));
}

//‰æ‘œ‚ğmap‚É•Û‘¶
void Renderer::LoadContent(string assetName, int graph)
{
	textures[assetName] = graph;
}

//‰æ‘œî•ñ‚ğ•Ô‚·
int Renderer::Texture(string name)
{
	return textures[name];
}

//À•W‚É•`‰æ
void Renderer::DrawTexture(string name, Vector2* position)
{
	DrawGraph((int)position->x, (int)position->y, textures[name], 1);
}

//ŠgkA‰ñ“]‚ª‚Å‚«‚é•`‰æ
void Renderer::DrawTexture1(string name, Vector2 * position, float angle, float scale, bool reverse)
{
	double radian = angle * PI / 180.0f;
	DrawRotaGraph((int)position->x, (int)position->y, (double)scale, radian, textures[name], 1, reverse);
}

//Šî€“_‚ğ•ÏX‚·‚é•`‰æ
void Renderer::DrawTexture2(string name, Vector2 * position, Vector2* center, float angle,float scale,bool reverse)
{
	double radian = angle * PI / 180;
	DrawRotaGraph2((int)position->x, (int)position->y,(int)center->x,(int)center->y, (double)scale, radian , textures[name], 1,reverse);
}

//XY‚»‚ê‚¼‚êŠgk‚Å‚«‚é•`‰æ
void Renderer::DrawTexture3(string name, Vector2 * position, Vector2 * center, float angle, float scaleX, float scaleY, bool reverse)
{
	double radian = angle * PI / 180;
	DrawRotaGraph3((int)position->x, (int)position->y, (int)center->x, (int)center->y, (double)scaleX,(double)scaleY, radian, textures[name], 1, reverse);
}
