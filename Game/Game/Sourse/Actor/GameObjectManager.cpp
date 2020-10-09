#include "GameObjectManager.h"

using namespace std;

vector<shared_ptr<GameObject>> GameObjectManager::gameObjects;
vector<shared_ptr<GameObject>> GameObjectManager::addgameObjects;
vector<shared_ptr<GameObject>> GameObjectManager::blockObjects;
vector<shared_ptr<GameObject>> GameObjectManager::addblockObjects;
Player* GameObjectManager::sPlayer;
GameStart* GameObjectManager::sStart;
Boss* GameObjectManager::sBoss;

vector<GameObject*>::iterator itr;

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager::GameObjectManager()
{
	instance = this;
	Initialize();
}

//�C���X�^���X
GameObjectManager * GameObjectManager::Instance()
{
	return instance;
}

//����������
void GameObjectManager::Initialize()
{
	//���ׂĂ�vector���N���A���T�C�Y�����킹��
	gameObjects.clear();
	addgameObjects.clear();
	gameObjects.shrink_to_fit();
	addgameObjects.shrink_to_fit();
	blockObjects.clear();
	addblockObjects.clear();
	blockObjects.shrink_to_fit();
	addblockObjects.shrink_to_fit();
	//�Ď��p�ϐ���nullptr��
	sPlayer = nullptr;
	sStart = nullptr;
	sBoss = nullptr;
}

//�u���b�N�ȊO�̃L������z��ɉ�����
void GameObjectManager::Add(GameObject* obj)
{
	//player�͊Ď��p�ϐ��ɓ����
	if (obj->GetType() == player)
	{
		sPlayer = (Player*)obj;
	}
	//start�͊Ď��p�ϐ��ɓ����
	if (obj->GetType() == start)
	{
		sStart = (GameStart*)obj;
	}
	//boss�͊Ď��p�ϐ��ɓ����
	if (obj->GetType() == boss)
	{
		sBoss = (Boss*)obj;
	}
	shared_ptr<GameObject> addobj(obj);
	addgameObjects.push_back(addobj);
}

//�u���b�N��z��ɉ�����
void GameObjectManager::AddBlock(GameObject* obj)
{
	shared_ptr<GameObject> addblock(obj);
	addblockObjects.push_back(addblock);
}

//���t���[������
void GameObjectManager::Update()
{
	//�V�����������ꂽ�I�u�W�F�N�g�̒ǉ�
	blockObjects.insert(blockObjects.begin(), addblockObjects.begin(),addblockObjects.end());
	gameObjects.insert(gameObjects.end(), addgameObjects.begin(), addgameObjects.end());
	addgameObjects.clear();
	addblockObjects.clear();

	//�A�b�v�f�[�g
	for (auto obj1 : gameObjects)
	{
		for (auto obj2 : gameObjects)
		{
			obj1->SetPlayerPos(obj2->GetPos(), obj2->GetType());
		}
	}
	//�L�����N�^�[�̖��t���[������
	for (auto itr : gameObjects)
	{
		itr->Update();
	}
	//�u���b�N�ނ̖��t���[������
	for (auto itr : blockObjects)
	{
		itr->Update();
	}
	HitToObject();
	//���S����
	//�L�����N�^�[�̎��S����
	for (auto itr = gameObjects.begin(); itr != gameObjects.end(); )
	{
		//���S���Ă���vector�������
		if ((*itr)->IsDead())
		{
		    itr  = gameObjects.erase(itr);
		}
		//���S���ĂȂ������玟�̃I�u�W�F�N�g������
		else
		{
			itr++;
		}
	}
	//�u���b�N�ނ̎��S����
	for (auto itr = blockObjects.begin(); itr != blockObjects.end(); )
	{
		//���S���Ă���vector�������
		if ((*itr)->IsDead())
		{
			itr = blockObjects.erase(itr);
		}
		//���S���ĂȂ������玟�̃I�u�W�F�N�g������
		else
		{
			itr++;
		}
	}

	//�T�C�Y�����킹��
	gameObjects.shrink_to_fit();
	blockObjects.shrink_to_fit();
}

//�`�揈��
void GameObjectManager::Draw()
{
	for (auto itr : gameObjects)
	{
		itr->Draw();
	}
}

//�u���b�N�̕`�揈��
void GameObjectManager::BlockDraw()
{
	for (auto itr : blockObjects)
	{
		itr->Draw();
	}
}

