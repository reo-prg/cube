#include <Scene/GameScene.h>



GameScene::GameScene()
{
	ImageMngIns.getImage("image/char.png", "player", 64, 32, 2, 8);

	_objList.emplace_back(new player({ 800.0,704.0 }, 0.0, { 32,32 }));
}


GameScene::~GameScene()
{
}

Base_unq GameScene::Update(Base_unq scene)
{
	for (auto data : _objList)
	{
		data->Update();
	}
	
	for (auto data : _objList)
	{
		data->objDraw();
	}

	StageMngIns.Update();

	return std::move(scene);
}
