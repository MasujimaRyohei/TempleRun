#include "RailCamera.h"
USING_NS_CC;


RailCamera * RailCamera::create(Vec3 s, Vec3 e)
{
	auto ret = new (std::nothrow) RailCamera();
	if (ret)
	{
		ret->init(s, e);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool RailCamera::init(Vec3 s, Vec3 e)
{
	Size winsize = Director::getInstance()->getWinSize();
	if (!Camera::initPerspective(60.0, winsize.width / winsize.height, 0.1f, 1000.0f))
	{
		return false;
	}
	this->setCameraFlag(CameraFlag::USER1);
	// アップデート
	this->scheduleUpdate();


	//レール始点
	m_PointStart = Vec3(s);
	//終点
	m_PointEnd = Vec3(e);
	//レール内のオフセットは０から開始
	m_Offset = 0.0f;

	this->setPosition3D(m_PointStart);
	this->lookAt(m_PointEnd + (m_PointEnd - m_PointStart));
	return true;
}

void RailCamera::update(float delta)
{
	//ゴール
	if (m_Offset >= 1.0f)
	{
		this->setPosition3D(m_PointEnd);
		this->lookAt(m_PointEnd + (m_PointEnd - m_PointStart));
		return;
	}
	static float x = 0;
	static float y = 0;
	static float z = 0;

	Duration(Vec3(x, y, z));
}

void RailCamera::Duration(Vec3 lookAt, float n)
{
	m_LookAt = lookAt;
	//レール内のオフセットを進める
	m_Offset += 1.f / (60.0f * n);
	//終点と始点の差分
	Vec3 sub = m_PointEnd - m_PointStart;

	//差分の全体の内、現在進んでいるところまで
	Vec3 offsetpos = sub*m_Offset;

	//始点に進んだ分を足したものが、現在座標
	Vec3 pos = m_PointStart + offsetpos;


	//移動後のカメラ座標を反映
	this->setPosition3D(pos);
	//カメラ参照点座標
	this->lookAt(m_LookAt);
	//this->lookAt(m_PointEnd + (m_PointEnd - m_PointStart));
}
