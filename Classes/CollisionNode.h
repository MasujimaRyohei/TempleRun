#pragma once

#include "Obj3D.h"
#include "Collision.h"

// �����蔻��m�[�h�Ǘ��N���X
class CollisionNode
{
protected:
	// �f�o�b�O�\����ON/OFF�t���O
	static bool s_DebugVisible;
public:
	// �f�o�b�O�\����ON/OFF��ݒ�
	static void SetDebugVisible(bool flag) { s_DebugVisible = flag; }
	// �f�o�b�O�\����ON/OFF���擾
	static bool GetDebugVisible(void) { return s_DebugVisible; }
};

// �����蔻�苅�m�[�h
class SphereNode : public Sphere, public Obj3D
{
public:
	CREATE_FUNC(SphereNode);
	// ������
	bool init();
	// ���t���[���X�V
	void update(float delta) override;
	// �`��
	void visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags);
	// ���[�J�����a��ݒ�
	void SetRadius(float radius);
};

// �����蔻��J�v�Z���m�[�h
class CapsuleNode : public Capsule, public Obj3D
{
public:
	CREATE_FUNC(CapsuleNode);
	// ������
	bool init();
	// ���t���[���X�V
	void update(float delta) override;
	// �`��
	void visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags);
	// ���[�J�����a��ݒ�
	void SetRadius(float radius);
	// ���[�J����������ݒ�
	void SetLength(float length);
};