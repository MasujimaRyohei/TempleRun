#include "Enemy.h"
#include "ui/CocosGUI.h"
#include <random>

USING_NS_CC;



Enemy* Enemy::create()
{
	//メモリ確保
	auto enemy = new (std::nothrow) Enemy();
	//初期化
	if (enemy && enemy->init())
	{
		// AABBからコンテンツサイズ取得
		enemy->_contentSize = enemy->getBoundingBox().size;
		// 自動リリースとして登録
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

	// モデル作成関数
	createObject(Pos, Rote, Scale);
	_pBody->playAnimation("body/running_inPlace.c3b", true);




	/*--------------------------------------------------------------------*/

	/*--------------------------------------------------------------------*/

	// アップデート
	this->scheduleUpdate();
	return true;
}

/*------------------------------------------------------------------
*
*	アップデート
*
-------------------------------------------------------------------*/
void Enemy::update(float dt)
{
	Vec3 pos = getPosition3D();
	pos.z += 0.1f;
	setPosition3D(Vec3(pos.x, pos.y,pos.z));
	////　定期的に進行方向をかえる
	////　カウントダウン
	//_timer--;
	//if (_timer < 0)
	//{
	//	//　0になったら
	//	_timer = 60;
	//	//　目標角度を変更
	//	float rnd = (float)rand() / RAND_MAX - 0.5;
	//	rnd *= 180.f;
	//	//　今の角度＋ー90度が新たな進行方向
	//	_distAngle += rnd;
	//}

	////　キャラの角度操作
	//Vec3 rot = this->getRotation3D();
	////　キャラの方位角に、目標角度を代入
	////rot.y = _distAngle;
	//float angle_diff = _distAngle - rot.y;
	//rot.y += angle_diff*0.01f;
	//this->setRotation3D(rot);

	////キャラの向いている方向に進む
	////移動ベクトル
	//Vec3 moveV(0, 0, 0.05f);

	////　プレイヤーのY軸回り角度
	//float playerrot = this->getRotation3D().y;
	////　ラジアンに変換
	//playerrot = CC_DEGREES_TO_RADIANS(playerrot);

	//Mat4 rotmat;
	////　角度指定で回転行列を作成
	//Mat4::createRotationY(playerrot, &rotmat);
	////　力移動ベクトルを回転させる
	//rotmat.transformVector(&moveV);
	////　時期の現在座標を回転させる
	//Vec3 pos = this->getPosition3D();
	////　移動
	//pos += moveV;
	////　自機にセット
	//this->setPosition3D(pos);
}

/*------------------------------------------------------------------
*	モデル作成
*	引数：　ポジション、角度、スケール
*
-------------------------------------------------------------------*/
void Enemy::createObject(Vec3 pos, Vec3 rote, float scale)
{
	// モデル埋め込み
	_pBody = Obj3D::create("body/body.c3b");

	_pBody->setLightMask(0);

	// スケール変更
	//_pBody->setScaleX(scale);
	//_pBody->setScaleY(scale);
	//_pBody->setScaleZ(scale);
	_pBody->setScale(scale);

	// 回転
	_pBody->setRotation3D(Vec3(rote));

	// ポジション
	_pBody->setPosition3D(Vec3(pos));

	// ユーザカメラ１に割り振る
	_pBody->setCameraMask((unsigned short)CameraFlag::USER1);

	// モデル作成
	this->addChild(_pBody);


	//攻撃当たり判定作成
	_pCollisionNodeBody = SphereNode::create();
	//半径設定
	_pCollisionNodeBody->SetRadius(0.2f);
	//長さ設定
	_pCollisionNodeBody->setPosition3D(pos);
	//取りついた部位につなぐ
	this->addChild(_pCollisionNodeBody);

}


