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
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	Vec3 SegmentSub;
	Vec3 SegmentPoint;
	Vec3 CP;

	// 線分の始点から終点へのベクトル
	SegmentSub = _segment.end - _segment.start;

	// 線分の始点から点へのベクトル
	SegmentPoint = _point - _segment.start;
	if (SegmentSub.dot(SegmentPoint) < epsilon)
	{// ２ベクトルの内積が負なら、線分の始点が最近傍
		return SegmentPoint.dot(SegmentPoint);
	}

	// 点から線分の終点へのベクトル
	SegmentPoint = _segment.end - _point;
	if (SegmentSub.dot(SegmentPoint) < epsilon)
	{// ２ベクトルの内積が負なら、線分の終点が最近傍
		return SegmentPoint.dot(SegmentPoint);
	}

	// 上記のどちらにも該当しない場合、線分上に落とした射影が最近傍
	// (本来ならサインで求めるが、外積の大きさ/線分のベクトルの大きさで求まる)
	Vec3::cross(SegmentSub, SegmentPoint, &CP);

	return CP.dot(CP) / SegmentSub.dot(SegmentSub);
}

float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	Vec3 d0, d1, r;
	Vec3 c0, c1;	// 二つの線分上の最接近点
	Vec3 v;		// c1→c0ベクトル
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end - _segment0.start;	// 線分0の方向ベクトル
	d1 = _segment1.end - _segment1.start; // 線分1の方向ベクトル
	r = _segment0.start - _segment1.start; // 線分1の始点から線分0の始点へのベクトル
	a = d0.dot(d0);		// 線分0の距離の二乗
	e = d1.dot(d1);		// 線分1の距離の二乗
						//	b = d0.dot(d1);		// 最適化の為後方に移動した
						//	c = d0.dot(r);		// 最適化の為後方に移動した
						//	f = d1.dot(r);		// 最適化の為後方に移動した

						// いづれかの線分の長さが0かどうかチェック
	if (a <= epsilon && e <= epsilon)
	{// 両方長さ0
		v = _segment0.start - _segment1.start;

		return v.dot(v);
	}

	if (a <= epsilon)
	{// 線分0が長さ0
		return GetSqDistancePoint2Segment(_segment0.start, _segment1);
	}

	if (e <= epsilon)
	{// 線分1が長さ0
		return GetSqDistancePoint2Segment(_segment1.start, _segment0);
	}

	b = d0.dot(d1);
	f = d1.dot(r);
	c = d0.dot(r);

	denom = a * e - b * b;	// 常に非負
							// 線分が平行でない場合、直線0上の直線1に対する最近接点を計算、そして
							// 線分0上にクランプ。そうでない場合は任意のsを選択
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// 直線1上の最接近点を計算
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

// 最小値と最大値の間にクランプする
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
// 説　明 : 点と線分の最近接点を計算
// 引　数 : _point	点
//			_segment	線分
//			_closest	最近接点(結果出力用）
// 戻り値 : なし
// メ　モ : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Segment(const Vec3& _point, const Segment& _segment, Vec3* _closest)
{
	Vec3 segv;
	Vec3 s2p;
	float t;

	segv = _segment.end - _segment.start;
	s2p = _point - _segment.start;
	t = segv.dot(s2p) / segv.dot(segv);

	// 線分の外側にある場合、tを最接近点までクランプ
	t = Clamp(t, 0, 1);

	// クランプされているtからの射影されている位置を計算
	*_closest = t * segv + _segment.start;
}

//--------------------------------------------------------------------------------------------
// 説　明 : 線分と線分の最近接点を計算
// 引　数 : _segment0	線分0
//			_segment1	線分1
//			_closest0	線分0上の最近接点(結果出力用）
//			_closest1	線分1上の最近接点(結果出力用）
// 戻り値 : なし
// メ　モ : 
//--------------------------------------------------------------------------------------------
void ClosestPtSegment2Segment(const Segment& _segment0, const Segment& _segment1, Vec3* _closest0, Vec3* _closest1)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	Vec3 d0, d1, r;
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end - _segment0.start;		// 線分0の方向ベクトル
	d1 = _segment1.end - _segment1.start;		// 線分1の方向ベクトル
	r = _segment0.start - _segment1.start;	// 線分1の始点から線分0の始点へのベクトル
	a = d0.dot(d0);	// 線分0の距離の二乗
	e = d1.dot(d1);	// 線分1の距離の二乗
					//	b = d0.dot(d1);	// 最適化の為後方に移動した
					//	c = d0.dot(r);	// 最適化の為後方に移動した
					//	f = d1.dot(r);	// 最適化の為後方に移動した

					// いづれかの線分の長さが0かどうかチェック
	if (a <= epsilon && e <= epsilon)
	{// 両方長さ0
		*_closest0 = _segment0.start;
		*_closest1 = _segment1.start;
		return;
	}

	if (a <= epsilon)
	{// 線分0が長さ0
		*_closest0 = _segment0.start;
		ClosestPtPoint2Segment(_segment0.start, _segment1, _closest1);
	}

	if (e <= epsilon)
	{// 線分1が長さ0
		*_closest1 = _segment1.start;
		ClosestPtPoint2Segment(_segment1.start, _segment0, _closest0);
	}

	b = d0.dot(d1);
	f = d1.dot(r);
	c = d0.dot(r);

	denom = a * e - b * b;	// 常に非負
							// 線分が平行でない場合、直線0上の直線1に対する最近接点を計算、そして
							// 線分0上にクランプ。そうでない場合は任意のsを選択
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// 直線1上の最接近点を計算
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
