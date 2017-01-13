#include "Collision.h"
USING_NS_CC;



bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB, cocos2d::Vec3* inter)
{
	float distance = Sphere::Distance3DSQ(sphereA.crnter, sphereB.crnter);
	float radius_sum = sphereA.radius + sphereB.radius;
	float radius_sumSQ = radius_sum*radius_sum;

	if (distance > radius_sumSQ)
	{
		return false;
	}

	if (inter)
	{
		Vec3 sub=sphereA.crnter-sphereB.crnter;
		Vec3 BtoInter = sub * sphereB.radius / (sphereA.radius + sphereB.radius);
		*inter = sphereB.crnter + BtoInter;
	}
	return true;
}

bool CheckSphere2Capsule(const Sphere &sphere, const Capsule &capsule, cocos2d::Vec3* inter)
{

	float distance = GetSqDistancePoint2Segment(sphere.crnter, capsule.segment);
	float radius = sphere.radius + capsule.radius;

	if (distance > radius*radius)	return false;

	if (inter)
	{
		Vec3 cpointB;
		ClosestPtPoint2Segment(sphere.crnter,capsule.segment,&cpointB);

		Vec3 sub = sphere.crnter - cpointB;
		Vec3 BtoInter = sub* capsule.radius / (sphere.radius + capsule.radius);
		*inter = cpointB + BtoInter;
		
	}
	return true;
}

bool CheckCapsule2Capsule(const Capsule & capsuleA, const Capsule & capsuleB,Vec3* inter)
{
	float distance = GetSqDistanceSegment2Segment(capsuleA.segment, capsuleB.segment);
	float radiusSum = capsuleA.radius + capsuleB.radius;
	float radiusSumSQ = radiusSum*radiusSum;

	if (distance >radiusSumSQ)	return false;
	
if (inter)
	{
		Vec3 cpointA, cpointB;
		ClosestPtSegment2Segment(capsuleA.segment, capsuleB.segment, &cpointA, &cpointB);
		Vec3 sub = cpointA - cpointB;
		Vec3 BtoInter = sub*capsuleB.radius / (capsuleA.radius + capsuleB.radius);
		*inter = cpointB + BtoInter;
}
	return true;
}

float GetSqDistancePoint2Segment(const Vec3& _point, const Segment& _segment)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vec3 SegmentSub;
	Vec3 SegmentPoint;
	Vec3 CP;

	// �����̎n�_����I�_�ւ̃x�N�g��
	SegmentSub = _segment.end - _segment.start;

	// �����̎n�_����_�ւ̃x�N�g��
	SegmentPoint = _point - _segment.start;
	if (SegmentSub.dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̎n�_���ŋߖT
		return SegmentPoint.dot(SegmentPoint);
	}

	// �_��������̏I�_�ւ̃x�N�g��
	SegmentPoint = _segment.end - _point;
	if (SegmentSub.dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̏I�_���ŋߖT
		return SegmentPoint.dot(SegmentPoint);
	}

	// ��L�̂ǂ���ɂ��Y�����Ȃ��ꍇ�A������ɗ��Ƃ����ˉe���ŋߖT
	// (�{���Ȃ�T�C���ŋ��߂邪�A�O�ς̑傫��/�����̃x�N�g���̑傫���ŋ��܂�)
	Vec3::cross(SegmentSub, SegmentPoint, &CP);

	return CP.dot(CP) / SegmentSub.dot(SegmentSub);
}

float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vec3 d0, d1, r;
	Vec3 c0, c1;	// ��̐�����̍Őڋߓ_
	Vec3 v;		// c1��c0�x�N�g��
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end - _segment0.start;	// ����0�̕����x�N�g��
	d1 = _segment1.end - _segment1.start; // ����1�̕����x�N�g��
	r = _segment0.start - _segment1.start; // ����1�̎n�_�������0�̎n�_�ւ̃x�N�g��
	a = d0.dot(d0);		// ����0�̋����̓��
	e = d1.dot(d1);		// ����1�̋����̓��
						//	b = d0.dot(d1);		// �œK���̈׌���Ɉړ�����
						//	c = d0.dot(r);		// �œK���̈׌���Ɉړ�����
						//	f = d1.dot(r);		// �œK���̈׌���Ɉړ�����

						// ���Âꂩ�̐����̒�����0���ǂ����`�F�b�N
	if (a <= epsilon && e <= epsilon)
	{// ��������0
		v = _segment0.start - _segment1.start;

		return v.dot(v);
	}

	if (a <= epsilon)
	{// ����0������0
		return GetSqDistancePoint2Segment(_segment0.start, _segment1);
	}

	if (e <= epsilon)
	{// ����1������0
		return GetSqDistancePoint2Segment(_segment1.start, _segment0);
	}

	b = d0.dot(d1);
	f = d1.dot(r);
	c = d0.dot(r);

	denom = a * e - b * b;	// ��ɔ�
							// ���������s�łȂ��ꍇ�A����0��̒���1�ɑ΂���ŋߐړ_���v�Z�A������
							// ����0��ɃN�����v�B�����łȂ��ꍇ�͔C�ӂ�s��I��
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// ����1��̍Őڋߓ_���v�Z
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	c0 = s * d0 + _segment0.start;
	c1 = t * d1 + _segment1.start;
	v = c0 - c1;

	return v.dot(v);
}

