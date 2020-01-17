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
	int _charSelPos_x;					// �L�����N�^�[�Z���N�g�̃I�t�Z�b�g
	int _cursorPos;						// �J�[�\���̈ʒu
	bool _charMoveFlag;					// �L�����N�^�[�������Ă��邩

	std::map<int, int>	_keyOld;		// 1�t���O�̃L�[
	
	void charMove(void);
	Base_unq charSelect(Base_unq);
	int keyUpdate(int);
};

