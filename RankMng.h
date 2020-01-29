#pragma once
#include <DxLib.h>
#include <_debug/_DebugConOut.h>

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

	void RankInit(void);	// �����L���O�̓ǂݎ��

private:
	static RankMng* sInstance;

	int _clearTimeRank[STAGE_COUNT][RANK_COUNT];	// �N���A�^�C���̊i�[

	RankMng();
	~RankMng();
};

