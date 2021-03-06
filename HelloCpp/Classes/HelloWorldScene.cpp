#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;
#include "CCControlButton.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

 /*   /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
*/
    /////////////////////////////
    // 3. add your codes below...
    //enable accelerometer
    setAccelerometerEnabled(true);
    //enable touch
	setTouchEnabled( true );
    //add a empty sprite to avoid CCLabelTTF show a block rect, and setDisplayStats(true) crash.
    CCSprite* sprite=CCSprite::create();
    this->addChild(sprite,0);
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();//winSize equals to designResolutionSize
    
    //show frame rate info
    CCDirector::sharedDirector()->setDisplayStats(true);
    //start update
    this->scheduleUpdate();
    
    
    
    m_backGroundSprite=CCSprite::create();
    m_backGroundSprite->initWithFile("HelloWorld_iphone5.png");
    m_backGroundSprite->setAnchorPoint(ccp(0.5, 0.5));
    m_backGroundSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(m_backGroundSprite,0);
    //
    m_swirl=new CswirlSprite();
    m_swirl->autorelease();
    m_swirl->init("swirl_frame0.png",m_backGroundSprite->getTexture(),m_backGroundSprite->boundingBox());
    m_swirl->setAnchorPoint(ccp(0.5,0.5));
    m_swirl->setPosition(ccp(winSize.width/2, winSize.height/2));
    CCRect boundingBox=m_swirl->boundingBox();
    float r=(boundingBox.getMaxX()-boundingBox.getMinX())/2;
    m_swirl->setRefractionCenter(ccp(winSize.width/2+r, winSize.height/2));
    this->addChild(m_swirl,1);
    
    //slider
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(6.0f); // Sets the max value of range
		slider->setValue(m_swirl->getBending());
		slider->setPosition(ccp(screenSize.width *0.35, 240));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction), CCControlEventValueChanged);
		m_pSliderCtl=slider;
		addChild(m_pSliderCtl,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("bending ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
	}
	//slider2
    {
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(16.0f); // Sets the max value of range
		slider->setValue(m_swirl->getDA());
		slider->setPosition(ccp(screenSize.width *0.35, 240-40));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction2), CCControlEventValueChanged);
		m_pSliderCtl2=slider;
		addChild(m_pSliderCtl2,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("speed ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
	}
    //slider3
    {
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(2.0f); // Sets the max value of range
		slider->setValue(m_swirl->getScale());
		slider->setPosition(ccp(screenSize.width *0.35, 240-80));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction3), CCControlEventValueChanged);
		m_pSliderCtl3=slider;
		addChild(m_pSliderCtl3,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("size ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
	}
    //slider4
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(40.0f); // Sets the max value of range
		slider->setValue(m_swirl->getHighlight());
		slider->setPosition(ccp(screenSize.width *0.35, 240-120));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction4), CCControlEventValueChanged);
		m_pSliderCtl4=slider;
		addChild(m_pSliderCtl4,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("highlight ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
	}

    //slider5
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(1.0f); // Sets the max value of range
		slider->setValue(m_swirl->getfakeRefraction());
		slider->setPosition(ccp(screenSize.width *0.35, 240-160));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderAction5), CCControlEventValueChanged);
		m_pSliderCtl5=slider;
		addChild(m_pSliderCtl5,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("refraction ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
	}
        //-------
    //sliderR
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(255.0f); // Sets the max value of range
		slider->setValue(m_swirl->getExtraColor().r*255);
		slider->setPosition(ccp(screenSize.width *0.75, 200));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderActionR), CCControlEventValueChanged);
		m_pSliderCtlR=slider;
		addChild(m_pSliderCtlR,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("R ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
        //valueStr
        pLabelR = CCLabelTTF::create(numberToStr((int)(m_swirl->getExtraColor().r*255)).c_str(), "Arial", 40);
		pLabelR->setPosition(ccp(slider->getPositionX()+slider->getContentSize().width/2+pLabelR->getContentSize().width/2+15, slider->getPositionY()));
        this->addChild(pLabelR, 1);
        
	}
	//sliderG
    {
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(255.0f); // Sets the max value of range
		slider->setValue(m_swirl->getExtraColor().g*255);
		slider->setPosition(ccp(screenSize.width *0.75, 200-40));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderActionG), CCControlEventValueChanged);
		m_pSliderCtlG=slider;
		addChild(m_pSliderCtlG,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("G ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
        //valueStr
        pLabelG = CCLabelTTF::create(numberToStr((int)(m_swirl->getExtraColor().g*255)).c_str(), "Arial", 40);
		pLabelG->setPosition(ccp(slider->getPositionX()+slider->getContentSize().width/2+pLabelG->getContentSize().width/2+15, slider->getPositionY()));
        this->addChild(pLabelG, 1);
	}
    //sliderB
    {
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(255.0f); // Sets the max value of range
		slider->setValue(m_swirl->getExtraColor().b*255);
		slider->setPosition(ccp(screenSize.width *0.75, 200-80));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderActionB), CCControlEventValueChanged);
		m_pSliderCtlB=slider;
		addChild(m_pSliderCtlB,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("B ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
        //valueStr
        pLabelB = CCLabelTTF::create(numberToStr((int)(m_swirl->getExtraColor().b*255)).c_str(), "Arial", 40);
		pLabelB->setPosition(ccp(slider->getPositionX()+slider->getContentSize().width/2+pLabelB->getContentSize().width/2+15, slider->getPositionY()));
        this->addChild(pLabelB, 1);
	}
    //sliderA
	{
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
		CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
		slider->setAnchorPoint(ccp(0.5f, 0.5f));
		slider->setMinimumValue(0.0f); // Sets the min value of range
		slider->setMaximumValue(255.0f); // Sets the max value of range
		slider->setValue(m_swirl->getExtraColor().a*255);
		slider->setPosition(ccp(screenSize.width *0.75, 200-120));
		slider->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::sliderActionA), CCControlEventValueChanged);
		m_pSliderCtlA=slider;
		addChild(m_pSliderCtlA,100);
		//title
		CCLabelTTF* pLabel = CCLabelTTF::create("A ", "Arial", 40);
		pLabel->setPosition(ccp(slider->getPositionX()-slider->getContentSize().width/2-pLabel->getContentSize().width/2, slider->getPositionY()));
        this->addChild(pLabel, 1);
        //valueStr
        pLabelA = CCLabelTTF::create(numberToStr((int)(m_swirl->getExtraColor().a*255)).c_str(), "Arial", 40);
		pLabelA->setPosition(ccp(slider->getPositionX()+slider->getContentSize().width/2+pLabelA->getContentSize().width/2+15, slider->getPositionY()));
        this->addChild(pLabelA, 1);
	}


    
    // author info
    {
        CCLabelTTF* pLabel = CCLabelTTF::create("by yang chao (wantnon) 2013-11-2", "Arial", 30);
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height-60));
        this->addChild(pLabel, 1);
    }
    
    // add a label shows "Hello World"
    // create and initialize a label
 
    CCLabelTTF* pLabel = CCLabelTTF::create("2D Swirl Demo (use accelerometer)", "Arial", 45);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
  
    
    // add "HelloWorld" splash screen"
