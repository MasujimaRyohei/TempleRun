#include "Enemy.h"
#include "ui/CocosGUI.h"
#include <random>

USING_NS_CC;



Enemy* Enemy::create()
{
	//�������m��
	auto enemy = new (std::nothrow) Enemy();
	//������
	if (enemy && enemy->init())
	{
		// AABB����R���e���c�T�C�Y�擾
		enemy->_contentSize = enemy->getBoundingBox().size;
		// ���������[�X�Ƃ��ēo�^
		enemy->autorelease();

		return enemy;
	}
}



bool Enemy::init()
{
	if (!Obj3D::init())
	{
		return false;
	}
	_timer = 60;
	int rand = random(0, 2);
	//Vec3 Pos = Vec3(rand, 0, rand);
	
	Vec3 Pos = Vec3(linePosition[rand], 0, 0);

	Vec3 Rote = Vec3(0, 0, 0);
	float Scale = 0.6f;

	// ���f���쐬�֐�
	createObject(Pos, Rote, Scale);
	_pBody->playAnimation("body/running_inPlace.c3b", true);




	/*--------------------------------------------------------------------*/

	/*--------------------------------------------------------------------*/

	// �A�b�v�f�[�g
	this->scheduleUpdate();
	return true;
}

/*------------------------------------------------------------------
*
*	�A�b�v�f�[�g
*
-------------------------------------------------------------------*/
void Enemy::update(float dt)
{
	Vec3 pos = getPosition3D();
	pos.z += 0.1f;
	setPosition3D(Vec3(pos.x, pos.y,pos.z));
	////�@����I�ɐi�s������������
	////�@�J�E���g�_�E��
	//_timer--;
	//if (_timer < 0)
	//{
	//	//�@0�ɂȂ�����
	//	_timer = 60;
	//	//�@�ڕW�p�x��ύX
	//	float rnd = (float)rand() / RAND_MAX - 0.5;
	//	rnd *= 180.f;
	//	//�@���̊p�x�{�[90�x���V���Ȑi�s����
	//	_distAngle += rnd;
	//}

	////�@�L�����̊p�x����
	//Vec3 rot = this->getRotation3D();
	////�@�L�����̕��ʊp�ɁA�ڕW�p�x����
	////rot.y = _distAngle;
	//float angle_diff = _distAngle - rot.y;
	//rot.y += angle_diff*0.01f;
	//this->setRotation3D(rot);

	////�L�����̌����Ă�������ɐi��
	////�ړ��x�N�g��
	//Vec3 moveV(0, 0, 0.05f);

	////�@�v���C���[��Y�����p�x
	//float playerrot = this->getRotation3D().y;
	////�@���W�A���ɕϊ�
	//playerrot = CC_DEGREES_TO_RADIANS(playerrot);

	//Mat4 rotmat;
	////�@�p�x�w��ŉ�]�s����쐬
	//Mat4::createRotationY(playerrot, &rotmat);
	////�@�͈ړ��x�N�g������]������
	//rotmat.transformVector(&moveV);
	////�@�����̌��ݍ��W����]������
	//Vec3 pos = this->getPosition3D();
	////�@�ړ�
	//pos += moveV;
	////�@���@�ɃZ�b�g
	//this->setPosition3D(pos);
}

/*------------------------------------------------------------------
*	���f���쐬
*	�����F�@�|�W�V�����A�p�x�A�X�P�[��
*
-------------------------------------------------------------------*/
void Enemy::createObject(Vec3 pos, Vec3 rote, float scale)
{
	// ���f�����ߍ���
	_pBody = Obj3D::create("body/body.c3b");

	_pBody->setLightMask(0);

	// �X�P�[���ύX
	//_pBody->setScaleX(scale);
	//_pBody->setScaleY(scale);
	//_pBody->setScaleZ(scale);
	_pBody->setScale(scale);

	// ��]
	_pBody->setRotation3D(Vec3(rote));

	// �|�W�V����
	_pBody->setPosition3D(Vec3(pos));

	// ���[�U�J�����P�Ɋ���U��
	_pBody->setCameraMask((unsigned short)CameraFlag::USER1);

	// ���f���쐬
	this->addChild(_pBody);


	//�U�������蔻��쐬
	_pCollisionNodeBody = SphereNode::create();
	//���a�ݒ�
	_pCollisionNodeBody->SetRadius(0.2f);
	//�����ݒ�
	_pCollisionNodeBody->setPosition3D(pos);
	//���������ʂɂȂ�
	this->addChild(_pCollisionNodeBody);

}


