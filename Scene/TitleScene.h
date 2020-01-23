#pragma once
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>
#include <Graphic/ImageMng.h>
#include <Scene/CharSelectScene.h>

#define RAD(ang)	(ang * 3.141592 / 180.0)	// ���W�A���ϊ�
#define MES_SIZE_X	700							// ���b�Z�[�W�̑傫��

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	Base_unq Update(Base_unq scene);	// �X�V
private:
	int _keyAllOld;			// 1�t���O��CheckHitKeyAll
	int _theta;				// �p�x
	bool _sceneMoveFlag;	// �V�[�����ڍs���邩�̃t���O
	bool _mesMoveFlag;		// ���b�Z�[�W�������Ă��邩�̃t���O
	int _mesPos_x;			// ���b�Z�[�W��X���W

	Base_unq mesMove(Base_unq scene);	// ���b�Z�[�W�𓮂���
	void Draw(void);					// �`��
};