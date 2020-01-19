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

		ImageMngIns.Draw();
	}
}

bool SceneMng::SystemInit(void)
{
	SetWindowText("cube!");
	SetGraphMode(SceneMngIns.ScreenSize.x, SceneMngIns.ScreenSize.y, 16);			// 1024 * 764ドット、65536色モードに設定
	ChangeWindowMode(true);															// true:window false:フルスクリーン

	if (DxLib_Init() == -1)															// Dxライブラリの初期化
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先をバックバッファに設定

	ImageMngIns.getImage("image/TitleLogo.png", "logo");
	ImageMngIns.getImage("image/TitleMes.png", "TitleMes");
	ImageMngIns.getImage("image/cursor.png", "cursor");
	ImageMngIns.getImage("image/stage.png", "stage", 128, 96, 4, 2);
	ImageMngIns.getImage("image/stageflame.png", "flame");
	ImageMngIns.getImage("image/back.png", "back");
	ImageMngIns.getImage("image/stage_chip.png", "s_cube", 32, 32, 8, 8);
	ImageMngIns.getImage("image/cube.png", "cube", 32, 32, 3, 1);
	ImageMngIns.getImage("image/char.png", "player", 64, 32, 2, 8);

	_runScene = std::make_unique<TitleScene>();

	return true;
}

SceneMng::SceneMng() :ScreenSize{ 1024,768 }, ScreenCenter(ScreenSize / 2)
{
}


SceneMng::~SceneMng()
{
}