/*    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    */
    return true;
}

void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
    
    float ax= pAccelerationValue->x;// * 9.81f;
    float ay= pAccelerationValue->y;// * 9.81f;
    float az= pAccelerationValue->z;// * 9.81f;
  //  CCLOG("a:%f,%f,%f",ax,ay,az);
    CCPoint accelerationXY=CCPoint(ax,ay);
    m_swirl->setAcceleration(accelerationXY);
    
    
    
}
void HelloWorld::update(float t){
    if(!(m_targetPoint.x==-1&&m_targetPoint.y==-1)){//if target not invalid
        CCPoint swirlToTargetDir=ccpNormalize(m_targetPoint-m_swirl->getPosition());
        float swirlToTargetLen=ccpLength(m_targetPoint-m_swirl->getPosition());
        float velocityLen=MIN(7,swirlToTargetLen);
        CCPoint velocity=ccpMult(swirlToTargetDir, velocityLen);
        CCPoint oldVelocity=m_swirl->getVelocity();
        CCPoint blendVelocity=ccpMult(velocity+oldVelocity,0.5);
        m_swirl->setVelocity(blendVelocity);
    }
}


void HelloWorld::sliderAction(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
   // CCLOG("slider value:%f",value);
    m_swirl->setBending(value);
    
}
void HelloWorld::sliderAction2(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
  //  CCLOG("slider value:%f",value);
    m_swirl->setDA(value);
    
}
void HelloWorld::sliderAction3(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
  //  CCLOG("slider value:%f",value);
    m_swirl->setScale(value);
    
}
void HelloWorld::sliderAction4(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    // CCLOG("slider value:%f",value);
    m_swirl->setHighlight(value);
    
}
void HelloWorld::sliderAction5(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    // CCLOG("slider value:%f",value);
    m_swirl->setfakeRefraction(value);
    
}

