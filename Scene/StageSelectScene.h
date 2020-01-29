#pragma once
#include <map>
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>
#include <RankMng.h>

#define STAGE_SPACE		60			// �X�e�[�W�Ԃ̊Ԋu
#define STAGE_SIZE_X	128			// �X�e�[�W��X�����̑傫��
#define STAGE_SIZE_Y	96			// �X�e�[�W��Y�����̑傫��
#define STAGE_COUNT		8			// �X�e�[�W�̐�
#define STAGE_OFFSET	(SceneMngIns.ScreenCenter.x - (STAGE_SIZE_X + STAGE_SPACE) * 3 / 2)		// ���̃X�e�[�W�B�̃I�t�Z�b�g


class StageSelectScene :
	public BaseScene
{
public:
	StageSelectScene();
	~StageSelectScene();

	Base_unq Update(Base_unq scene);	// �X�V
private:
	int _stagePos_x;					// �X�e�[�W�̍��W
	int _cursor;						// �J�[�\��
	bool _sceneMoveFlag;				// ��ʂ�ς��邩�ǂ���
	Base_unq _tmpScene;					// �ꎞ�I�Ɏ��̃V�[����ێ�
	int _stageViewScreen;				// �X�e�[�W���g�債�����̂�`�悷��X�N���[��

	std::map<int, int> _keyOld;			// 1�t���O�̃L�[���

	Base_unq stageMove(Base_unq scene);			// �X�e�[�W�������Ă���Ԃ̏���
	Base_unq stageSelect(Base_unq scene);		// �X�e�[�W��I�Ԏ��̏���

	Base_unq (StageSelectScene::*_stageSel)(Base_unq);	// ��2�̊֐��|�C���^

	int keyUpdate(int key);				// �L�[��Ԃ̊Ǘ�
	void Draw();						// �`��
};

