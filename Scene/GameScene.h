#pragma once
#include <vector>
#include <Scene/BaseScene.h>
#include <Graphic/ImageMng.h>
#include <StageMng.h>
#include <Objects/object.h>
#include <Objects/player.h>

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	Base_unq Update(Base_unq scene);
private:
	friend class StageMng;
	static std::vector<std::shared_ptr<object>> _objList;
};

