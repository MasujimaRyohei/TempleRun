#include "MainScene.h"
#include "ui/CocosGUI.h"
#include "CollisionNode.h"
#include <random>
#include <Player.h>
#include <Obj3D.h>
USING_NS_CC;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	CollisionNode::SetDebugVisible(true);

	player = Player::create();
	player->setPosition3D(Vec3(0, 0, 0));
	this->addChild(player);

	enemy = Enemy::create();
	enemy->setPosition3D(Vec3(0, 0, -10));
	this->addChild(enemy);

	//for (int i = 0; i < ENEMY_MAX; i++)
	//{
	//	m_enemies[i] = Enemy::create();
	//	this->addChild(m_enemies[i]);
	//}

	//camera = FollowCamera::createPerspective(player, 60.0f, 960.0f / 640.0f, 2.4f, 1000.0f);
	camera = Camera::createPerspective(60.0f, 640.0f / 1136.0f, 1.4f, 1000.0f);
	Vec3 pp = player->getPosition3D();
	camera->setPosition3D(Vec3(0,1.2f,2.5));
	camera->setCameraFlag(CameraFlag::USER1);
	addChild(camera);

	//Capsule sphereA;
	//sphereA.segment.start = Vec3(-3.0f, 1, 0);
	//sphereA.segment.end = Vec3(3.0f, 1, 0);
	//sphereA.radius = 2.0f;

	//Capsule CapsuleA;
	//CapsuleA.segment.start = Vec3(-1.0f, 1, 0);
	//CapsuleA.segment.end = Vec3(1.0f, 1, 0);
	//CapsuleA.radius = 1.0f;

	//bool hit = CheckCapsule2Capsule(sphereA, CapsuleA);
	//if (hit)
	//{
	//	log("HHHHHHHHHIIIIIIIIIITTTTTTTTTT");
	//}
	//else
	//{
	//	log("NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOooo");
	//}
	/*--------------------------------------------------------------------*/

	/*--------------------------------------------------------------------*/

	// 光の方向ベクトル
	Vec3 dLightDirection(1.0f, -1.0f, -1.0f);
	// 光の色RGB
	Color3B dLightColor(0xff, 0xff, 0xff);
	// 平行光源の作成
	DirectionLight* directionLight = DirectionLight::create(dLightDirection, dLightColor);
	// ライトを0番に振り分け
	directionLight->setLightFlag(LightFlag::LIGHT0);
	this->addChild(directionLight);

	// 光の色　RGB
	Color3B aLightColor(0x40, 0x40, 0x40);
	// 環境光源の作成
	AmbientLight* ambient = AmbientLight::create(aLightColor);
	// ライトを0番に振り分け
	ambient->setLightFlag(LightFlag::LIGHT0);
	this->addChild(ambient);

	/*--------------------------------------------------------------------*/

	/*--------------------------------------------------------------------*/

	// モデル埋め込み,背景（天球）
	back = Obj3D::create("skydome.c3b");
	back->setScale(5.0);
	this->addChild(back);
	back->setLightMask(0);

	//// モデル埋め込み,地面
	//ground = Obj3D::create("miti.c3b");
	//ground->setScale(1);
	//this->addChild(ground);
	//ground->setLightMask(1);

	// アップデート
	this->scheduleUpdate();
	return true;
}

/*------------------------------------------------------------------
*
*	アップデート
*
-------------------------------------------------------------------*/
void MainScene::update(float dt)
{
	//プレイヤーの攻撃当たり判定カプセル取得
	const Capsule* bulletCapsule = player->getCollisionNodeBody();
	//敵の数だけ処理する

		////すでに死んでいる敵は、スキップ
		//if (m_enemies[i]->getDeath())
		//{
		//	continue;
		//}
		//敵の本体当たり判定球取得
	const Sphere* enemySphere = enemy->GetCollisionNodeBody();
	Vec3 inter;
	if (CheckSphere2Capsule(*enemySphere, *bulletCapsule, &inter))
	{
		Director::getInstance()->replaceScene(MainScene::createScene());
	}
}