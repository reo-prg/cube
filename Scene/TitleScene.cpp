#include <Scene/TitleScene.h>



TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

Base_unq TitleScene::Update(Base_unq scene)
{
	return std::move(scene);
}
