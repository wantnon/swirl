

#ifndef HelloWorld_swirlSprite_h
#define HelloWorld_swirlSprite_h


#include<iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;

//SceneNode sprite's own texture is used as heightMap
class CswirlSprite : public CCSprite
{
public:
	CswirlSprite() {
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
        //
        m_backGroundTex=NULL;
        m_bending=3.0;
		m_dA=4.5;
        m_A=0.0;
        m_prisonBox=CCRect(visibleOrigin.x, visibleOrigin.y, visibleSize.width, visibleSize.height);
        m_damping=0.94;
        m_extraColor=ccc4f(71.0/255, 78.0/255, 93.0/255, 154.0/255);
        m_fakeRefraction=1.0;//0.8
        m_highlight=3.5;
    }
	virtual ~CswirlSprite(){
        if(m_backGroundTex)m_backGroundTex->release();
    };
	bool init(string heightMapTexFileName,CCTexture2D*backGroundTex,CCRect backGroundRect) ;
	virtual void draw() ;
    virtual void update(float t);
    void setBackGroundTex(CCTexture2D*backGroundTex);
    CCTexture2D*getBackGroundTex()const{return m_backGroundTex;}
    void setBending(float bending){m_bending=bending;}
    float getBending()const{return m_bending;}
    void setDA(float dA){m_dA=dA;}
    float getDA()const{return m_dA;}
    void setA(float A){m_A=A;}
    float getA()const{return m_A;}
    void setVelocity(const CCPoint&velocity){m_velocity=velocity;}
    CCPoint getVelocity()const{return m_velocity;}
    void setAcceleration(const CCPoint&acceleration){m_acceleration=acceleration;}
    CCPoint getAcceleration()const{return m_acceleration;}
    CCRect getPrisonBox()const{return m_prisonBox;}
    void setPrisonBox(const CCRect&prisonBox){m_prisonBox=prisonBox;}
    ccColor4F getExtraColor()const{return m_extraColor;}
    void setExtraColor(const ccColor4F&extraColor){m_extraColor=extraColor;}
    void setfakeRefraction(float value){m_fakeRefraction=value;}
    float getfakeRefraction()const{return m_fakeRefraction;}
    void setHighlight(float value){m_highlight=value;}
    float getHighlight()const{return m_highlight;}
    void setRefractionCenter(CCPoint refractionCenter){m_refractionCenter=refractionCenter;}
protected:
    float m_bending;
	float m_dA;//angle per frame
    float m_A;//total angle
    CCTexture2D * m_backGroundTex;
    CCRect m_backGroundRect;
    CCPoint m_velocity;
    CCPoint m_acceleration;
    float m_damping;
    CCRect m_prisonBox;
    ccColor4F m_extraColor;
    float m_fakeRefraction;
    float m_highlight;
    CCPoint m_refractionCenter;
    

};
#endif
