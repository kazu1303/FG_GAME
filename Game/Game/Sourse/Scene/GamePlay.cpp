#include "GamePlay.h"
#include"DxLib.h"

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{
}

//����������
void GamePlay::Initialize()
{
	isEnd = false;
}

//���t���[������
void GamePlay::Update()
{
	//�Q�[���I���̏���
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		isEnd = true;
		//Sound::Instance()->StopBGM();
	}
}

//�`�揈��
void GamePlay::Draw()
{
}

//���̃V�[��
Scene GamePlay::Next()
{
	return gameOver;
}

//���݂̃V�[��
Scene GamePlay::CurrentScene()
{
	return gamePlay;
}
