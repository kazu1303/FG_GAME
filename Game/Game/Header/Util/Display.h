#pragma once
#include <map>


//スクリーン
enum ScreenID
{
	BossLeg_Screen,
	BossHead_Screen,
	Enemy_Screen,
	PlayerLeg_Screen,
	PlayerHead_Screen,
	Block_Screen,
	PlayerBullet_Screen,
	BossAttack_Screen,
	Firing_Screen,
	Particle_Screen,
	CloudofDust_Screen,
	BossDust_Screen,
	Item_Screen
};

class Display
{
private:
	std::map<ScreenID, int> screens;//作成したスクリーンを保存
	static Display* instance;//インスタンス
	int screenNum = 13;//作成するスクリーンの数
public:
	Display();
	~Display();
	//インスタンスを返す
	static Display* Instance();
	//マスクの生成
	void MakeDrawScreen();
	//作成したスクリーンをmapに保存
	void MakeDrawScreen(ScreenID id, int screen);
	//マスクの描画のクリア
	void ClearScreen();
	//描画するマスクをセット
	void SetScreen(ScreenID id);
	//全マスクの描画
	void DrawScreen();
};



