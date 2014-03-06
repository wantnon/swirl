
#include "swirlSprite.h"

#include <iostream>
#include <map>
using namespace std ;
#include "glProgramWithMyUnifos.h"

using namespace cocos2d ;


bool CswirlSprite::init(string heightMapTexFileName,CCTexture2D*backGroundTex,CCRect backGroundRect)
{
////    //set projection to 2D (default is 3D). if use 3D projection, may cause tiny projection error, in some situation, if the error accumulated across frames, may cause effect wrong.
////    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
   
    //init this CCSprite
    this->initWithFile(heightMapTexFileName.c_str());
    //set backGroundTex
    setBackGroundTex(backGroundTex);
    //backGroundRect
    m_backGroundRect=backGroundRect;
    //create and set shader program
	{
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("renderRipple.fsh").c_str())->getCString();
		CGLProgramWithMyUnifos* program = new CGLProgramWithMyUnifos();
        program->autorelease();
		program->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
        //bind attribute
		program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        //link  (must after bindAttribute)
		program->link();
        //get cocos2d-x build-in uniforms
		program->updateUniforms();
        //get my own uniforms
        program->attachUniform("colorMap");
        program->attachUniform("texSize");
        program->attachUniform("backGroundTexSize");
        program->attachUniform("texLUPos");
        program->attachUniform("backGroundTexLUPos");
        program->attachUniform("bending");
        program->attachUniform("angleAllPixel");
        program->attachUniform("extraColor");
        program->attachUniform("fakeRefraction");
        this->setShaderProgram(program);
        //check gl error
		CHECK_GL_ERROR_DEBUG();
	}
	//check gl error
	CHECK_GL_ERROR_DEBUG();
    this->scheduleUpdate();
	return true ;
}
void CswirlSprite::update(float t){
  
    m_velocity=m_velocity+m_acceleration;
    float velocityLen=ccpLength(m_velocity)*m_damping;
    m_velocity=ccpNormalize(m_velocity)*velocityLen;
    
    CCPoint pos=this->getPosition();
    
    pos=pos+m_velocity;
    if(pos.x>m_prisonBox.getMaxX()){
        pos.x=m_prisonBox.getMaxX();
        m_velocity=CCPoint(0,0);
    }
    if(pos.x<m_prisonBox.getMinX()){
        pos.x=m_prisonBox.getMinX();
        m_velocity=CCPoint(0,0);
    }
    if(pos.y>m_prisonBox.getMaxY()){
        pos.y=m_prisonBox.getMaxY();
        m_velocity=CCPoint(0,0);
    }
    if(pos.y<m_prisonBox.getMinY()){
        pos.y=m_prisonBox.getMinY();
        m_velocity=CCPoint(0,0);
    }
    
    this->setPosition(pos);
}
void CswirlSprite::setBackGroundTex(CCTexture2D*backGroundTex){
    assert(backGroundTex);
    if(m_backGroundTex==NULL){
        m_backGroundTex=backGroundTex;
        m_backGroundTex->retain();
    }else{
        m_backGroundTex->release();
        m_backGroundTex=backGroundTex;
        m_backGroundTex->retain();
    }
}

void CswirlSprite::draw()
{
    //update angle
    m_A+=m_dA;
    if(m_A>=360.0)m_A=0.0;//note: here must do the wrap, or the value of A will be overflow and cause wrong effect
    //----prepare uniform values
    float angleAllPixel_tmp = m_A*M_PI/180;
    float texSize_tmp[2]={this->boundingBox().getMaxX()-this->boundingBox().getMinX(),this->boundingBox().getMaxY()-this->boundingBox().getMinY()};//{this->getTexture()->getContentSize().width,this->getTexture()->getContentSize().height};
  //  CCLOG("texSize:%f,%f",texSize_tmp[0],texSize_tmp[1]);
    float texLUPos_tmp[2]={this->boundingBox().getMinX(),this->boundingBox().getMaxY()};
  //  CCLOG("texLUPos:%f,%f",texLUPos_tmp[0],texLUPos_tmp[1]);
    float backGroundTexLUPos_tmp[2]={m_backGroundRect.getMinX(),m_backGroundRect.getMaxY()};
    float backGroundTexSize_tmp[2]={m_backGroundTex->getContentSize().width,m_backGroundTex->getContentSize().height};
    float extraColor_tmp[4]={this->m_extraColor.r,this->m_extraColor.g,this->m_extraColor.b,this->m_extraColor.a};
    //----change shader
    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    CGLProgramWithMyUnifos*program=(CGLProgramWithMyUnifos*)this->getShaderProgram();
    program->use();
    program->setUniformsForBuiltins();
    //pass values for my own uniforms
    program->passUnifoValue1f("bending", m_bending);
    program->passUnifoValue1f("angleAllPixel", angleAllPixel_tmp);
    program->passUnifoValueNfv("texSize", texSize_tmp, 2);
    program->passUnifoValueNfv("backGroundTexSize", backGroundTexSize_tmp, 2);
    program->passUnifoValueNfv("texLUPos", texLUPos_tmp, 2);
    program->passUnifoValueNfv("backGroundTexLUPos", backGroundTexLUPos_tmp, 2);
    program->passUnifoValueNfv("extraColor", extraColor_tmp, 4);
    program->passUnifoValue1f("fakeRefraction", m_fakeRefraction);
    //pass texture attach point id to sampler uniform
    program->passUnifoValue1i("colorMap", 1);
    //attach texture to texture attach point
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_backGroundTex->getName());
    glActiveTexture(GL_TEXTURE0);//back to GL_TEXTURE0
    
    //----call CCSprite::draw
    CCSprite::draw();
}