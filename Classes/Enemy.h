#ifndef __Enemy_H__
#define __Enemy_H__

#include <map>
#include "cocos2d.h"
#include "Obj3D.h"
#include"CollisionNode.h"

class Enemy : public Obj3D
{
private:

	Obj3D*_pBody;

	int _timer;
	float _distAngle;

	float _cycle = 0;

	std::map<cocos2d::EventKeyboard::KeyCode, bool>_keyMap;

protected:
	SphereNode* _pCollisionNodeBody;

public:
	static Enemy* Enemy::create();
	void update(float dt);
	virtual bool init();
	void createObject(cocos2d::Vec3 pos, cocos2d::Vec3 rote, float scale);
	const SphereNode* GetCollisionNodeBody() { return _pCollisionNodeBody; }
	
	


};

#endif // __HELLOWORLD_SCENE_H__
