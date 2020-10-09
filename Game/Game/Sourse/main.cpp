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
	//�E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

    //�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A

    //���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���

    SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	//SetMainWindowsText(); �^�C�g���̕ύX

	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�Ɂj
	SetGraphMode(WinWidth, WinHight, 32);

	//��ʃT�C�Y��ݒ�i�𑜓x�̔䗦�j
	SetWindowSizeExtendRate(1, 0);

	//��ʂ̔w�i�F��ݒ�
	SetBackgroundColor(35, 120, 197);

    //Dx���C�u������������

    if (DxLib_Init() == -1)
    {
	    //�G���[���o����}�C�i�X�l��Ԃ��ďI��
	    return -1;
    }

	while (1)
	{
		if (ProcessMessage() == -1)break;
		if (CheckHitKey(KEY_INPUT_ESCAPE))break;
	    
	}

    //�����������܂őҋ@

    WaitKey();

    //Dx���C�u�����I������

    DxLib_End();

    return 0;

}