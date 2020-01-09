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

	int getStageData(Vector2Template<int> val);
private:
	static StageMng* sInstance;

	static int _stageData[StageHeight][StageWidth];			// �X�e�[�W�̏���ۑ�
	static int _stageScreen;					// �X�e�[�W�p�̃X�N���[��

	StageMng();
	~StageMng();
};

