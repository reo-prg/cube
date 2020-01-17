#pragma once
#include <map>
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>


#define PL_SPACE	80

class CharSelectScene :
	public BaseScene
{
public:
	CharSelectScene();
	~CharSelectScene();

	Base_unq Update(Base_unq scene);
private:
	int _charSelPos_x;					// キャラクターセレクトのオフセット
	int _cursorPos;						// カーソルの位置
	bool _charMoveFlag;					// キャラクターが動いているか

	std::map<int, int>	_keyOld;		// 1フレ前のキー
	
	void charMove(void);
	Base_unq charSelect(Base_unq);
	int keyUpdate(int);
};

