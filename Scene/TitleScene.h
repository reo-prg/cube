#pragma once
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>
#include <Graphic/ImageMng.h>
#include <Scene/CharSelectScene.h>

#define RAD(ang)	(ang * 3.141592 / 180.0)
#define MES_SIZE_X	700

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	Base_unq Update(Base_unq scene);
private:
	int _keyAllOld;			// 1フレ前のCheckHitKeyAll
	int _theta;				// 角度
	bool _sceneMoveFlag;	// シーンを移行するかのフラグ
	int _mesPos_x;			// メッセージのX座標

	void Draw(void);
};

