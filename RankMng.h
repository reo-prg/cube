#pragma once
#include <DxLib.h>
#include <_debug/_DebugConOut.h>
#include <common/Vector2.h>
#include <Graphic/ImageMng.h>

#define RankMngIns RankMng::getInstance()

#define STAGE_COUNT	8		// �X�e�[�W�̐�
#define RANK_COUNT	3		// �����N�̐�

#define MIN			60000	// �~���b���番�ւ̕ϊ��p
#define SEC			1000	// �~���b����b�ւ̕ϊ��p

#define NUM_SIZE_X	32		// �ԍ��摜��X�̑傫��
#define RANK_OFFSET	20		// �����N�摜�̃I�t�Z�b�g
#define RANK_DUR	64		// �����N�Ԃ̊Ԋu
#define TIME_MAX	5999999	// ���Ԃ̍ő�l

class RankMng
{
public:

	static RankMng& getInstance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new RankMng();
		}
		return *sInstance;
	}

	static void Destroy(void)
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	void RankInit(void);	// �����L���O�̓ǂݎ��

	int getClearTime(int stage, int rank);	// �N���A�^�C���̎擾
	int getRankScreen(int stage);			// �����L���O�̃X�N���[�����擾
	int checkRank(int stage, int clearTime);			// �N���A�^�C���������L���O�ɓ����Ă���̂����`�F�b�N

private:
	static RankMng* sInstance;

	int _clearTimeRank[STAGE_COUNT][RANK_COUNT];	// �N���A�^�C���̊i�[
	int _rankScreen;								// �����N���`�悳��Ă���X�N���[��

	void saveClearTime(void);

	RankMng();
	~RankMng();
};

