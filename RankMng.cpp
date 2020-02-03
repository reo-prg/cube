#include "RankMng.h"

RankMng* RankMng::sInstance = nullptr;

void RankMng::RankInit(void)
{
	FILE *fp;
	fopen_s(&fp, "data/cleartime.csv", "r");

	if (fp == nullptr)
	{
		AST();
	}
	else
	{
		for (int i = 0; i < STAGE_COUNT; i++)
		{
			for (int j = 0; j < RANK_COUNT; j++)
			{
				fscanf_s(fp, "%d,", &_rankColor[i][j]);

				for (int data = 0; data < NAME_COUNT; data++)
				{
					int tmpVal;
					fscanf_s(fp, "%d,", &tmpVal);
					if (tmpVal == -1)
					{
						break;
					}
					_rankName[i][j].emplace_back(tmpVal);
				}
   				fscanf_s(fp, "%d", &_clearTimeRank[i][j]);
			}
		}
	}
	fclose(fp);
}

int RankMng::getClearTime(int stage, int rank)
{
	if (stage < 0 || stage > STAGE_COUNT)
	{
		AST();
		return 0;
	}
	if (rank < 0 || rank > RANK_COUNT)
	{
		AST();
		return 0;
	}
	return _clearTimeRank[stage][rank];
}

int RankMng::getRankScreen(int stage)
{
	if (stage < 0 || stage >= STAGE_COUNT)
	{
		AST();
		return -1;
	}
	SetDrawScreen(_rankScreen);
	ClsDrawScreen();
	DrawGraph(0, 0, ImageMngIns.getImage("back")[0], false);
	for (int i = 0; i < RANK_COUNT; i++)
	{
		int tmpTime = _clearTimeRank[stage][i];
		int count = 0;

		if (_rankColor[stage][i] >= 0 && _rankColor[stage][i] < 8)
		{
			DrawGraph(0, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("player")[_rankColor[stage][i] * 2], true);
		}
		for (auto data : _rankName[stage][i])
		{
			DrawGraph(CHAR_SIZE * count + 60, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("char")[data], true);
			count++;
		}
		
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 0, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime / (MIN * 10)], true);
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 1, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime / MIN % 10], true);
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 2, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[10], true);
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 3, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % MIN / (SEC * 10)], true);
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 4, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % MIN / SEC % 10], true);
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 5, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[10], true);
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 6, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % SEC / 100 ], true);
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 7, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % 100 / 10], true);
		DrawGraph(RANK_OFFSET_X + NUM_SIZE_X * 8, RANK_OFFSET_Y + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % 10], true);
	}
	return _rankScreen;
}

int RankMng::checkRank(int stage, int clearTime)
{
	int tmpRank = RANK_COUNT;
	for (int i = 0; i < RANK_COUNT; i++)
	{
		if (clearTime < _clearTimeRank[stage][i])
		{
			tmpRank = i;
			break;
		}
	}
	for (int i = RANK_COUNT - 1; i > tmpRank; i--)
	{
		_clearTimeRank[stage][i] = _clearTimeRank[stage][i - 1];
		_rankName[stage][i] = _rankName[stage][i - 1];
		_rankColor[stage][i] = _rankColor[stage][i - 1];
	}
	if (tmpRank != RANK_COUNT)
	{
		_clearTimeRank[stage][tmpRank] = clearTime;
		_rankName[stage][tmpRank] = _name;
		_rankColor[stage][tmpRank] = StageMngIns.getPlayerColor();
	}

	saveClearTime();

	return tmpRank;
}

void RankMng::setName(std::vector<int> val)
{
	_name = val;
}

void RankMng::saveClearTime(void)
{
	FILE *fp;
	fopen_s(&fp, "data/cleartime.csv", "w");
	
	for (int i = 0; i < STAGE_COUNT; i++)
	{
		for (int j = 0; j < RANK_COUNT; j++)
		{
			fprintf_s(fp, "%d,", _rankColor[i][j]);
			int tmpCount = 0;
			for (auto data : _rankName[i][j])
			{
				fprintf_s(fp, "%d,", data);
				tmpCount++;
			}
			if (tmpCount < NAME_COUNT)
			{
				fprintf_s(fp, "-1,");
			}
			fprintf_s(fp, "%d\n", _clearTimeRank[i][j]);
		}
	}

	fclose(fp);
}

RankMng::RankMng()
{
	RankInit();
	_rankScreen = MakeScreen(480, 195, false);
}


RankMng::~RankMng()
{
}
