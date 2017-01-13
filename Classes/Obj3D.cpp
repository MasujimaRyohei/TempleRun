#include "Obj3D.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Obj3D* Obj3D::create(const std::string & modelPath)
{
	//ファイル名　4文字以上でなければエラー
	CCASSERT(modelPath.length() >= 4, "invalid filename for Sprite3D");

	//メモリ確保
	auto obj3d = new (std::nothrow) Obj3D();
	//初期化
	if (obj3d && obj3d->initWithFile(modelPath))
	{
		// AABBからコンテンツサイズ取得
		obj3d->_contentSize = obj3d->getBoundingBox().size;
		// 自動リリースとして登録
		obj3d->autorelease();

		return obj3d;
	}
}

bool Obj3D::initWithFile(const std::string& path)
{
	// 基底クラス初期化
	if (!Sprite3D::init())
	{
		return false;
	}
	m_spr3D = Sprite3D::create(path);
	this->addChild(m_spr3D);
	m_spr3D->setCameraMask((unsigned short)CameraFlag::USER1);
	m_spr3D->setLightMask((unsigned int)LightFlag::LIGHT0);
	return true;
}

const Mat4 & Obj3D::getNodeToParentTransform() const
{
	Mat4 scalem;
	Mat4::createScale(_scaleX, _scaleY, _scaleZ, &scalem);


	Mat4 rotm_z;
	Mat4::createRotationZ(CC_DEGREES_TO_RADIANS(_rotationZ_X), &rotm_z);

	Mat4 rotm_x;
	Mat4::createRotationX(CC_DEGREES_TO_RADIANS(_rotationX), &rotm_x);

	Mat4 rotm_y;
	Mat4::createRotationY(CC_DEGREES_TO_RADIANS(_rotationY), &rotm_y);

	Mat4 rotm = Mat4::IDENTITY;
	rotm *= rotm_y;
	rotm *= rotm_x;
	rotm *= rotm_z;


	Mat4 transm;
	Mat4::createTranslation(_position.x, _position.y, _positionZ, &transm);

	_transform = Mat4::IDENTITY;
	_transform *= transm;
	_transform *= rotm;
	_transform *= scalem;

	return _transform;
}

void Obj3D::setLightMask(unsigned int mask)
{
	m_spr3D->setLightMask(mask);
}

void Obj3D::playAnimation(const std::string & filename, bool isLoop)
{
	if (isLoop)
	{
		Animation3D* animation = Animation3D::create(filename, "mixamo.com");
		animate = Animate3D::create(animation);
		m_spr3D->runAction(RepeatForever::create(animate));
	}
	else
	{
		Animation3D* animation = Animation3D::create(filename, "mixamo.com");
		animate = Animate3D::create(animation);
		m_spr3D->runAction(animate);
	}
}

void Obj3D::stopAnimation()
{
	m_spr3D->stopAllActions();
}


