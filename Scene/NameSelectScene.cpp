#include <Scene/NameSelectScene.h>

std::vector<int> NameSelectScene::_name;

NameSelectScene::NameSelectScene()
{
	_cursor = { 0,0 };
	_charCount = 0;
	_update = &NameSelectScene::NameSceneMove;
	_sceneMoveFlag = false;
	_scenePos_x = -500;

	_nameScreen = MakeScreen(SceneMngIns.ScreenSize.x, SceneMngIns.ScreenSize.y, false);
	SetDrawScreen(_nameScreen);
	ClsDrawScreen();
	DrawGraph(0, 0, ImageMngIns.getImage("back")[0], true);
	DrawRotaGraph(SceneMngIns.ScreenCenter.x, 50, 1.0, 0.0, ImageMngIns.getImage("SelectMes")[2], true);
	DrawRotaGraph(SceneMngIns.ScreenCenter.x, GUIDE_POS_Y, 1.0, 0.0, ImageMngIns.getImage("guide")[3], true);
	for (int i = 0; i < CHAR_COUNT_Y; i++)
	{
		for (int j = 0; j < CHAR_COUNT_X; j++)
		{
			DrawGraph(static_cast<int>(CHAR_OFFSET_X) + (CHAR_SIZE + CHAR_DUR_X) * j, CHAR_OFFSET_Y + (CHAR_SIZE + CHAR_DUR_Y) * i, ImageMngIns.getImage("char")[i * 10 + j], true);
		}
	}
	for (int i = 0; i < NAME_COUNT_MAX; i++)
	{
		DrawLine(NAME_OFFSET_X + CHAR_SIZE * i + 1, NAME_OFFSET_Y + CHAR_SIZE, NAME_OFFSET_X + CHAR_SIZE * (i + 1) - 1, NAME_OFFSET_Y + CHAR_SIZE, 0x000000);
	}

	_keyOld.try_emplace(KEY_INPUT_LEFT, 1);
	_keyOld.try_emplace(KEY_INPUT_RIGHT, 1);
	_keyOld.try_emplace(KEY_INPUT_UP, 1);
	_keyOld.try_emplace(KEY_INPUT_DOWN, 1);
	_keyOld.try_emplace(KEY_INPUT_RSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_LSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_SPACE, 1);
}


NameSelectScene::~NameSelectScene()
{
}

Base_unq NameSelectScene::Update(Base_unq scene)
{
	if ((this->*_update)())
	{
		scene = std::make_unique<CharSelectScene>();
	}
	Draw();
	return std::move(scene);
}

bool NameSelectScene::NameSceneMove(void)
{
	_scenePos_x += 10;

	if (!_sceneMoveFlag)
	{
		if (_scenePos_x >= SceneMngIns.ScreenCenter.x)
		{
			_scenePos_x = SceneMngIns.ScreenCenter.x;
			_update = &NameSelectScene::NameSceneUpdate;
		}
	}
	else
	{
		if (_scenePos_x >= SceneMngIns.ScreenSize.x + 500)
		{
			return true;
		}
	}
	return false;
}

bool NameSelectScene::NameSceneUpdate(void)
{
	// カーソルの上下左右移動
	if ((keyUpdate(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_LEFT) == 1) || (SceneMngIns.GetStick().x < -STICK_INPUT && SceneMngIns.GetStickOld().x >= -STICK_INPUT))
	{
		_cursor.x--;
		if (_cursor.x < 0)
		{
			_cursor.x = CHAR_COUNT_X - 1;
		}
	}
	else if ((keyUpdate(KEY_INPUT_RIGHT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 1) || (SceneMngIns.GetStick().x > STICK_INPUT && SceneMngIns.GetStickOld().x <= STICK_INPUT))
	{
		_cursor.x++;
		if (_cursor.x >= CHAR_COUNT_X)
		{
			_cursor.x = 0;
		}
	}
	else if ((keyUpdate(KEY_INPUT_UP) == 0 && CheckHitKey(KEY_INPUT_UP) == 1) || (SceneMngIns.GetStick().y < -STICK_INPUT && SceneMngIns.GetStickOld().y >= -STICK_INPUT))
	{
		_cursor.y--;
		if (_cursor.y < 0)
		{
			_cursor.y = CHAR_COUNT_Y - 1;
		}
	}
	else if ((keyUpdate(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_DOWN) == 1) || (SceneMngIns.GetStick().y > STICK_INPUT && SceneMngIns.GetStickOld().y <= STICK_INPUT))
	{
		_cursor.y++;
		if (_cursor.y >= CHAR_COUNT_Y)
		{
			_cursor.y = 0;
		}
	}
	else
	{
		// なにもしない
	}

	// 決定
	if ((keyUpdate(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_SPACE) == 1) || ((SceneMngIns.GetPad() & PAD_INPUT_2) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_2) == 0))
	{
		if (_cursor.x == 9 && _cursor.y == 9)
		{
			if (_charCount > 0)
			{
				_sceneMoveFlag = true;
				_update = &NameSelectScene::NameSceneMove;
				RankMngIns.setName(_name);
			}
		}
		else if (_cursor.x == 8 && _cursor.y == 9)
		{
			if (_charCount > 0)
			{
				_name.pop_back();
				_charCount--;
			}
		}
		else if ((_cursor.x == 1 && (_cursor.y == 7 || _cursor.y == 9)) || (_cursor.x == 3 && (_cursor.y == 7 || _cursor.y == 9)))
		{
			// なにもしない
		}
		else
		{
			if (_charCount < NAME_COUNT_MAX)
			{
				_name.emplace_back(_cursor.y * CHAR_COUNT_X + _cursor.x);
				_charCount++;
			}
		}
	}
	return false;
}

int NameSelectScene::keyUpdate(int key)
{
	if (_keyOld.find(key) == _keyOld.end())
	{
		return 1;
	}

	int tmpState = _keyOld[key];
	_keyOld[key] = CheckHitKey(key);
	return tmpState;
}

void NameSelectScene::Draw(void)
{
	ImageMngIns.AddDraw({ ImageMngIns.getImage("back")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -10 });
	ImageMngIns.AddDraw({ _nameScreen, _scenePos_x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, 0 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("c_flame")[0], static_cast<int>(CHAR_OFFSET_X + CHAR_SIZE / 2) + (CHAR_SIZE + CHAR_DUR_X) * _cursor.x + _scenePos_x - SceneMngIns.ScreenCenter.x,
								CHAR_OFFSET_Y + static_cast<int>(CHAR_SIZE / 2) + (CHAR_SIZE + CHAR_DUR_Y) * _cursor.y, 0.0, LAYER::UI, 0 });
	for (int i = 0; i < _charCount; i++)
	{
		ImageMngIns.AddDraw({ ImageMngIns.getImage("char")[_name[i]], NAME_OFFSET_X + CHAR_SIZE / 2 + CHAR_SIZE * i + _scenePos_x - SceneMngIns.ScreenCenter.x, NAME_OFFSET_Y + CHAR_SIZE / 2, 0.0, LAYER::CHAR, 0 });
	}
}
