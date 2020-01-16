#include <Scene/TitleScene.h>




TitleScene::TitleScene()
{
	_keyAllOld = 1;
	_theta = 0;
}


TitleScene::~TitleScene()
{
}

Base_unq TitleScene::Update(Base_unq scene)
{
	if (CheckHitKeyAll() > 0 && _keyAllOld == 0)
	{
		return std::make_unique<CharSelectScene>();
	}
	_keyAllOld = CheckHitKeyAll();

	ImageMngIns.AddDraw({ ImageMngIns.getImage("back")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("logo")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y - 70, 0.0, LAYER::UI, 0 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("TitleMes")[0], SceneMngIns.ScreenCenter.x, 600 - static_cast<int>(std::sin(RAD(_theta)) * 60), 0.0, LAYER::UI, 10 });

	_theta = (_theta + 6) % 360;

	return std::move(scene);
}
