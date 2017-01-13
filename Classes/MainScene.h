#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include"Player.h"
#include "cocos2d.h"
#include "Obj3D.h"
#include "FollowCamera.h"
#include "RailCamera.h"
#include"Enemy.h"
#include"Collision.h"
#include "CollisionNode.h"

static const int ENEMY_MAX = 5;

class MainScene : public cocos2d::Layer
{
private:

	Player* player;
	Enemy* enemy;
	Enemy*m_enemies[ENEMY_MAX];
	cocos2d::Camera* camera;
	//RailCamera* railcamrra;
	Obj3D*body;
	Obj3D*test;
	Obj3D*back;
	Obj3D*ground;


public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt)override;



	void createObject(cocos2d::Vec3 pos, cocos2d::Vec3 rote, float scale);
	CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__
