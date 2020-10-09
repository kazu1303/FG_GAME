#include "Sound.h"
#include "DxLib.h"

using namespace std;
Sound* Sound::instance = nullptr;

Sound::Sound()
{
	instance = this;
	ses = map<string, int>();
	bgms = map<string, string>();
}


Sound::~Sound()
{
}

//インスタンスを返す
Sound * Sound::Instance()
{
	return instance;
}

//SEのロード
void Sound::LoadSE(string assetName, string failPath,string Path)
{
	string fName = Path + assetName + failPath;
	LoadSE(assetName, LoadSoundMem(fName.c_str()));
}

//ロードしたSEをmapに保存
void Sound::LoadSE(string assetname, int sound)
{
	ses[assetname] = sound;
}

//SEを流す
void Sound::PlaySE(string name)
{
	PlaySoundMem(ses[name], DX_PLAYTYPE_BACK);
}

//SEが流れているか調べている
bool Sound::CkeckSEPlay(string name)
{
	return CheckSoundMem(ses[name]);
}

//BGMを流す
void Sound::PlayBGM(string name,string Path)
{
	string fname = Path + name;
	PlayMusic(fname.c_str(), DX_PLAYTYPE_LOOP);
}

//BGMが流れているか調べる
bool Sound::CkeckBGMPlay()
{
	return CheckMusic();
}

//BGMを止める
void Sound::StopBGM()
{
	StopMusic();
}
