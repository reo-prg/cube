#include <DxLib.h>
#include <Scene/SceneMng.h>

SceneMng* SceneMng::sInstance = nullptr;
int SceneMng::joypad;

void SceneMng::Run(void)
{
	SystemInit();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_runScene = _runScene->Update(std::move(_runScene));
		joypad = GetJoypadInputState(DX_INPUT_PAD1);

		ImageMngIns.Draw();
	}
}

bool SceneMng::SystemInit(void)
{
	SetWindowText("cube!");
	SetGraphMode(SceneMngIns.ScreenSize.x, SceneMngIns.ScreenSize.y, 16);			// 1024 * 764�h�b�g�A65536�F���[�h�ɐݒ�
	ChangeWindowMode(true);															// true:window false:�t���X�N���[��

	if (DxLib_Init() == -1)															// Dx���C�u�����̏�����
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`�����o�b�N�o�b�t�@�ɐݒ�

	ImageMngIns.getImage("image/back.png", "back");
	ImageMngIns.getImage("image/stageblock.png", "s_block");


	_runScene = std::make_unique<GameScene>();

	return true;
}

SceneMng::SceneMng() :ScreenSize{ 1024,768 }, ScreenCenter(ScreenSize / 2)
{
}


SceneMng::~SceneMng()
{
}
