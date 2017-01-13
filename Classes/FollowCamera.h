#include "Player.h"

// 追従カメラクラス
class FollowCamera : public cocos2d::Camera
{
private:
	cocos2d::Camera* m_camera;
	// 自機へのポインタ
	Player* m_pPlayer;
	// カメラ参照点座標
	cocos2d::Vec3 m_RefPos;



	cocos2d::Vec3 m_refposed;
public:
	// 透視投影でカメラを作成
	static FollowCamera* createPerspective(Player* player, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	// 透視投影でカメラを初期化
	bool initPerspective(Player* player, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	// 毎フレーム更新
	void update(float delta) override;
};