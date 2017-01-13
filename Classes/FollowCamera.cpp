#include "FollowCamera.h"
USING_NS_CC;


FollowCamera * FollowCamera::createPerspective(Player * player, float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	auto ret = new (std::nothrow) FollowCamera();
	if (ret)
	{
		ret->initPerspective(player, fieldOfView, aspectRatio, nearPlane, farPlane);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool FollowCamera::initPerspective(Player * player, float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{

	if (!Camera::initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane))
	{
		return false;
	}
	m_pPlayer = player;
	// アップデート
	this->scheduleUpdate();
	return true;
}

void FollowCamera::update(float delta)
{
	//カメラ追従
	const float CAMETA_DISTANCE = 10.0f;
	//視点、参照点
	Vec3 eyepos, refpos;

	//プレイヤーの座標取得
	Vec3 playerpos = m_pPlayer->getPosition3D();
	//プレイヤーのY軸の角度取得
	float playerrot = m_pPlayer->getRotation3D().y;
	//ラジアン値に変換
	playerrot = CC_DEGREES_TO_RADIANS(playerrot);

	//自機の座標追従
	refpos = playerpos;

	//上から見る
	refpos += Vec3(0, 4.0f, 0);
	//参照点からカメラ視点への差分
	Vec3 cameraV(0.0f, 0.0f, -CAMETA_DISTANCE);

	Mat4 rotmat;
	//角度を指定し回転行列作成
	Mat4::createRotationY(playerrot, &rotmat);
	//カメラ視点方向ベクトルを回転させる
	rotmat.transformVector(&cameraV);

	m_refposed = refpos;
	//カメラ座標計算
	eyepos = refpos + cameraV;
	eyepos = this->getPosition3D() + (eyepos - this->getPosition3D())*0.04;
	refpos = m_refposed + (refpos - m_refposed)*0.03;
	// カメラ座標の設定
	this->setPosition3D(eyepos);
	//　参照座標、上方向ベクトルの指定
	this->lookAt(refpos);
}
