#pragma once
#include "Vector2.h"
#include "Textures.h"

#include<map>

class Renderer
{
private:
	std::map<std::string, int> textures;//ロードした画像をの保存用
    static Renderer* instance;//インスタンス
	int texNum = 19;
public:
	Renderer();
	~Renderer();
	//インスタンスを返す
    static Renderer* Instance();
	//画像のロード
	void Load();
	//画像読み込み
	void LoadContent(std::string assetName, std::string failPath, std::string Path = "");
	//画像をmapに保存
	void LoadContent(std::string assetName,int graph);
	//画像情報を返す
	int Texture(std::string name);
	//座標に描画
	void DrawTexture(std::string name,Vector2* position);
	//拡縮、回転ができる描画
	void DrawTexture1(std::string name, Vector2* position, float angle, float scale = 4.0f, bool reverse = false);
	//基準点を変更する描画
	void DrawTexture2(std::string name, Vector2* position, Vector2* center, float angle,float scale = 4.0f,bool reverse = false);
	//XYそれぞれ拡縮できる描画
	void DrawTexture3(std::string name, Vector2* position, Vector2* center, float angle, float scaleX = 4.0f, float scaleY = 4.0f, bool reverse = false);
};





