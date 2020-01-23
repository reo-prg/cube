#include <StageMng.h>

StageMng* StageMng::sInstance = nullptr;

void StageMng::Update(void)
{
	// �X�N���[���̕`��
	ImageMngIns.AddDraw({ _stageScreen,SceneMngIns.ScreenCenter.x,SceneMngIns.ScreenCenter.y,0.0,LAYER::CHAR,0 });
}

void StageMng::UpdateStagecount(int count)
{
	_objInitPos.clear();

	// �f�[�^�̓ǂݍ��݂ƃI�u�W�F�N�g�̔z�u
	FILE  *fp;
	fopen_s(&fp, fileName[count].c_str(), "r");

	if (fp == nullptr)
	{
		AST();
	}
	else
	{
		int objCount;				// �I�u�W�F�N�g�̐�
		Vector2Template<int> pos;	// �I�u�W�F�N�g�̍��W
		int type;	// �I�u�W�F�N�g�̎��

		for (int i = 0; i < StageHeight; i++)
		{
			for (int j = 0; j < StageWidth; j++)
			{
				fscanf_s(fp, "%d,", &_stageData[i][j]);
			}
		}

		fscanf_s(fp, "%d,", &objCount);
		for (int i = 0; i < objCount; i++)
		{
			fscanf_s(fp, "%d,%d,%d,", &pos.x, &pos.y, &type);
			switch (type)
			{
			case 0:
				GameScene::_objList.emplace_back(new FallCube(pos, { 32,32 }));
				break;
			case 1:
				GameScene::_objList.emplace_back(new LockCube(pos, { 32,32 }));
				break;
			case 10:
				GameScene::_objList.emplace_back(new player({ static_cast<double>(pos.x), static_cast<double>(pos.y) + PLAYER_OFFSET }, 0.0, { 32,32 }, _playerColor));
			}
			_objInitPos.emplace_back(std::make_pair(Vector2Template<int>{ pos.x,pos.y },type));
		}
		fclose(fp);
	}
	
	// �X�e�[�W��ʂ̃X�N���[���ɂ��炩���ߕ`��
	SetDrawScreen(_stageScreen);
	ClsDrawScreen();
	DrawGraph(0, 0, ImageMngIns.getImage("back")[0], true);
	for (int y = 0; y < StageHeight; y++)
	{
		for (int x = 0; x < StageWidth; x++)
		{
			if (_stageData[y][x] != -1)
			{
				DrawGraph(x * 32, y * 32, ImageMngIns.getImage("s_cube")[_stageData[y][x]], true);
			}

		}
	}
}

int StageMng::getStageData(Vector2Template<int> val)
{
	if (val.x >= 0 && val.x < StageWidth * CubeSize && val.y >= 0 && val.y < StageHeight * CubeSize)
	{
		return _stageData[val.y / CubeSize][val.x / CubeSize];
	}
	else
	{
		return 100;
	}
}

int StageMng::getPlayerColor(void)
{
	return _playerColor;
}

void StageMng::setPlayerColor(int color)
{
	if (color >= 0 && color < 8)
	{
		_playerColor = color;
	}
	else
	{
		_playerColor = 0;
	}
}

void StageMng::resetObj(void)
{
	GameScene::_objList.clear();
	for (auto data : _objInitPos)
	{
		switch (data.second)
		{
		case 0:
			GameScene::_objList.emplace_back(new FallCube(data.first, { 32,32 }));
			break;
		case 1:
			GameScene::_objList.emplace_back(new LockCube(data.first, { 32,32 }));
			break;
		case 10:
			GameScene::_objList.emplace_back(new player({ static_cast<double>(data.first.x), static_cast<double>(data.first.y) }, 0.0, { 32,32 }, _playerColor));
		}
	}
}

StageMng::StageMng()
{
	// ������
	// �X�N���[���̍쐬
	_stageScreen = MakeScreen(SceneMngIns.ScreenSize.x, SceneMngIns.ScreenSize.y, false);
}


StageMng::~StageMng()
{
}
