#pragma once


// ���C���[
enum class LAYER
{
	BG,				// �w�i
	CHAR,			// �L�����N�^�[
	UI,				// UI
	EX,				// ����
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);

LAYER operator++(LAYER& key);
LAYER operator*(LAYER key);