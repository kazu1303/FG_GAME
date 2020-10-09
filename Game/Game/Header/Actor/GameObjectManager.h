#pragma once
#include <vector>
#include <memory>

#include "GameObject.h"
#include "Player.h"
#include "GameStart.h"
#include "Boss.h"

//�I�u�W�F�N�g���Ǘ�����N���X
class GameObjectManager
{
private:
	static GameObjectManager* instance;//�C���X�^���X
	//�u���b�N�ȊO�̃I�u�W�F�N�g������悤
	static std::vector<std::shared_ptr<GameObject>> gameObjects;//�L�������i�[
	static std::vector<std::shared_ptr<GameObject>> addgameObjects;//�V�������������L�������i�[
	//�u���b�N�̃I�u�W�F�N�g������悤
	static std::vector<std::shared_ptr<GameObject>> blockObjects;//�n�ʂ�ǂ��i�[
	static std::vector<std::shared_ptr<GameObject>> addblockObjects;//�V�������������u���b�N���i�[
	static Player* sPlayer;//Player�Ď��p
	static GameStart* sStart;//GameStart�Ď��p
	static Boss* sBoss;//Boss�Ď��p
public:
	GameObjectManager();
	//�C���X�^���X
	static GameObjectManager* Instance();
	//����������
	void Initialize();
	//�u���b�N�ȊO�̃L������z��ɉ�����
	void Add(GameObject* obj);
	//�u���b�N��z��ɉ�����
	void AddBlock(GameObject* obj);
	//���t���[������
	void Update();
	//�`�揈��
	void Draw();
	//�u���b�N�̕`�揈��
	void BlockDraw();
	//�q�b�g����
	void HitToObject();
	//�v���C���[���ł��߂�������Ԃ�
	int PlayerPos();
	//�X�^�[�g���邩
	bool Start();
	//���񂾂�
	bool GameOver();
	//�N���A������
	bool GameClear();
	//�N���A������
	bool ClearFlag();
	//�������ꂽ�u���b�N�̐���Ԃ�
	int BlockNum();
	~GameObjectManager();
};