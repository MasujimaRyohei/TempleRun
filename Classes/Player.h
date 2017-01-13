#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <map>
#include "cocos2d.h"
#include "Obj3D.h"
#include"CollisionNode.h"


enum KeyStates
{
	WAIT,
	BEGAN,
	KEEP,
	ENDED,
};

class Player : public Obj3D
{
private:
	Obj3D*_pBody;
	KeyStates keyW;
	KeyStates keyA;
	KeyStates keyS;
	KeyStates keyD;
	KeyStates key1;

	float _cycle = 0;

	std::map<cocos2d::EventKeyboard::KeyCode, bool>_keyMap;
protected:
	//攻撃当たり判定カプセル
	CapsuleNode* _pCollisionNodeBody;
public:
	static Player* Player::create();
	void update(float dt);
	virtual bool init();

	//攻撃当たり判定カプセル取得
	const CapsuleNode* getCollisionNodeBody() { return _pCollisionNodeBody; }

	// タッチイベント
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event * pEvent);
	void createObject(cocos2d::Vec3 pos, cocos2d::Vec3 rote, float scale);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* pEvent);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* pEvent);

	void switchKeyPressed(KeyStates& key);

	bool moveToRightLine();
	bool moveToLeftLine();

	void moveToCurrentLine();


};

#endif // __HELLOWORLD_SCENE_H__
