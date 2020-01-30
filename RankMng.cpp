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
   				fscanf_s(fp, "%d,", &_clearTimeRank[i][j]);
				if (_clearTimeRank[i][j] == -1)
				{
					_clearTimeRank[i][j] = TIME_MAX;
				}
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

		DrawGraph(NUM_SIZE_X * 0, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime / (MIN * 10)], true);
		DrawGraph(NUM_SIZE_X * 1, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime / MIN % 10], true);
		DrawGraph(NUM_SIZE_X * 2, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[10], true);
		DrawGraph(NUM_SIZE_X * 3, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % MIN / (SEC * 10)], true);
		DrawGraph(NUM_SIZE_X * 4, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % MIN / SEC % 10], true);
		DrawGraph(NUM_SIZE_X * 5, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[10], true);
		DrawGraph(NUM_SIZE_X * 6, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % SEC / 100 ], true);
		DrawGraph(NUM_SIZE_X * 7, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % 100 / 10], true);
		DrawGraph(NUM_SIZE_X * 8, RANK_OFFSET + RANK_DUR * i, ImageMngIns.getImage("number")[tmpTime % 10], true);
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
	}
	if (tmpRank != RANK_COUNT)
	{
		_clearTimeRank[stage][tmpRank] = clearTime;
	}

	saveClearTime();

	return tmpRank;
}

void RankMng::saveClearTime(void)
{
	FILE *fp;
	fopen_s(&fp, "data/cleartime.csv", "w");
	
	for (int i = 0; i < STAGE_COUNT; i++)
	{
		fprintf_s(fp, "%d,%d,%d\n", _clearTimeRank[i][0], _clearTimeRank[i][1], _clearTimeRank[i][2]);
	}

	fclose(fp);
}

RankMng::RankMng()
{
	RankInit();
	_rankScreen = MakeScreen(288, 195, false);
}


RankMng::~RankMng()
{
}
