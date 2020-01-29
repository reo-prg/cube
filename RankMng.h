#pragma once
#include <DxLib.h>
#include <_debug/_DebugConOut.h>
#include <common/Vector2.h>

#define RankMngIns RankMng::getInstance()

#define STAGE_COUNT	8
#define RANK_COUNT	3

class RankMng
{
public:

	static RankMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new RankMng();
		}
		return *sInstance;
	}

	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void RankInit(void);	// ランキングの読み取り

	int getClearTime(int stage, int rank);	// クリアタイムの取得
	int checkRank(int stage, int clearTime);			// クリアタイムがランキングに入っているのかをチェック

private:
	static RankMng* sInstance;

	int _clearTimeRank[STAGE_COUNT][RANK_COUNT];	// クリアタイムの格納

	void saveClearTime(void);

	RankMng();
	~RankMng();
};

