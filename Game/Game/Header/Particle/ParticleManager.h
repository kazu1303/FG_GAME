#pragma once
#include "Particle.h"

class ParticleManager
{
private:
	static ParticleManager* instance;//インスタンス
public:
	ParticleManager();
	~ParticleManager();
	//ParticleManagerのインスタンスを返す
	static ParticleManager* Instance();
	//初期化処理
	void Initialize();
	//毎フレーム処理
	void Update();
	//描画処理
	void Draw();
	//生成したパーティクルを加える
	void Add(Particle* particle);
};

