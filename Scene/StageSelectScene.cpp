#include <Scene/StageSelectScene.h>



StageSelectScene::StageSelectScene()
{
	_stagePos_x = -720;
	_cursor = 0;
	_stageMoveFlag = true;
	_sceneMoveFlag = false;

	_keyOld.try_emplace(KEY_INPUT_LEFT, 1);
	_keyOld.try_emplace(KEY_INPUT_RIGHT, 1);
	_keyOld.try_emplace(KEY_INPUT_UP, 1);
	_keyOld.try_emplace(KEY_INPUT_DOWN, 1);
	_keyOld.try_emplace(KEY_INPUT_RSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_SPACE, 1);

	_stageViewScreen = MakeScreen(STAGE_SIZE_X * 2, STAGE_SIZE_Y * 2, false);
}


StageSelectScene::~StageSelectScene()
{
}

Base_unq StageSelectScene::Update(Base_unq scene)
{
	if (_stageMoveFlag)
	{
		scene = stageMove(std::move(scene));
	}
	else
	{
		scene = stageSelect(std::move(scene));
	}

	Draw();
	return std::move(scene);
}

Base_unq StageSelectScene::stageMove(Base_unq scene)
{
	_stagePos_x += 10;
	if (!_sceneMoveFlag)
	{
		if (_stagePos_x >= STAGE_OFFSET)
		{
			_stagePos_x = STAGE_OFFSET;
			_stageMoveFlag = false;
		}
	}
	else
	{
		if (_stagePos_x >= SceneMngIns.ScreenSize.x + 400)
		{
			return std::move(_tmpScene);
		}
	}
	return std::move(scene);
}

Base_unq StageSelectScene::stageSelect(Base_unq scene)
{
	if (keyUpdate(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		_cursor--;
		if (_cursor < 0)
		{
			_cursor = 7;
		}
	}
	if (keyUpdate(KEY_INPUT_RIGHT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		_cursor++;
		if (_cursor > 7)
		{
			_cursor = 0;
		}
	}
	if (keyUpdate(KEY_INPUT_UP) == 0 && CheckHitKey(KEY_INPUT_UP) == 1)
	{
		_cursor += 4;
		if (_cursor > 7)
		{
			_cursor = _cursor - 8;
		}
	}
	if (keyUpdate(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		_cursor -= 4;
		if (_cursor < 0)
		{
			_cursor = _cursor + 8;
		}
	}

	if (keyUpdate(KEY_INPUT_RSHIFT) == 0 && CheckHitKey(KEY_INPUT_RSHIFT) == 1)
	{
		_stageMoveFlag = true;
		_sceneMoveFlag = true;
		_tmpScene = std::make_unique<CharSelectScene>();
	}
	if (keyUpdate(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		_stageMoveFlag = true;
		_sceneMoveFlag = true;
		_tmpScene = std::make_unique<GameScene>(_cursor);
	}

	// 枠の描画
	ImageMngIns.AddDraw({ ImageMngIns.getImage("s_flame")[0], STAGE_OFFSET + (_cursor % 4) * (STAGE_SIZE_X + STAGE_SPACE), 470 + (_cursor / 4) * (STAGE_SIZE_Y + STAGE_SPACE), 0.0, LAYER::UI, 0 });
	
	// 上の拡大されたステージの描画
	SetDrawScreen(_stageViewScreen);
	ClsDrawScreen();
	DrawRotaGraph(STAGE_SIZE_X, STAGE_SIZE_Y, 2.0, 0.0, ImageMngIns.getImage("stage")[_cursor], false);
	ImageMngIns.AddDraw({ _stageViewScreen, SceneMngIns.ScreenCenter.x, 250, 0.0, LAYER::UI, 0 });

	ImageMngIns.AddDraw({ ImageMngIns.getImage("flame")[0], SceneMngIns.ScreenCenter.x, 250, 0.0, LAYER::UI, 100 });

	// ガイドの描画
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[0], BACK_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[1], NEXT_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[3], SELECT_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });

	return std::move(scene);
}

int StageSelectScene::keyUpdate(int key)
{
	if (_keyOld.find(key) == _keyOld.end())
	{
		return 1;
	}

	int tmpState = _keyOld[key];
	_keyOld[key] = CheckHitKey(key);
	return tmpState;
}

void StageSelectScene::Draw()
{
	ImageMngIns.AddDraw({ ImageMngIns.getImage("back")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("SelectMes")[1], _stagePos_x + SceneMngIns.ScreenCenter.x - STAGE_OFFSET, 52, 0.0, LAYER::BG, 0 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("player")[StageMngIns.getPlayerColor() * 2], _stagePos_x + 700, 658, 0.0, LAYER::UI, 0 });			// 座標はステージ一覧の右下

	for (int i = 0; i < 8; i++)
	{
		ImageMngIns.AddDraw({ ImageMngIns.getImage("stage")[i], (i % 4) * (STAGE_SIZE_X + STAGE_SPACE) + _stagePos_x, 470 + (i / 4) * (STAGE_SIZE_Y + STAGE_SPACE), 0.0, LAYER::CHAR, 0 });
	}
}
