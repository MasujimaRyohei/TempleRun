#pragma once
#include"cocos2d.h"

// 追従カメラクラス
class RailCamera : public cocos2d::Camera
{
private:

	cocos2d::Vec3 m_PointStart;
	cocos2d::Vec3 m_PointEnd;
	cocos2d::Vec3 m_LookAt;
	float m_Offset;

public:
	// カメラを作成
	static RailCamera* create(cocos2d::Vec3 s, cocos2d::Vec3 e);
	// カメラを初期化
	bool init(cocos2d::Vec3 s, cocos2d::Vec3 e);
	// 毎フレーム更新
	void update(float delta) override;
	void Duration(cocos2d::Vec3 lookAt, float n = 1.0f);
};