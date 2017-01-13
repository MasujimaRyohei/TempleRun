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
	// �A�b�v�f�[�g
	this->scheduleUpdate();


	//���[���n�_
	m_PointStart = Vec3(s);
	//�I�_
	m_PointEnd = Vec3(e);
	//���[�����̃I�t�Z�b�g�͂O����J�n
	m_Offset = 0.0f;

	this->setPosition3D(m_PointStart);
	this->lookAt(m_PointEnd + (m_PointEnd - m_PointStart));
	return true;
}

void RailCamera::update(float delta)
{
	//�S�[��
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
	//���[�����̃I�t�Z�b�g��i�߂�
	m_Offset += 1.f / (60.0f * n);
	//�I�_�Ǝn�_�̍���
	Vec3 sub = m_PointEnd - m_PointStart;

	//�����̑S�̂̓��A���ݐi��ł���Ƃ���܂�
	Vec3 offsetpos = sub*m_Offset;

	//�n�_�ɐi�񂾕��𑫂������̂��A���ݍ��W
	Vec3 pos = m_PointStart + offsetpos;


	//�ړ���̃J�������W�𔽉f
	this->setPosition3D(pos);
	//�J�����Q�Ɠ_���W
	this->lookAt(m_LookAt);
	//this->lookAt(m_PointEnd + (m_PointEnd - m_PointStart));
}
