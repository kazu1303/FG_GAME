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

//インスタンスを返す
Renderer* Renderer::Instance()
{
	return instance;
}

//画像のロード
void Renderer::Load()
{
	for (int i = 0; i < texNum; i++)
	{
		LoadContent(Textures::Date[i][0], Textures::Date[i][1], "Content/Texture/");
	}
}

//画像読み込み
void Renderer::LoadContent(string assetName,string failPath, string Path)
{
	string fName = Path + assetName + failPath;
	LoadContent(assetName, LoadGraph(fName.c_str()));
}

//画像をmapに保存
void Renderer::LoadContent(string assetName, int graph)
{
	textures[assetName] = graph;
}

//画像情報を返す
int Renderer::Texture(string name)
{
	return textures[name];
}

//座標に描画
void Renderer::DrawTexture(string name, Vector2* position)
{
	DrawGraph((int)position->x, (int)position->y, textures[name], 1);
}

//拡縮、回転ができる描画
void Renderer::DrawTexture1(string name, Vector2 * position, float angle, float scale, bool reverse)
{
	double radian = angle * PI / 180.0f;
	DrawRotaGraph((int)position->x, (int)position->y, (double)scale, radian, textures[name], 1, reverse);
}

//基準点を変更する描画
void Renderer::DrawTexture2(string name, Vector2 * position, Vector2* center, float angle,float scale,bool reverse)
{
	double radian = angle * PI / 180;
	DrawRotaGraph2((int)position->x, (int)position->y,(int)center->x,(int)center->y, (double)scale, radian , textures[name], 1,reverse);
}

//XYそれぞれ拡縮できる描画
void Renderer::DrawTexture3(string name, Vector2 * position, Vector2 * center, float angle, float scaleX, float scaleY, bool reverse)
{
	double radian = angle * PI / 180;
	DrawRotaGraph3((int)position->x, (int)position->y, (int)center->x, (int)center->y, (double)scaleX,(double)scaleY, radian, textures[name], 1, reverse);
}
