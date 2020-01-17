#include <Scene/TitleScene.h>




TitleScene::TitleScene()
{
	_keyAllOld = 1;
	_theta = 0;
	_sceneMoveFlag = false;
	_mesPos_x = SceneMngIns.ScreenCenter.x;
}


TitleScene::~TitleScene()
{
}

Base_unq TitleScene::Update(Base_unq scene)
{
	if (!_sceneMoveFlag)
	{
		if (CheckHitKeyAll() > 0 && _keyAllOld == 0)
		{
			_sceneMoveFlag = true;
		}
		_keyAllOld = CheckHitKeyAll();
	}
	else
	{
		_mesPos_x += 10;
		if (_mesPos_x >= SceneMngIns.ScreenSize.x + MES_SIZE_X / 2)
		{
			scene = std::make_unique<CharSelectScene>();
		}
	}

	Draw();
	_theta = (_theta + 6) % 360;

	return std::move(scene);
}

void TitleScene::Draw(void)
{
	ImageMngIns.AddDraw({ ImageMngIns.getImage("back")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("logo")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y - 70, 0.0, LAYER::UI, 0 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("TitleMes")[0], _mesPos_x, 600 - static_cast<int>(std::sin(RAD(_theta)) * 60), 0.0, LAYER::UI, 10 });
}
