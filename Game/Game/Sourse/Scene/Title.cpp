#include "Title.h"
#include "Player.h"
#include "Vector2.h"
#include "StartBlock.h"
#include "TitleEnemy.h"
#include "Sound.h"
#include "Renderer.h"
#include "Obstacle.h"
#include "CenterBlock.h"

Title::Title()
{
	isEnd = false;
	gameObjectManager = new GameObjectManager();
	particleManager = new ParticleManager();
}

Title::~Title()
{
}

//初期化処理
void Title::Initialize()
{
	isEnd = false;
	GameObjectManager::Instance()->Initialize();
	ParticleManager::Instance()->Initialize();
	Sound::Instance()->PlayBGM("fight.mp3");
	new Player(&Vector2((float)(Block::blockSize * 8 + Block::blockSize / 2), (float)(Block::blockSize * 13 + Block::blockSize / 2)));
	new StartBlock(&Vector2((float)(Block::blockSize * 8 + Block::blockSize / 2), (float)(Block::blockSize * 12 + Block::blockSize / 2)));
	new StartBlock(&Vector2((float)(Block::blockSize * 8 + Block::blockSize / 2), (float)(Block::blockSize * 13 + Block::blockSize / 2)));
	new StartBlock(&Vector2((float)(Block::blockSize * 7 + Block::blockSize / 2), (float)(Block::blockSize * 12 + Block::blockSize / 2)));
	new StartBlock(&Vector2((float)(Block::blockSize * 7 + Block::blockSize / 2), (float)(Block::blockSize * 13 + Block::blockSize / 2)));
	new StartBlock(&Vector2((float)(Block::blockSize * 9 + Block::blockSize / 2), (float)(Block::blockSize * 12 + Block::blockSize / 2)));
	new StartBlock(&Vector2((float)(Block::blockSize * 9 + Block::blockSize / 2), (float)(Block::blockSize * 13 + Block::blockSize / 2)));
	new TitleEnemy(&Vector2((float)(Block::blockSize * 5 + Block::blockSize / 2), (float)(Block::blockSize * 9 + Block::blockSize / 2)), 1);
	
}

//毎フレーム処理
void Title::Update()
{
	if (gameObjectManager->Start())
	{
		isEnd = true;
		Sound::Instance()->StopBGM();
	}
	GameObjectManager::Instance()->Update();
	ParticleManager::Instance()->Update();
}

//描画処理
void Title::Draw()
{
	Renderer::Instance()->DrawTexture1("title", &Vector2((float)Screen::WinWidth / 2, 100.0f), 0.0f,6.0f);
	Renderer::Instance()->DrawTexture1("key", &Vector2(150.0f, (float)Screen::WinHight- 100.0f),  0.0f, 3.0f);
	Renderer::Instance()->DrawTexture1("mouse", &Vector2((float)Screen::WinWidth - 150.0f, (float)Screen::WinHight - 100.0f), 0.0f, 3.0f);
	GameObjectManager::Instance()->BlockDraw();
	GameObjectManager::Instance()->Draw();
	ParticleManager::Instance()->Draw();
}

//次のシーン
Scene Title::Next()
{
	return gamePlay;
}

//現在のシーン
Scene Title::CurrentScene()
{
	return title;
}
