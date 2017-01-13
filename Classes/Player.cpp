#include "Player.h"
#include "ui/CocosGUI.h"

#include <random>
USING_NS_CC;



Player* Player::create()
{
	//メモリ確保
	auto player = new (std::nothrow) Player();
	//初期化
	if (player && player->init())
	{
		// AABBからコンテンツサイズ取得
		player->_contentSize = player->getBoundingBox().size;
		// 自動リリースとして登録
		player->autorelease();

		return player;
	}
}

bool Player::init()
{
	if (!Obj3D::init())
	{
		return false;
	}
	Vec3 Pos = Vec3(linePosition[CENTER], 0, 0);
	Vec3 Rote = Vec3(0, 180, 0);
	float Scale = 0.6f;

	// モデル作成関数
	createObject(Pos, Rote, Scale);
	_pBody->playAnimation("body/running_inPlace.c3b", true);

	////攻撃当たり判定作成
	//_pCollisionNodeAttack = CapsuleNode::create();
	////半径設定
	//_pCollisionNodeAttack->SetRadius(0.1f);
	////長さ設da定
	//_pCollisionNodeAttack->SetLength(1.4f);
	////取りついた部位につなぐ
	//_pBody->addChild(_pCollisionNodeAttack);

	/*--------------------------------------------------------------------*/

	/*--------------------------------------------------------------------*/

	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
	// イベントの登録
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);

	// イベントの登録
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);



	// アップデート
	this->scheduleUpdate();
	return true;
}

/*------------------------------------------------------------------
*
*	アップデート
*
-------------------------------------------------------------------*/
void Player::update(float dt)
{
	_cycle += 0.1f;
	float scale = 1.0f + sinf(_cycle);
	//m_stick1->setScale(scale);
	moveToCurrentLine();


}

/*--------------------------------------------------------------------------
*
*	タッチイベント
*
---------------------------------------------------------------------------*/
bool Player::onTouchBegan(Touch* pTouch, Event * pEvent)
{
	return true;
}

/*------------------------------------------------------------------
*	モデル作成
*	引数：　ポジション、角度、スケール
*
-------------------------------------------------------------------*/
void Player::createObject(Vec3 pos, Vec3 rote, float scale)
{
	// モデル埋め込み
	_pBody = Obj3D::create("body/body.c3b");

	_pBody->setLightMask(0);

	//// スケール変更
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
	_pCollisionNodeBody = CapsuleNode::create();
	//半径設定
	_pCollisionNodeBody->SetRadius(0.2f);
	//長さ設定
	_pCollisionNodeBody->setPosition3D(Vec3(0, 0.f, 0));
	//取りついた部位につなぐ
	this->addChild(_pCollisionNodeBody);
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		break;
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		moveToLeftLine();
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		moveToRightLine();
		break;
	case EventKeyboard::KeyCode::KEY_1:
		break;
	}

}

void Player::switchKeyPressed(KeyStates& key)
{

}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		keyW = WAIT;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		keyS = WAIT;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		keyA = WAIT;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		keyD = WAIT;
		break;
	case EventKeyboard::KeyCode::KEY_1:
		key1 = WAIT;
		break;
	}
}

bool Player::moveToRightLine()
{
	switch (currentLine)
	{
	case LEFT:
		currentLine = CENTER;	
		break;
	case CENTER:
		currentLine = RIGHT;
		break;
	case RIGHT:
		break;
	default:
		return false;
		break;

	}
	Vec3 pos = getPosition3D();
	pos = Vec3(linePosition[currentLine], 0, 0);
	this->setPosition3D(pos);

	return true;
}

bool Player::moveToLeftLine()
{
	switch (currentLine)
	{
	case LEFT:
		break;
	case CENTER:
		currentLine = LEFT;		
		break;
	case RIGHT:
		currentLine = CENTER;
		break;
	default:
		return false;
		break;
	}
	Vec3 pos = getPosition3D();
	pos = Vec3(linePosition[currentLine], 0, 0);
	this->setPosition3D(pos);

	return true;
}

void Player::moveToCurrentLine()
{
	//float pos = _pBody->getPositionX();
	//if (pos == linePosition[currentLine])
	//{
	//	if (pos > linePosition[currentLine])
	//	{
	//		this->setPosition3D(Vec3(pos -= 0.01f,0,0));
	//	}
	//	else
	//	{
	//		_pBody->setPosition3D(Vec3(pos += 0.01f,0,0));
	//	}
	//}
}