// �ŏ��l�ƍő�l�̊ԂɃN�����v����
inline float Clamp(float _x, float _min, float _max)
{
	return std::min(std::max(_x, _min), _max);
}

float Sphere::VectorLength(const cocos2d::Vec3 & v)
{
	return sqrtf(v.x*v.x + v.y*v.y + v.z + v.z);
}

float Sphere::Distance3D(const cocos2d::Vec3 & p1, const cocos2d::Vec3 & p2)
{	
	Vec3 sub = p1 - p2;
	return VectorLength(sub);
}

float Sphere::VectorLengthSQ(const cocos2d::Vec3 & v)
{
	return v.x*v.x + v.y*v.y + v.z + v.z;
}

float Sphere::Distance3DSQ(const cocos2d::Vec3 & p1, const cocos2d::Vec3 & p2)
{
	Vec3 sub = p1 - p2;
	return VectorLength(sub);
}

//--------------------------------------------------------------------------------------------
// ���@�� : �_�Ɛ����̍ŋߐړ_���v�Z
// ���@�� : _point	�_
//			_segment	����
//			_closest	�ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Segment(const Vec3& _point, const Segment& _segment, Vec3* _closest)
{
	Vec3 segv;
	Vec3 s2p;
	float t;

	segv = _segment.end - _segment.start;
	s2p = _point - _segment.start;
	t = segv.dot(s2p) / segv.dot(segv);

	// �����̊O���ɂ���ꍇ�At���Őڋߓ_�܂ŃN�����v
	t = Clamp(t, 0, 1);

	// �N�����v����Ă���t����̎ˉe����Ă���ʒu���v�Z
	*_closest = t * segv + _segment.start;
}

//--------------------------------------------------------------------------------------------
// ���@�� : �����Ɛ����̍ŋߐړ_���v�Z
// ���@�� : _segment0	����0
//			_segment1	����1
//			_closest0	����0��̍ŋߐړ_(���ʏo�͗p�j
//			_closest1	����1��̍ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtSegment2Segment(const Segment& _segment0, const Segment& _segment1, Vec3* _closest0, Vec3* _closest1)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vec3 d0, d1, r;
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end - _segment0.start;		// ����0�̕����x�N�g��
	d1 = _segment1.end - _segment1.start;		// ����1�̕����x�N�g��
	r = _segment0.start - _segment1.start;	// ����1�̎n�_�������0�̎n�_�ւ̃x�N�g��
	a = d0.dot(d0);	// ����0�̋����̓��
	e = d1.dot(d1);	// ����1�̋����̓��
					//	b = d0.dot(d1);	// �œK���̈׌���Ɉړ�����
					//	c = d0.dot(r);	// �œK���̈׌���Ɉړ�����
					//	f = d1.dot(r);	// �œK���̈׌���Ɉړ�����

					// ���Âꂩ�̐����̒�����0���ǂ����`�F�b�N
	if (a <= epsilon && e <= epsilon)
	{// ��������0
		*_closest0 = _segment0.start;
		*_closest1 = _segment1.start;
		return;
	}

	if (a <= epsilon)
	{// ����0������0
		*_closest0 = _segment0.start;
		ClosestPtPoint2Segment(_segment0.start, _segment1, _closest1);
	}

	if (e <= epsilon)
	{// ����1������0
		*_closest1 = _segment1.start;
		ClosestPtPoint2Segment(_segment1.start, _segment0, _closest0);
	}

	b = d0.dot(d1);
	f = d1.dot(r);
	c = d0.dot(r);

	denom = a * e - b * b;	// ��ɔ�
							// ���������s�łȂ��ꍇ�A����0��̒���1�ɑ΂���ŋߐړ_���v�Z�A������
							// ����0��ɃN�����v�B�����łȂ��ꍇ�͔C�ӂ�s��I��
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// ����1��̍Őڋߓ_���v�Z
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	*_closest0 = s * d0 + _segment0.start;
	*_closest1 = t * d1 + _segment1.start;
}
