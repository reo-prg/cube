#pragma once
#include <map>
#include <common/Vector2.h>
#include <Graphic/ImageMng.h>


// オブジェクトの種類
enum class OBJ_TYPE
{
	PLAYER,
	CUBE_LOCK,
	CUBE_FALL,
	MAX
};

// オブジェクトの状態
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

	void setImage(OBJ_STATS, int);		// 状態ごとの画像の設定
protected:
	Vector2Template<double> _pos;		// 座標
	double					_rad;		// 角度
	int						_zOrder;	// zオーダー
	OBJ_STATS				_stats;		// 現在の状態
	Vector2Template<int>	_size;		// サイズ
	OBJ_TYPE				_type;		// オブジェクトの種類
private:
	std::map<OBJ_STATS,int> _image;		// 画像ID
};

