#pragma once
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>
#include <Graphic/ImageMng.h>
#include <Scene/CharSelectScene.h>

#define RAD(ang)	(ang * 3.141592 / 180.0)

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	Base_unq Update(Base_unq scene);
private:
	int _keyAllOld;			// 1ƒtƒŒ‘O‚ÌCheckHitKeyAll
	int _theta;				// Šp“x
};

