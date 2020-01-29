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

int RankMng::checkRank(int stage, int clearTime)
{
	int tmpRank = RANK_COUNT;
	for (int i = 0; i < RANK_COUNT; i++)
	{
		if (clearTime < _clearTimeRank[stage][i])
		{
			tmpRank = i;
		}
	}
	for (int i = RANK_COUNT - 1; i > tmpRank; i++)
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
		fprintf_s(fp, "%d,%d,%d/n", _clearTimeRank[i][0], _clearTimeRank[i][1], _clearTimeRank[i][2]);
	}

	fclose(fp);
}

RankMng::RankMng()
{

}


RankMng::~RankMng()
{
}
