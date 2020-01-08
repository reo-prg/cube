#pragma once
#include <map>
#include <common/Vector2.h>
#include <Graphic/ImageMng.h>

// オブジェクトの種類
enum class OBJ_TYPE
{
	PLAYER,
	BLOCK,
	MAX
};

// オブジェクトの状態
enum class OBJ_STATS
{
	LEFT,
	RIGHT,
	MAX
};

class object
{
public:
	object();
	virtual ~object();

	virtual void Update(void) = 0;
	void objDraw(void);

	void setImage(OBJ_STATS, int);		// 状態ごとの画像の設定
protected:
	Vector2Template<double> _pos;		// 座標
	double					_rad;		// 角度
	int						_zOrder;	// zオーダー
	OBJ_STATS				_stats;		// 現在の状態
private:
	std::map<OBJ_STATS,int> _image;		// 画像ID
};

