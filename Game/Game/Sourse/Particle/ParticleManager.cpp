#include "ParticleManager.h"
#include <memory>
#include <vector>
using namespace std;

vector<shared_ptr<Particle>> particles;//パーティクルを格納
vector<shared_ptr<Particle>> addParticle;//新しいパーティクルを格納

ParticleManager* ParticleManager::instance = nullptr;

ParticleManager::ParticleManager()
{
	instance = this;
	Initialize();
}


ParticleManager::~ParticleManager()
{
}

//インスタンス
ParticleManager * ParticleManager::Instance()
{
	return instance;
}

//初期化処理
void ParticleManager::Initialize()
{
	//vectorの中身を全消去
	particles.clear();
	addParticle.clear();
	particles.shrink_to_fit();
	addParticle.shrink_to_fit();
}

//毎フレーム処理
void ParticleManager::Update()
{
	//新しく生成されたparticleを追加
	copy(addParticle.begin(), addParticle.end(), back_inserter(particles));
	addParticle.clear();
	//アップデート
	for (auto itr : particles)
	{
		itr->Update();
	}
	//死亡処理
	for (auto itr = particles.begin(); itr != particles.end(); )
	{
		if ((*itr)->IsDead())
		{
			itr = particles.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

//描画処理
void ParticleManager::Draw()
{
	//パーティクルの描画
	for (auto itr : particles)
	{
		itr->Draw();
	}
}

//パーティクルを加える
void ParticleManager::Add(Particle * particle)
{
	shared_ptr<Particle> addpart(particle);
	addParticle.push_back(addpart);
}