void HelloWorld::sliderActionR(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    // CCLOG("slider value:%f",value);
    ccColor4F color=m_swirl->getExtraColor();
    color.r=value/255.0;
    m_swirl->setExtraColor(color);
    pLabelR->setString(numberToStr((int)(m_swirl->getExtraColor().r*255)).c_str());
    pLabelR->setPosition(ccp(m_pSliderCtlR->getPositionX()+m_pSliderCtlR->getContentSize().width/2+pLabelR->getContentSize().width/2+15, m_pSliderCtlR->getPositionY()));
    
}
void HelloWorld::sliderActionG(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    // CCLOG("slider value:%f",value);
    ccColor4F color=m_swirl->getExtraColor();
    color.g=value/255.0;
    m_swirl->setExtraColor(color);
    pLabelG->setString(numberToStr((int)(m_swirl->getExtraColor().g*255)).c_str());
    pLabelG->setPosition(ccp(m_pSliderCtlG->getPositionX()+m_pSliderCtlG->getContentSize().width/2+pLabelG->getContentSize().width/2+15, m_pSliderCtlG->getPositionY()));
    
    
}
void HelloWorld::sliderActionB(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    // CCLOG("slider value:%f",value);
    ccColor4F color=m_swirl->getExtraColor();
    color.b=value/255.0;
    m_swirl->setExtraColor(color);
    pLabelB->setString(numberToStr((int)(m_swirl->getExtraColor().b*255)).c_str());
    pLabelB->setPosition(ccp(m_pSliderCtlB->getPositionX()+m_pSliderCtlB->getContentSize().width/2+pLabelB->getContentSize().width/2+15, m_pSliderCtlB->getPositionY()));
    
}
void HelloWorld::sliderActionA(CCObject* sender, CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    float value=pSlider->getValue();
    //CCLOG("slider value:%f",value);
    ccColor4F color=m_swirl->getExtraColor();
    color.a=value/255.0;
    m_swirl->setExtraColor(color);
    pLabelA->setString(numberToStr((int)(m_swirl->getExtraColor().a*255)).c_str());
    pLabelA->setPosition(ccp(m_pSliderCtlA->getPositionX()+m_pSliderCtlA->getContentSize().width/2+pLabelA->getContentSize().width/2+15, m_pSliderCtlA->getPositionY()));
    
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        
        m_targetPoint=CCPoint(-1,-1);//invalid
    }
}
void HelloWorld::ccTouchesMoved(cocos2d::CCSet* touches , cocos2d::CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        
        m_targetPoint=loc_GLSpace;

    
        
		
    }
    
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
	for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;
        
        CCPoint loc_winSpace = touch->getLocationInView();
        CCPoint loc_GLSpace = CCDirector::sharedDirector()->convertToGL(loc_winSpace);
        //CCLOG("loc_GLSpace:%f,%f",loc_GLSpace.x,loc_GLSpace.y);
        m_targetPoint=loc_GLSpace;
        
        
    }
}

