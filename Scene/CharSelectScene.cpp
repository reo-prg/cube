#include <Scene/CharSelectScene.h>



CharSelectScene::CharSelectScene()
{
	_charSelPos_x = -600;
	_cursor = 0;
	_sceneMoveFlag = false;
	_charSel = &CharSelectScene::charMove;

	_keyOld.try_emplace(KEY_INPUT_LEFT, 1);
	_keyOld.try_emplace(KEY_INPUT_RIGHT, 1);
	_keyOld.try_emplace(KEY_INPUT_RSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_SPACE, 1);
}


CharSelectScene::~CharSelectScene()
{
}

Base_unq CharSelectScene::Update(Base_unq scene)
{
	scene = (this->*_charSel)(std::move(scene));

	Draw();

	return std::move(scene);
}

Base_unq CharSelectScene::charMove(Base_unq scene)
{
	_charSelPos_x += 10;
	if (!_sceneMoveFlag)
	{
		if (_charSelPos_x > SceneMngIns.ScreenCenter.x - PL_POS_X)
		{
			_charSelPos_x = SceneMngIns.ScreenCenter.x - PL_POS_X;
			_charSel = &CharSelectScene::charSelect;
		}
	}
	else
	{
		if (_charSelPos_x > SceneMngIns.ScreenSize.x + 400)
		{
			return std::move(_tmpScene);
		}
	}

	return std::move(scene);
}


Base_unq CharSelectScene::charSelect(Base_unq scene)
{
	if ((keyUpdate(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_LEFT) == 1) || (SceneMngIns.GetStick().x < -STICK_INPUT && SceneMngIns.GetStickOld().x >= -STICK_INPUT))
	{
		_cursor--;
		if (_cursor < 0)
		{
			_cursor = 7;
		}
	}
	if ((keyUpdate(KEY_INPUT_RIGHT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 1) || (SceneMngIns.GetStick().x > STICK_INPUT && SceneMngIns.GetStickOld().x <= STICK_INPUT))
	{
		_cursor++;
		if (_cursor > 7)
		{
			_cursor = 0;
		}
	}
	if ((keyUpdate(KEY_INPUT_RSHIFT) == 0 && CheckHitKey(KEY_INPUT_RSHIFT) == 1) || ((SceneMngIns.GetPad() & PAD_INPUT_1) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_1) == 0))
	{
		_sceneMoveFlag = true;
		_charSel = &CharSelectScene::charMove;
		_tmpScene = std::make_unique<TitleScene>();
	}
	if (keyUpdate(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_SPACE) == 1 || ((SceneMngIns.GetPad() & PAD_INPUT_2) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_2) == 0))
	{
		_sceneMoveFlag = true;
		_charSel = &CharSelectScene::charMove;
		StageMngIns.setPlayerColor(_cursor);
		_tmpScene = std::make_unique<StageSelectScene>();
	}

	// ÉJÅ[É\ÉãÇÃï`âÊ
	ImageMngIns.AddDraw({ ImageMngIns.getImage("cursor")[0], PL_SPACE * _cursor + _charSelPos_x, 400 + CubeSize, 0.0, LAYER::UI, 0 });
	// ÉKÉCÉhÇÃï`âÊ
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[0], BACK_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[1], NEXT_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[2], SELECT_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });

	return std::move(scene);
}

int CharSelectScene::keyUpdate(int key)
{
	if (_keyOld.find(key) == _keyOld.end())
	{
		return 1;
	}

	int tmpState = _keyOld[key];
	_keyOld[key] = CheckHitKey(key);
	return tmpState;
}

void CharSelectScene::Draw(void)
{
	ImageMngIns.AddDraw({ ImageMngIns.getImage("back")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("SelectMes")[0], _charSelPos_x + PL_POS_X, 200, 0.0, LAYER::BG, 0 });
	for (int i = 0; i < 8; i++)
	{
		ImageMngIns.AddDraw({ ImageMngIns.getImage("player")[i * 2], PL_SPACE * i + _charSelPos_x, 400, 0.0, LAYER::CHAR, 0 });
	}
}
