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
	// �A�b�v�f�[�g
	this->scheduleUpdate();
	return true;
}

void FollowCamera::update(float delta)
{
	//�J�����Ǐ]
	const float CAMETA_DISTANCE = 10.0f;
	//���_�A�Q�Ɠ_
	Vec3 eyepos, refpos;

	//�v���C���[�̍��W�擾
	Vec3 playerpos = m_pPlayer->getPosition3D();
	//�v���C���[��Y���̊p�x�擾
	float playerrot = m_pPlayer->getRotation3D().y;
	//���W�A���l�ɕϊ�
	playerrot = CC_DEGREES_TO_RADIANS(playerrot);

	//���@�̍��W�Ǐ]
	refpos = playerpos;

	//�ォ�猩��
	refpos += Vec3(0, 4.0f, 0);
	//�Q�Ɠ_����J�������_�ւ̍���
	Vec3 cameraV(0.0f, 0.0f, -CAMETA_DISTANCE);

	Mat4 rotmat;
	//�p�x���w�肵��]�s��쐬
	Mat4::createRotationY(playerrot, &rotmat);
	//�J�������_�����x�N�g������]������
	rotmat.transformVector(&cameraV);

	m_refposed = refpos;
	//�J�������W�v�Z
	eyepos = refpos + cameraV;
	eyepos = this->getPosition3D() + (eyepos - this->getPosition3D())*0.04;
	refpos = m_refposed + (refpos - m_refposed)*0.03;
	// �J�������W�̐ݒ�
	this->setPosition3D(eyepos);
	//�@�Q�ƍ��W�A������x�N�g���̎w��
	this->lookAt(refpos);
}
