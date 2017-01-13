#include "CollisionNode.h"

USING_NS_CC;

// デバッグ表示のON/OFFフラグの実体
bool CollisionNode::s_DebugVisible = false;

//--------------------------------------------------------------
bool SphereNode::init()
{
	// 基底クラス初期化
	// デバッグ表示用モデルの読み込み
	// モデルは半径1mのローポリな球を作成すること。
	if (!Obj3D::initWithFile("atari/hati.c3b"))
	{
		return false;
	}

	// updateを有効化
	this->scheduleUpdate();

	return true;
}

void SphereNode::update(float delta)
{
	// ワールド座標系での当たり判定球を計算
	{
		// 計算済みワールド行列を取得
		Mat4 worldm = this->getNodeToWorldTransform();
		// モデル座標系での中心
		Vec3 crnter(0, 0, 0);
		// モデル座標系での右端
		Vec3 right(1, 0, 0);

		// ワールド座標に変換
		worldm.transformPoint(&crnter);
		worldm.transformPoint(&right);

		// ワールド座標系での中心座標を設定
		Sphere::crnter = crnter;
		// ワールド座標系での半径を計算
		Sphere::radius = crnter.distance(right);
	}
}

void SphereNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	// デバッグ表示がONなら
	if (CollisionNode::GetDebugVisible())
	{
		// モデルを描画
		Obj3D::visit(renderer, parentTransform, parentFlags);
	}
}

void SphereNode::SetRadius(float radius)
{
	// モデルは半径1mで作ってあるので、
	// 半径nメートルならスケーリングn倍になる。
	this->setScaleX(radius);
	this->setScaleY(radius);
	this->setScaleZ(radius);
}

//--------------------------------------------------------------
bool CapsuleNode::init()
{
	// 基底クラス初期化
	// デバッグ表示用モデルの読み込み
	// モデルは半径1mのローポリな球を作成すること。
	if (!Obj3D::initWithFile("atari/ball.c3b"))
	{
		return false;
	}

	// updateを有効化
	this->scheduleUpdate();

	return true;
}


void CapsuleNode::update(float delta)
{
	// ワールド座標系での当たり判定カプセルを計算
	{
		// 計算済みワールド行列を取得
		Mat4 worldm = this->getNodeToWorldTransform();
		// モデル座標系での中心
		Vec3 crnter(0, 0, 0);
		// モデル座標系での上端
		Vec3 up(0, 1, 0);
		// モデル座標系での右端
		Vec3 right(1, 0, 0);

		// ワールド座標に変換
		worldm.transformPoint(&crnter);
		worldm.transformPoint(&up);
		worldm.transformPoint(&right);

		// ワールド座標系での軸線座標を設定
		Capsule::segment.start = crnter;
		Capsule::segment.end = up;
		// ワールド座標系での半径を計算
		Capsule::radius = crnter.distance(right);
	}
}

void CapsuleNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	// デバッグ表示がONなら
	if (CollisionNode::GetDebugVisible())
	{
		// モデルを描画
		Obj3D::visit(renderer, parentTransform, parentFlags);
	}
}


void CapsuleNode::SetRadius(float radius)
{
	// モデルは半径1mで作ってあるので、
	// 半径nメートルならスケーリングn倍になる。
	this->setScaleX(radius);
	this->setScaleZ(radius);
}

void CapsuleNode::SetLength(float length)
{
	// モデルは軸線の長さ1mで作ってあるので、
	// 長さnメートルならスケーリングn倍になる。
	this->setScaleY(length);
}