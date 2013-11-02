

#include "SceneNode.h"
#include <iostream>
#include <map>
#include "support/ccUtils.h"
#include "myFunc.h"
using namespace cocos2d ;
using namespace std ;


bool SceneNode::init(string heightMapTexFileName,CCSprite*backGroundSprite)
{
    //set projection to 2D (default is 3D). if use 3D projection, may cause tiny projection error, in some situation, if the error accumulated across frames, may cause effect wrong.
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
    //init this CCSprite
    this->initWithFile(heightMapTexFileName.c_str());
    //link backGroundSprite_outRef
    backGroundSprite_outRef=backGroundSprite;
    //use bufferTexSize to calculate step_s and step_t
    step_s=1.0/this->getTexture()->getContentSize().width;
	step_t=1.0/this->getTexture()->getContentSize().height;
    //renderRipple shader
	{
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename("renderRipple.fsh").c_str())->getCString();
		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
        //bind attribute
		pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        //link  (must after bindAttribute)
		pProgram->link();
        //get cocos2d-x build-in uniforms
		pProgram->updateUniforms();
        //get my own uniforms
		map<string,GLint> myUnifoMap;
        myUnifoMap["colorMap"] = glGetUniformLocation(pProgram->getProgram(),"colorMap");
        myUnifoMap["step_s"] = glGetUniformLocation(pProgram->getProgram(),"step_s");
        myUnifoMap["step_t"] = glGetUniformLocation(pProgram->getProgram(),"step_t");
        myUnifoMap["texSize"] = glGetUniformLocation(pProgram->getProgram(),"texSize");
        myUnifoMap["bending"] = glGetUniformLocation(pProgram->getProgram(),"bending");
        //make program_renderRipple
        program_renderRipple.myUnifoMap=myUnifoMap;
        program_renderRipple.setProgram(pProgram);
        //program can be released
        pProgram->release();
        //check gl error
		CHECK_GL_ERROR_DEBUG();
	}
	//check gl error
	CHECK_GL_ERROR_DEBUG();

	return true ;
}
void SceneNode::draw()
{
    //----change shader
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));
    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    //render the rect equals to this's boundingbox on backGroudSprite to a texture
    
    CCRect thisRect=this->boundingBox();
    float rttWidth=thisRect.getMaxX()-thisRect.getMinX();
    float rttHeight=thisRect.getMaxY()-thisRect.getMinY();
    CCRenderTexture* renderTex=CCRenderTexture::create(rttWidth, rttHeight);
    CCPoint oldPos=backGroundSprite_outRef->getPosition();//save old position
    backGroundSprite_outRef->setPosition(oldPos-CCPoint(thisRect.getMinX(),thisRect.getMinY()));//modify postion
    renderTex->begin();
  //  backGroundSprite_outRef->setVisible(true);
    backGroundSprite_outRef->visit();
  //  backGroundSprite_outRef->setVisible(false);
    renderTex->end();//get renderTex
    backGroundSprite_outRef->setPosition(oldPos);//restore position
    
    
    
    //
    //----change shader
    this->setShaderProgram(program_renderRipple.getProgram());
    ccGLEnable(m_eGLServerState);
    //pass values for cocos2d-x build-in uniforms
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    //pass values for my own uniforms
    glUniform1f(program_renderRipple.myUnifoMap["step_s"],step_s);
    glUniform1f(program_renderRipple.myUnifoMap["step_t"],step_t);
    glUniform1f(program_renderRipple.myUnifoMap["bending"],bending);
    float texSize_c[2]={this->getTexture()->getContentSize().width,this->getTexture()->getContentSize().height};
    glUniform2fv(program_renderRipple.myUnifoMap["texSize"], 1, texSize_c);
    //pass texture attach point id to sampler uniform
    glUniform1i(program_renderRipple.myUnifoMap["colorMap"],1);
    //attach texture to texture attach point
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, renderTex->getSprite()->getTexture()->getName());
    glActiveTexture(GL_TEXTURE0);//back to GL_TEXTURE0
    
    //----cal CCSprite::draw
    CCSprite::draw();
}