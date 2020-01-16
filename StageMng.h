#pragma once
#include <DxLib.h>
#include <vector>
#include <Graphic/ImageMng.h>
#include <Scene/SceneMng.h>
#include <_debug/_DebugConOut.h>
#include <Objects/LockCube.h>
#include <Objects/FallCube.h>

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

	int getStageData(Vector2Template<int> val);
	void resetObj(void);
private:
	static StageMng* sInstance;

	static int _stageData[StageHeight][StageWidth];			// ステージの情報を保存
	static int _stageScreen;								// ステージ用のスクリーン
	static std::vector<std::pair<Vector2Template<int>, int>> _objInitPos;	// オブジェクトの初期位置を保存

	const std::vector<std::string> fileName = { "data/stage_0.csv" };


	StageMng();
	~StageMng();
};

