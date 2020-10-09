#pragma once
class Timer
{
private:
	bool isTime;//設定した秒数の経過の真偽
	bool loop;//ループするか
	float time,maxtime;//現在時間、設定時間
public:
	Timer();
	Timer(float maxTime, bool loop);
	~Timer();
	//セットした時間が経過したか
	bool IsTime();
	//タイマーを０に
	void Reset();
	//タイマーを設定した時間に
	void Max();
	//初期化処理
	void Initialize();
	//タイマーの時間の再設定
	void Resetting(float maxTime);
	//毎フレーム処理
	void Update();
};

