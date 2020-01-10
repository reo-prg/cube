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
	FILE *fp;
	fopen_s(&fp, "data/stage_data.dat", "rb");
	if (fp != nullptr)
	{
		int cubeCount;		// �L���[�u�̐�
		int pos[2];			// �ǂݎ�������W�̈ꎞ�i�[�ꏊ
		int type;			// �L���[�u�̎��

		fread(&_stageData[0], sizeof(_stageData[0][0]), StageHeight * StageWidth, fp);

		fread(&cubeCount, sizeof(int), 1, fp);
		for (int i = 0; i < cubeCount; i++)
		{
			fread(pos, sizeof(int), 2, fp);
			fread(&type, sizeof(int), 1, fp);
			switch (type)
			{
			case 0:
				GameScene::_objList.emplace_back(new LockCube({ pos[0],pos[1] }, { 32,32 }));
				break;
			case 1:
				GameScene::_objList.emplace_back(new FallCube({ pos[0],pos[1] }, { 32,32 }));
				break;
			default:
				AST();
				break;
			}
		}
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
			if (_stageData[y][x] == 1)
			{
				DrawGraph(x * 32, y * 32, ImageMngIns.getImage("s_cube")[0], true);
			}

		}
	}
}

int StageMng::getStageData(Vector2Template<int> val)
{
	if (val.x >= 0 && val.x < StageWidth && val.y >= 0 && val.y < StageHeight)
	{
		return _stageData[val.y][val.x];
	}
	else
	{
		return 1;
	}
}

StageMng::StageMng()
{
	_stageScreen = MakeScreen(SceneMngIns.ScreenSize.x, SceneMngIns.ScreenSize.y, false);
	UpdateStagecount(0);
}


StageMng::~StageMng()
{
}
