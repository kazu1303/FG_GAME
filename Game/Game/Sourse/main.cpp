#include "DxLib.h"

const int WinWidth = 800;
const int WinHight = 600;

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	//ウィンドウモードに設定
	ChangeWindowMode(TRUE);

    //ウィンドウサイズを手動では変更できず、

    //かつウィンドウサイズに合わせて拡大できないようにする

    SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	//SetMainWindowsText(); タイトルの変更

	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に）
	SetGraphMode(WinWidth, WinHight, 32);

	//画面サイズを設定（解像度の比率）
	SetWindowSizeExtendRate(1, 0);

	//画面の背景色を設定
	SetBackgroundColor(35, 120, 197);

    //Dxライブラリを初期化

    if (DxLib_Init() == -1)
    {
	    //エラーが出たらマイナス値を返して終了
	    return -1;
    }

	while (1)
	{
		if (ProcessMessage() == -1)break;
		if (CheckHitKey(KEY_INPUT_ESCAPE))break;
	    
	}

    //何か押されるまで待機

    WaitKey();

    //Dxライブラリ終了処理

    DxLib_End();

    return 0;

}