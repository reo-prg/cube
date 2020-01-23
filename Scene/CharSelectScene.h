#pragma once
#include <map>
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>
#include <Scene/StageSelectScene.h>

#define PL_SPACE	80
#define PL_POS_X	((PL_SPACE * 7 + CubeSize) / 2)

class CharSelectScene :
	public BaseScene
{
public:
	CharSelectScene();
	~CharSelectScene();

	Base_unq Update(Base_unq scene);
private:
	int _charSelPos_x;					// キャラクターセレクトのオフセット
	int _cursor;						// カーソルの位置
	bool _sceneMoveFlag;				// 場面を変えるかどうか
	Base_unq _tmpScene;					// 一時的に次のシーンを保持

	std::map<int, int>	_keyOld;		// 1フレ前のキー状態
	
	Base_unq charMove(Base_unq);
	Base_unq charSelect(Base_unq);

	Base_unq (CharSelectScene::*_charSel)(Base_unq);

	int keyUpdate(int);
	void Draw(void);
};

