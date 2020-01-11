#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <common/Vector2.h>
#include <Graphic/ImageMng.h>
#include <Scene/BaseScene.h>
#include <Scene/TitleScene.h>
#include <Scene/SelectScene.h>
#include <Scene/GameScene.h>

#define SceneMngIns SceneMng::getInstance()

class SceneMng
{
public:
	// Singleton
	static SceneMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
		return *sInstance;
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void Run(void);

	const Vector2Template<int> ScreenSize;
	const Vector2Template<int> ScreenCenter;
private:
	static SceneMng* sInstance;
	static int joypad;

	Base_unq _runScene;				// åªç›ÇÃÉVÅ[Éì

	bool SystemInit(void);

	SceneMng();
	~SceneMng();
};

