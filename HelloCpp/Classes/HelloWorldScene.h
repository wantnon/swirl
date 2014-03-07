#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "swirlSprite.h"
#include "myDef.h"
#include "myFunc.h"
using namespace cocos2d;
using namespace cocos2d::extension;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
public:
    //touch
	virtual void ccTouchesBegan(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches , cocos2d::CCEvent* event);
    //accelerometer
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

public:
    HelloWorld(){
        pLabelR=pLabelG=pLabelB=pLabelA=NULL;
        m_targetPoint=CCPoint(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2);
    }
public:
    void update(float t);
public:
    //slider
    CCControlSlider* m_pSliderCtl;
    void sliderAction(CCObject* sender, CCControlEvent controlEvent);
	//slider2
	CCControlSlider* m_pSliderCtl2;
    void sliderAction2(CCObject* sender, CCControlEvent controlEvent);
    //slider3
	CCControlSlider* m_pSliderCtl3;
    void sliderAction3(CCObject* sender, CCControlEvent controlEvent);
    //slider4
    CCControlSlider* m_pSliderCtl4;
    void sliderAction4(CCObject* sender, CCControlEvent controlEvent);
    //slider5
    CCControlSlider* m_pSliderCtl5;
    void sliderAction5(CCObject* sender, CCControlEvent controlEvent);
    //--------
    //sliderR
    CCControlSlider* m_pSliderCtlR;
    void sliderActionR(CCObject* sender, CCControlEvent controlEvent);
    CCLabelTTF* pLabelR;
	//sliderG
	CCControlSlider* m_pSliderCtlG;
    void sliderActionG(CCObject* sender, CCControlEvent controlEvent);
    CCLabelTTF* pLabelG;
    //sliderB
	CCControlSlider* m_pSliderCtlB;
    void sliderActionB(CCObject* sender, CCControlEvent controlEvent);
    CCLabelTTF* pLabelB;
    //sliderA
    CCControlSlider* m_pSliderCtlA;
    void sliderActionA(CCObject* sender, CCControlEvent controlEvent);
    CCLabelTTF* pLabelA;
public:
    CswirlSprite*m_swirl;
    CCSprite* m_backGroundSprite;
    CCPoint m_targetPoint;
};

#endif // __HELLOWORLD_SCENE_H__
