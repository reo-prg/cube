#include <Scene/SelectScene.h>



SelectScene::SelectScene()
{
}


SelectScene::~SelectScene()
{
}

Base_unq SelectScene::Update(Base_unq scene)
{
	return std::move(scene);
}
