#include <Scene/StageSelectScene.h>



StageSelectScene::StageSelectScene()
{
	_stagePos_x = -720;
	_cursor = 0;
	_sceneMoveFlag = false;
	_stageSel = &StageSelectScene::stageMove;

	_keyOld.try_emplace(KEY_INPUT_LEFT, 1);
	_keyOld.try_emplace(KEY_INPUT_RIGHT, 1);
	_keyOld.try_emplace(KEY_INPUT_UP, 1);
	_keyOld.try_emplace(KEY_INPUT_DOWN, 1);
	_keyOld.try_emplace(KEY_INPUT_RSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_LSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_SPACE, 1);

	_stageViewScreen = MakeScreen(STAGE_SIZE_X * 2, STAGE_SIZE_Y * 2, false);
	_drawRank = RankMngIns.getRankScreen(0);
}


StageSelectScene::~StageSelectScene()
{
}

Base_unq StageSelectScene::Update(Base_unq scene)
{
	scene = (this->*_stageSel)(std::move(scene));

	Draw();
	return std::move(scene);
}

Base_unq StageSelectScene::stageMove(Base_unq scene)
{
	_stagePos_x += 10;
	// 次のシーンに行く時のアニメーション処理
	if (!_sceneMoveFlag)
	{
		if (_stagePos_x >= STAGE_OFFSET)
		{
			_stagePos_x = STAGE_OFFSET;
			_stageSel = &StageSelectScene::stageSelect;
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
	// カーソルの上下左右移動
	if ((keyUpdate(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_LEFT) == 1) || (SceneMngIns.GetStick().x < -STICK_INPUT && SceneMngIns.GetStickOld().x >= -STICK_INPUT))
	{
		_cursor--;
		if (_cursor < 0)
		{
			_cursor = STAGE_COUNT - 1;
		}
		_drawRank = RankMngIns.getRankScreen(_cursor);
	}
	else if ((keyUpdate(KEY_INPUT_RIGHT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 1) || (SceneMngIns.GetStick().x > STICK_INPUT && SceneMngIns.GetStickOld().x <= STICK_INPUT))
	{
		_cursor++;
		if (_cursor >= STAGE_COUNT)
		{
			_cursor = 0;
		}
		_drawRank = RankMngIns.getRankScreen(_cursor);
	}
	else if ((keyUpdate(KEY_INPUT_UP) == 0 && CheckHitKey(KEY_INPUT_UP) == 1) || (SceneMngIns.GetStick().y < -STICK_INPUT && SceneMngIns.GetStickOld().y >= -STICK_INPUT))
	{
		_cursor += 4;
		if (_cursor >= STAGE_COUNT)
		{
			_cursor = _cursor - STAGE_COUNT;
		}
		_drawRank = RankMngIns.getRankScreen(_cursor);
	}
	else if ((keyUpdate(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_DOWN) == 1) || (SceneMngIns.GetStick().y > STICK_INPUT && SceneMngIns.GetStickOld().y <= STICK_INPUT))
	{
		_cursor -= 4;
		if (_cursor < 0)
		{
			_cursor = _cursor + STAGE_COUNT;
		}
		_drawRank = RankMngIns.getRankScreen(_cursor);
	}
	else
	{
		// なにもしない
	}

	// 決定、もどる
	if ((keyUpdate(KEY_INPUT_LSHIFT) == 0 && CheckHitKey(KEY_INPUT_LSHIFT) == 1) || (keyUpdate(KEY_INPUT_RSHIFT) == 0 && CheckHitKey(KEY_INPUT_RSHIFT) == 1) || ((SceneMngIns.GetPad() & PAD_INPUT_3) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_3) == 0))
	{
		_sceneMoveFlag = true;
		_stageSel = &StageSelectScene::stageMove;
		_tmpScene = std::make_unique<CharSelectScene>();
	}
	if ((keyUpdate(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_SPACE) == 1) || ((SceneMngIns.GetPad() & PAD_INPUT_2) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_2) == 0))
	{
		_sceneMoveFlag = true;
		_stageSel = &StageSelectScene::stageMove;
		_tmpScene = std::make_unique<GameScene>(_cursor);
	}

	// 枠の描画
	ImageMngIns.AddDraw({ ImageMngIns.getImage("s_flame")[0], STAGE_OFFSET + (_cursor % 4) * (STAGE_SIZE_X + STAGE_SPACE), 470 + (_cursor / 4) * (STAGE_SIZE_Y + STAGE_SPACE), 0.0, LAYER::UI, 0 });
	
	// 上の拡大されたステージの描画
	SetDrawScreen(_stageViewScreen);
	ClsDrawScreen();
	DrawRotaGraph(STAGE_SIZE_X, STAGE_SIZE_Y, 2.0, 0.0, ImageMngIns.getImage("stage")[_cursor], false);
	ImageMngIns.AddDraw({ _stageViewScreen, SceneMngIns.ScreenCenter.x / 2, 250, 0.0, LAYER::UI, 0 });

	//ImageMngIns.AddDraw({ ImageMngIns.getImage("flame")[0], SceneMngIns.ScreenCenter.x, 250, 0.0, LAYER::UI, 100 });

	// ガイドの描画
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[0], BACK_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[1], NEXT_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("guide")[3], SELECT_POS_X, GUIDE_POS_Y, 0.0, LAYER::UI, 1000 });

	// ランキングの描画
	ImageMngIns.AddDraw({ ImageMngIns.getImage("rank")[0], SceneMngIns.ScreenCenter.x / 2 + STAGE_SIZE_X * 2, 250, 0.0, LAYER::UI, 0 });
	ImageMngIns.AddDraw({ _drawRank, SceneMngIns.ScreenCenter.x / 2 + STAGE_SIZE_X * 2 + RANK_SIZE_X / 2 + 144, 250, 0.0, LAYER::UI, 0 });

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
	ImageMngIns.AddDraw({ ImageMngIns.getImage("player")[StageMngIns.getPlayerColor() * 2], (_cursor % 4) * (STAGE_SIZE_X + STAGE_SPACE) + _stagePos_x - 85, 470 + (_cursor / 4) * (STAGE_SIZE_Y + STAGE_SPACE) + 32, 0.0, LAYER::UI, 200 });			// 座標はステージ一覧の右下

	for (int i = 0; i < STAGE_COUNT; i++)
	{
		ImageMngIns.AddDraw({ ImageMngIns.getImage("stage")[i], (i % 4) * (STAGE_SIZE_X + STAGE_SPACE) + _stagePos_x, 470 + (i / 4) * (STAGE_SIZE_Y + STAGE_SPACE), 0.0, LAYER::CHAR, 0 });
	}
}
