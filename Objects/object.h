#pragma once
#include <map> 
#include <common/Vector2.h>
#include <Graphic/ImageMng.h>
#include <Objects/CHECK_DIR.h>


// �I�u�W�F�N�g�̎��
enum class OBJ_TYPE
{
	PLAYER,
	CUBE_LOCK,
	CUBE_FALL,
	MAX
};

// �I�u�W�F�N�g�̏��
enum class OBJ_STATS
{
	LEFT,
	RIGHT,
	NORMAL,
	MAX
};

class object
{
public:
	object();
	virtual ~object();

	virtual void Update(void);
	void objDraw(void);

	void setImage(OBJ_STATS, int);								// ��Ԃ��Ƃ̉摜�̐ݒ�
	void setGrip(bool);											// _grip�̕ύX
	void setPos(Vector2Template<double> pos);					// ���W�̐ݒ�
	void setState(OBJ_STATS stats);								// ��Ԃ̐ݒ�

	OBJ_STATS getStats(void);
	OBJ_TYPE getType(void);
	Vector2Template<double> getPos(void);
	Vector2Template<int>	getSize(void);
protected:
	Vector2Template<double> _pos;		// ���W
	double					_rad;		// �p�x
	int						_zOrder;	// z�I�[�_�[
	OBJ_STATS				_stats;		// ���݂̏��
	Vector2Template<int>	_size;		// �T�C�Y
	OBJ_TYPE				_type;		// �I�u�W�F�N�g�̎��
	bool					_grip;		// �͂�ł��邩
private:
	std::map<OBJ_STATS,int> _image;												// �摜ID
};

