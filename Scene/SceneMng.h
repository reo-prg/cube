#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <common/Vector2.h>
#include <Graphic/ImageMng.h>
#include <Scene/BaseScene.h>
#include <Scene/TitleScene.h>
#include <Scene/CharSelectScene.h>
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

	int GetPad(void)const;
	int GetPadOld(void)const;
	Vector2Template<int> GetStick(void)const;
	Vector2Template<int> GetStickOld(void)const;

	void StartVib(int pad, int power, int time)const;

	const Vector2Template<int> ScreenSize;
	const Vector2Template<int> ScreenCenter;
private:
	static SceneMng* sInstance;
	int _padInput;
	int _padInputOld;
	Vector2Template<int> _stick;
	Vector2Template<int> _stickOld;

	Base_unq _runScene;				// åªç›ÇÃÉVÅ[Éì

	bool SystemInit(void);
	void UpdatePad(void);

	SceneMng();
	~SceneMng();
};

