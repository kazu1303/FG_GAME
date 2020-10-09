#pragma once
#include "Sounds.h"
#include <map>

class Sound
{
private:
	std::map<std::string, int> ses;
	std::map<std::string, std::string> bgms;
	static Sound* instance;
public:
	Sound();
	~Sound();
	//インスタンスを返す
	static Sound* Instance();
	//読み込む音楽の数だけロード
	void Load();
	//SEのロード
	void LoadSE(std::string assetname, std::string failPath, std::string Path = "");
	//ロードしたSEをmapに保存
	void LoadSE(std::string assetname, int sound);
	//SEを流す
	void PlaySE(std::string name);
	//SEが流れているか調べている
	bool CkeckSEPlay(std::string name);
	//BGMを流す
	void PlayBGM(std::string name, std::string Path = "Content/Sound/");
	//BGMが流れているか調べる
	bool CkeckBGMPlay();
	//BGMを止める
	void StopBGM();
};

//読み込む音楽の数だけロード
inline void Sound::Load()
{
	for (int i = 0; i < 7; i++)
	{
		LoadSE(Sounds::SEDate[i][0], Sounds::SEDate[i][1], "Content/Sound/");
	}
}


