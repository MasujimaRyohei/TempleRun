#ifndef __OBJ3D_H__
#define __OBJ3D_H__

#include "cocos2d.h"

enum LINE
{
	LEFT, CENTER, RIGHT,
};
const int LINE_NUM = 3;

class Obj3D : public cocos2d::Sprite3D
{
private:
	cocos2d::Sprite3D* m_spr3D;
	cocos2d::Animate3D* animate;
protected:
	LINE currentLine;
	float linePosition[LINE_NUM] = { -0.6f,0.f,0.6f };
public:
	static Obj3D* Obj3D::create(const std::string& modelPaht);
	bool initWithFile(const std::string& paht);
	const cocos2d::Mat4 & getNodeToParentTransform() const;
	void setLightMask(unsigned int mask);
	cocos2d::Sprite3D* getSprite3D() { return m_spr3D; }
	void playAnimation(const std::string& filename, bool isLoop = false);
	void stopAnimation();
};

#endif // __MAIN_SCENE_H__
