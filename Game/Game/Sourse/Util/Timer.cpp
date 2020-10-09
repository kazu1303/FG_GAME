#include "Timer.h"

Timer::Timer()
{
}

Timer::Timer(float maxTime,bool loop)
{
	this->maxtime = maxTime;
	this->loop = loop;
	Initialize();
}


Timer::~Timer()
{
}

//セットした時間が経過したか
bool Timer::IsTime()
{
	return isTime;
}

//タイマーを０に
void Timer::Reset()
{
	time = 0.0f;
}

//タイマーを設定した時間に
void Timer::Max()
{
	time = maxtime;
}

//初期化処理
void Timer::Initialize()
{
	isTime = false;
	maxtime *= 60;
	time = 0;
}

//タイマーの時間の再設定
void Timer::Resetting(float maxTime)
{
	this->maxtime = maxTime * 60;
}

//毎フレーム処理
void Timer::Update()
{	
    isTime = false;
	//タイマーが設定した時間を経過した場合の処理
	if (time >= maxtime)
	{
		isTime = true;
		//ループする場合タイマーを０に
		if (loop)
		{
			time = 0.0f;
		}
		else//しない場合タイムを設定した時間に
		{
			time = maxtime;
		}
	}
	//タイマーが設定した時間を経過してない場合の処理
	else
	{
		time++;
	}
}
