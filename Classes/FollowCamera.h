#include "Player.h"

// �Ǐ]�J�����N���X
class FollowCamera : public cocos2d::Camera
{
private:
	cocos2d::Camera* m_camera;
	// ���@�ւ̃|�C���^
	Player* m_pPlayer;
	// �J�����Q�Ɠ_���W
	cocos2d::Vec3 m_RefPos;



	cocos2d::Vec3 m_refposed;
public:
	// �������e�ŃJ�������쐬
	static FollowCamera* createPerspective(Player* player, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	// �������e�ŃJ������������
	bool initPerspective(Player* player, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	// ���t���[���X�V
	void update(float delta) override;
};