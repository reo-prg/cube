#include <Scene/CharSelectScene.h>



CharSelectScene::CharSelectScene()
{
}


CharSelectScene::~CharSelectScene()
{
}

Base_unq CharSelectScene::Update(Base_unq scene)
{
	return std::move(scene);
}
