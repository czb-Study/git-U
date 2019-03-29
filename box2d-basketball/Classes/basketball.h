#ifndef __BASKETBALL_H__
#define __BASKETBALL_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "MyContactListener.h"
USING_NS_CC;
class basketball: public cocos2d::CCLayer
{
public:
	~basketball();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(basketball);


	b2World *world;
	CCTexture2D *texture;

	virtual void registerWithTouchDispatcher();
  	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

	void createSence();
	void update(float dt);

	void parseContact();

	MyContactListener *myContactListener;
private:
	CCSprite				*background;
	CCSprite				*arrow;//箭头
	CCSprite				*ball;
	CCSprite				*startArea;//开始点
	CCSprite				*target;//目标
	CCSprite				*basketry;//篮子 
	CCSprite				*trangle;
	CCLabelTTF		*hint;
	CCPoint				startPos;
	CCPoint				force;
	CCPoint				velocity;//速度
	CCPoint				acceleration;//加速度

	
	b2Body* body;

	bool						isShoot;
	float						left;
	int						bottom;

};

#endif // __BOX2D_DEMO_LAYER_H__
