#include <StageMng.h>

StageMng* StageMng::sInstance = nullptr;
std::vector<int> StageMng::_stageData;
int StageMng::_stageScreen;


void StageMng::Update(void)
{
	ImageMngIns.AddDraw({ _stageScreen,SceneMngIns.ScreenCenter.x,SceneMngIns.ScreenCenter.y,0.0,LAYER::CHAR,0 });
}

void StageMng::UpdateStagecount(int count)
{
	FILE *fp;
	fopen_s(&fp, "data/stage_data.dat", "rb");
	if (fp != nullptr)
	{
		fread(&_stageData[0], sizeof(_stageData[0]), _stageData.size(), fp);


	}
	else
	{
		AST();
	}
	fclose(fp);

	SetDrawScreen(_stageScreen);
	ClsDrawScreen();
	DrawGraph(0, 0, ImageMngIns.getImage("back")[0], true);
	for (int y = 0; y < StageHeight; y++)
	{
		for (int x = 0; x < StageWidth; x++)
		{
			if (_stageData[y * StageWidth + x] == 1)
			{
				DrawGraph(x * 32, y * 32, ImageMngIns.getImage("s_block")[0], true);
			}

		}
	}
}

int StageMng::getStageData(int val)
{
	if (val >= 0 && val < StageHeight * StageWidth)
	{
		return _stageData[val];
	}
	else
	{
		return 1;
	}
}

StageMng::StageMng()
{
	_stageScreen = MakeScreen(SceneMngIns.ScreenSize.x, SceneMngIns.ScreenSize.y, false);
	_stageData.resize(StageHeight * StageWidth);
	UpdateStagecount(0);
}


StageMng::~StageMng()
{
}
