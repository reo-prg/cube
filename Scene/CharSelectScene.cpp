#include <Scene/CharSelectScene.h>



CharSelectScene::CharSelectScene()
{
	_charSelPos_x = -800;
	_cursorPos = 0;
	_charMoveFlag = true;

	_keyOld.try_emplace(KEY_INPUT_LEFT, 1);
	_keyOld.try_emplace(KEY_INPUT_RIGHT, 1);
	_keyOld.try_emplace(KEY_INPUT_DOWN, 1);
	_keyOld.try_emplace(KEY_INPUT_SPACE, 1);
}


CharSelectScene::~CharSelectScene()
{
}

Base_unq CharSelectScene::Update(Base_unq scene)
{
	if (_charMoveFlag)
	{
		charMove();
	}
	else
	{
		scene = charSelect(std::move(scene));
	}

	ImageMngIns.AddDraw({ ImageMngIns.getImage("back")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("logo")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y - 70, 0.0, LAYER::UI, 0 });
	for (int i = 0; i < 8; i++)
	{
		ImageMngIns.AddDraw({ ImageMngIns.getImage("player")[i * 2], PL_SPACE * i + _charSelPos_x, 600, 0.0, LAYER::CHAR, 0 });
	}

	return std::move(scene);
}

void CharSelectScene::charMove(void)
{
	_charSelPos_x += 10;
	if (_charSelPos_x > SceneMngIns.ScreenCenter.x - (PL_SPACE * 7 + BlockSize) / 2)
	{
		_charSelPos_x = SceneMngIns.ScreenCenter.x - (PL_SPACE * 7 + BlockSize) / 2;
		_charMoveFlag = false;
	}
}


Base_unq CharSelectScene::charSelect(Base_unq scene)
{
	if (keyUpdate(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		_cursorPos--;
		if (_cursorPos < 0)
		{
			_cursorPos = 7;
		}
	}
	if (keyUpdate(KEY_INPUT_RIGHT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		_cursorPos++;
		if (_cursorPos > 7)
		{
			_cursorPos = 0;
		}
	}
	if (keyUpdate(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		scene = std::make_unique<TitleScene>();
	}
	


	ImageMngIns.AddDraw({ ImageMngIns.getImage("cursor")[0], PL_SPACE * _cursorPos + _charSelPos_x, 600 + BlockSize, 0.0, LAYER::UI, 0 });

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
