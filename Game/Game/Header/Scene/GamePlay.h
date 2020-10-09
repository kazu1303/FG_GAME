#pragma once
#include "GameScene.h"
#include "Timer.h"

class GamePlay:
	public GameScene
{
private:
	bool boss;
	Timer enemy1Summon;//�g���{�̐����Ԋu
	Timer enemy2Summon;//覐΂̐����Ԋu
	Timer enemy3Summon;//���̐����Ԋu
public:
	GamePlay();
	~GamePlay();
	//����������
	void Initialize()override;
	//���t���[������
	void Update()override;
	//�`�揈��
	void Draw() override;
	//���̃V�[��
	virtual Scene Next() override;
	//���݂̃V�[��
	Scene CurrentScene()override;
};
