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
}

RankMng::RankMng()
{

}


RankMng::~RankMng()
{
}
