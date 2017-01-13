#pragma once
#include"cocos2d.h"

// �Ǐ]�J�����N���X
class RailCamera : public cocos2d::Camera
{
private:

	cocos2d::Vec3 m_PointStart;
	cocos2d::Vec3 m_PointEnd;
	cocos2d::Vec3 m_LookAt;
	float m_Offset;

public:
	// �J�������쐬
	static RailCamera* create(cocos2d::Vec3 s, cocos2d::Vec3 e);
	// �J������������
	bool init(cocos2d::Vec3 s, cocos2d::Vec3 e);
	// ���t���[���X�V
	void update(float delta) override;
	void Duration(cocos2d::Vec3 lookAt, float n = 1.0f);
};