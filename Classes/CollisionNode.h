#pragma once

#include "Obj3D.h"
#include "Collision.h"

// 当たり判定ノード管理クラス
class CollisionNode
{
protected:
	// デバッグ表示のON/OFFフラグ
	static bool s_DebugVisible;
public:
	// デバッグ表示のON/OFFを設定
	static void SetDebugVisible(bool flag) { s_DebugVisible = flag; }
	// デバッグ表示のON/OFFを取得
	static bool GetDebugVisible(void) { return s_DebugVisible; }
};

// 当たり判定球ノード
class SphereNode : public Sphere, public Obj3D
{
public:
	CREATE_FUNC(SphereNode);
	// 初期化
	bool init();
	// 毎フレーム更新
	void update(float delta) override;
	// 描画
	void visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags);
	// ローカル半径を設定
	void SetRadius(float radius);
};

// 当たり判定カプセルノード
class CapsuleNode : public Capsule, public Obj3D
{
public:
	CREATE_FUNC(CapsuleNode);
	// 初期化
	bool init();
	// 毎フレーム更新
	void update(float delta) override;
	// 描画
	void visit(cocos2d::Renderer * renderer, const cocos2d::Mat4 & parentTransform, uint32_t parentFlags);
	// ローカル半径を設定
	void SetRadius(float radius);
	// ローカル軸長さを設定
	void SetLength(float length);
};