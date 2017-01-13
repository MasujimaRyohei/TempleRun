#pragma once

#include<cocos2d.h>



class Sphere
{
public:
	cocos2d::Vec3 crnter;
	float radius;
	Sphere() { radius = 1.0f; }
	static float VectorLength(const cocos2d::Vec3&v);
	static float Distance3D(const cocos2d::Vec3&p1, const cocos2d::Vec3&p2);

	static float VectorLengthSQ(const cocos2d::Vec3&v);
	static float Distance3DSQ(const cocos2d::Vec3&p1, const cocos2d::Vec3&p2);
};
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB,cocos2d::Vec3* inter=nullptr);

class Segment
{
public:
	cocos2d::Vec3 start;
	cocos2d::Vec3 end;
};

class Capsule
{
public:
	Segment segment;
	float radius;
	Capsule()
	{
		segment.start = cocos2d::Vec3(0, 0, 0);
		segment.end = cocos2d::Vec3(0, 1, 0);
		radius = 1.0f;
	};
};

bool CheckSphere2Capsule(const Sphere&sphere, const Capsule&capsule,cocos2d::Vec3* inter=nullptr);
bool CheckCapsule2Capsule(const Capsule&capsuleA, const Capsule&capsuleB,cocos2d::Vec3* inter=nullptr);
float GetSqDistancePoint2Segment(const cocos2d::Vec3& _point, const Segment& _segment);
float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment);
inline float Clamp(float _x, float _min, float _max);

void ClosestPtPoint2Segment(const cocos2d::Vec3& _point, const Segment& _segment, cocos2d::Vec3* _closest);
void ClosestPtSegment2Segment(const Segment& _segment0, const Segment& _segment1, cocos2d::Vec3* _closest0, cocos2d::Vec3* _closest1);