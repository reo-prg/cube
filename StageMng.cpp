#include <StageMng.h>

StageMng* StageMng::sInstance = nullptr;
int StageMng::_stageData[StageHeight][StageWidth];
int StageMng::_stageScreen;


void StageMng::Update(void)
{
	ImageMngIns.AddDraw({ _stageScreen,SceneMngIns.ScreenCenter.x,SceneMngIns.ScreenCenter.y,0.0,LAYER::CHAR,0 });
}

void StageMng::UpdateStagecount(int count)
{
	FILE  *fp;
	fopen_s(&fp, fileName[count].c_str(), "r");

	if (fp == nullptr)
	{
		AST();
	}
	else
	{
		int objCount;				// オブジェクトの数
		Vector2Template<int> pos;	// オブジェクトの座標
		int type;	// オブジェクトの種類

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
				GameScene::_objList.emplace_back(new player({ static_cast<double>(pos.x), static_cast<double>(pos.y) }, 0.0, { 32,32 }));
			}
		}
		fclose(fp);
	}
	

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
	if (val.x >= 0 && val.x < StageWidth * BlockSize && val.y >= 0 && val.y < StageHeight * BlockSize)
	{
		return _stageData[val.y / BlockSize][val.x / BlockSize];
	}
	else
	{
		return 100;
	}
}

StageMng::StageMng()
{
	_stageScreen = MakeScreen(SceneMngIns.ScreenSize.x, SceneMngIns.ScreenSize.y, false);
}


StageMng::~StageMng()
{
}
