#include "CollisionNode.h"

USING_NS_CC;

// �f�o�b�O�\����ON/OFF�t���O�̎���
bool CollisionNode::s_DebugVisible = false;

//--------------------------------------------------------------
bool SphereNode::init()
{
	// ���N���X������
	// �f�o�b�O�\���p���f���̓ǂݍ���
	// ���f���͔��a1m�̃��[�|���ȋ����쐬���邱�ƁB
	if (!Obj3D::initWithFile("atari/hati.c3b"))
	{
		return false;
	}

	// update��L����
	this->scheduleUpdate();

	return true;
}

void SphereNode::update(float delta)
{
	// ���[���h���W�n�ł̓����蔻�苅���v�Z
	{
		// �v�Z�ς݃��[���h�s����擾
		Mat4 worldm = this->getNodeToWorldTransform();
		// ���f�����W�n�ł̒��S
		Vec3 crnter(0, 0, 0);
		// ���f�����W�n�ł̉E�[
		Vec3 right(1, 0, 0);

		// ���[���h���W�ɕϊ�
		worldm.transformPoint(&crnter);
		worldm.transformPoint(&right);

		// ���[���h���W�n�ł̒��S���W��ݒ�
		Sphere::crnter = crnter;
		// ���[���h���W�n�ł̔��a���v�Z
		Sphere::radius = crnter.distance(right);
	}
}

void SphereNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	// �f�o�b�O�\����ON�Ȃ�
	if (CollisionNode::GetDebugVisible())
	{
		// ���f����`��
		Obj3D::visit(renderer, parentTransform, parentFlags);
	}
}

void SphereNode::SetRadius(float radius)
{
	// ���f���͔��a1m�ō���Ă���̂ŁA
	// ���an���[�g���Ȃ�X�P�[�����On�{�ɂȂ�B
	this->setScaleX(radius);
	this->setScaleY(radius);
	this->setScaleZ(radius);
}

//--------------------------------------------------------------
bool CapsuleNode::init()
{
	// ���N���X������
	// �f�o�b�O�\���p���f���̓ǂݍ���
	// ���f���͔��a1m�̃��[�|���ȋ����쐬���邱�ƁB
	if (!Obj3D::initWithFile("atari/ball.c3b"))
	{
		return false;
	}

	// update��L����
	this->scheduleUpdate();

	return true;
}


void CapsuleNode::update(float delta)
{
	// ���[���h���W�n�ł̓����蔻��J�v�Z�����v�Z
	{
		// �v�Z�ς݃��[���h�s����擾
		Mat4 worldm = this->getNodeToWorldTransform();
		// ���f�����W�n�ł̒��S
		Vec3 crnter(0, 0, 0);
		// ���f�����W�n�ł̏�[
		Vec3 up(0, 1, 0);
		// ���f�����W�n�ł̉E�[
		Vec3 right(1, 0, 0);

		// ���[���h���W�ɕϊ�
		worldm.transformPoint(&crnter);
		worldm.transformPoint(&up);
		worldm.transformPoint(&right);

		// ���[���h���W�n�ł̎������W��ݒ�
		Capsule::segment.start = crnter;
		Capsule::segment.end = up;
		// ���[���h���W�n�ł̔��a���v�Z
		Capsule::radius = crnter.distance(right);
	}
}

void CapsuleNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	// �f�o�b�O�\����ON�Ȃ�
	if (CollisionNode::GetDebugVisible())
	{
		// ���f����`��
		Obj3D::visit(renderer, parentTransform, parentFlags);
	}
}


void CapsuleNode::SetRadius(float radius)
{
	// ���f���͔��a1m�ō���Ă���̂ŁA
	// ���an���[�g���Ȃ�X�P�[�����On�{�ɂȂ�B
	this->setScaleX(radius);
	this->setScaleZ(radius);
}

void CapsuleNode::SetLength(float length)
{
	// ���f���͎����̒���1m�ō���Ă���̂ŁA
	// ����n���[�g���Ȃ�X�P�[�����On�{�ɂȂ�B
	this->setScaleY(length);
}