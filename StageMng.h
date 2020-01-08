#pragma once
#include <DxLib.h>
#include <Graphic/ImageMng.h>
#include <Scene/SceneMng.h>
#include <_debug/_DebugConOut.h>

#define StageMngIns StageMng::getInstance()
#define StageHeight	24
#define StageWidth	32
#define BlockSize	32

class StageMng
{
public:

	static StageMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new StageMng();
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
	
	void Update(void);
	void UpdateStagecount(int count);

	int getStageData(int);
private:
	static StageMng* sInstance;

	static std::vector<int> _stageData;			// ステージの情報を保存
	static int _stageScreen;					// ステージ用のスクリーン

	StageMng();
	~StageMng();
};

