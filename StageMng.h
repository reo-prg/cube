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
	void setPlayerColor(int);
	void resetObj(void);
private:
	static StageMng* sInstance;

	int _stageData[StageHeight][StageWidth];						// ステージの情報を保存
	int _stageScreen;												// ステージ用のスクリーン
	std::vector<std::pair<Vector2Template<int>, int>> _objInitPos;	// オブジェクトの初期位置を保存
	
	int _playerColor;												// プレイヤーの色

	const std::vector<std::string> fileName = { "data/stage_0.csv", "data/stage_1.csv", "data/stage_2.csv","data/stage_3.csv", 
												"data/stage_4.csv", "data/stage_5.csv", "data/stage_6.csv", "data/stage_7.csv", };


	StageMng();
	~StageMng();
};