//�q�b�g����
void GameObjectManager::HitToObject()
{
	//�u���b�N���̃v���C���[�̖ʐς����߂�
	for (auto obj1 : gameObjects)
	{
		//�v���C���[�̖ʐς��������߂�
		if (obj1->GetType() != player)
		{
			continue;
		}
		//�u���b�N���ׂĂƓ����蔻�菈��
		for (auto obj2 : blockObjects)
		{
			//��Q���͖ʐς��܂܂Ȃ�
			if (obj2->GetType() == obstacle)
			{
				continue;
			}
			//�v���C���[�ƃq�b�g���Ă���u���b�N�����ʐϏ���
			if (obj1->IsCollision(obj2.get()))
			{
				obj1->IsBlock(obj2.get());
			}

		}
	}
	//�q�b�g����
	for (auto obj1 : gameObjects)
	{
		//�����蔻�肪�Ȃ��ꍇ�������Ȃ�
		if (!obj1->EntityObject())
		{
			continue;
		}
		for (auto obj2 : gameObjects)
		{
			//�������̂Ɠ����蔻�肪�Ȃ����̂͏������Ȃ�
			if (obj1->Equal(obj2.get()) ||
				!obj2->EntityObject())
			{
				continue;
			}
			//�q�b�g���Ă�����q�b�g���̏���
			if (obj1->IsCollision(obj2.get()))
			{
				obj1->Hit(obj2.get());
			}
		}
	}
	//�u���b�N���m�̓����蔻��
	for (auto obj1 : blockObjects)
	{
		//�����蔻�肪�Ȃ��A�܂��͐V�����u���b�N�Ə�Q���͓����蔻�菈�����Ȃ�
		if (!obj1->EntityObject() ||
			(obj1->GetType() != newblock &&
				obj1->GetType() != obstacle))
		{
			continue;
		}
		for (auto obj2 : blockObjects)
		{
			//�������̂ƐV�����u���b�N�͏������Ȃ�
			if (obj1->Equal(obj2.get()) ||
				obj2->GetType() == newblock)
			{
				continue;
			}
			//�q�b�g���Ă�����q�b�g���̏���
			if (obj1->BBCollision(obj2.get()))
			{
				obj1->Hit(obj2.get());
				obj2->Hit(obj1.get());
			}
		}
	}
	//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
	for (auto obj1 : gameObjects)
	{
		//�����蔻�肪�Ȃ�,�܂��̓v���C���[�ƃ{���̔����ȊO�̓u���b�N�Ƃ̓����蔻�菈�����Ȃ�
		if (!obj1->EntityObject() ||
			(obj1->GetType() != player &&
				obj1->GetType() != bombexplosion))
		{
			continue;
		}
		for (auto obj2 : blockObjects)
		{
			//�����蔻�肪�Ȃ��ꍇ�������Ȃ�
			if (!obj2->EntityObject())
			{
				continue;
			}
			//�q�b�g���Ă�����q�b�g���̏���
			if (obj1->IsCollision(obj2.get()))
			{
				obj1->Hit(obj2.get());
				obj2->Hit(obj1.get());
			}
		}
	}
	//�ʐς̃��Z�b�g
	for (auto itr : gameObjects)
	{
		itr->ResetIsBlock();
	}
}

int GameObjectManager::PlayerPos()
{
	//�v���C���[���㉺���E�A�ǂ��ɋ߂����Ԃ�
	if (sPlayer != nullptr && sPlayer->GetPos()->y < Screen::WinHight / 2)
	{
		if (sPlayer->GetPos()->x < Screen::WinWidth / 2)
		{
			return 2;
		}
		return 1;
	}
	else
	{
		if (sPlayer == nullptr && sPlayer->GetPos()->x < Screen::WinWidth / 2)
		{
			return 3;
		}
		return 0;
	}
}

//�X�^�[�g���邩
bool GameObjectManager::Start()
{
	//sStart������ł���Q�[�����X�^�[�g����
	if (sStart != nullptr &&
		sStart->IsDead())
	{
		return true;
	}
	return false;
}

//���񂾂�
bool GameObjectManager::GameOver()
{
	//sPlayer������ł���Q�[���I�[�o�[�ɂ���
	if (sPlayer != nullptr && sPlayer->IsDead())
	{
		return true;
	}
	return false;
}

//�N���A�������i�Q�[���v���C�ɕԂ��p�j
bool GameObjectManager::GameClear()
{
	//sBoss������ł���Q�[���N���A�ɂ���
	if (sBoss != nullptr && sBoss->IsDead())
	{
		return true;
	}
	return false;
}

//�N���A�������i���̃N���X���Ŏg���悤�j
bool GameObjectManager::ClearFlag()
{
	//sBoss������ł���N���A�t���O�𗧂Ă�(�{�X�̎��S���o�̂���)
	if (sBoss != nullptr && sBoss->IsDeadFlag())
	{
		return true;
	}
	return false;
}

//�������ꂽ�u���b�N�̐���Ԃ�
int GameObjectManager::BlockNum()
{
	return blockObjects.size();
}

GameObjectManager::~GameObjectManager()
{
}
