

#ifndef HelloWorld_SceneNode_h
#define HelloWorld_SceneNode_h
#include "cocos2d.h"

#include<iostream>
#include<map>
using namespace std;

#include "indexVBO.h"
using namespace cocos2d;
//if program1 and program2 have a uniform variable with the same name, the two variable's uniform ID (GLint) may be different. 
//so safe way is let each shader program hold his own uniform IDs.
class CGLProgramWithMyUnifos{
	CCGLProgram*program;
public:
	map<string,GLint> myUnifoMap;
    CGLProgramWithMyUnifos(){
		program=NULL;
	}
	virtual ~CGLProgramWithMyUnifos(){
		program->release();
	}
    void setProgram(CCGLProgram*_program){
        if(program){
            program->release();
        }
        program=_program;
        program->retain();
    }
    CCGLProgram*getProgram(){
        return program;
    }

};

//SceneNode sprite's own texture is used as heightMap
class SceneNode : public CCSprite{//here SceneNode is a CCSprite
public:
	SceneNode() {
        step_s=0;
        step_t=0;
        backGroundSprite_outRef=NULL;
        bending=3.0;
		dA=30.0;
    
    }
	virtual ~SceneNode(){};
	bool init(string heightMapTexFileName,CCSprite*backGroundSprite) ;
	void draw() ;
    float bending;
	float dA;//per second
private:
	
	CGLProgramWithMyUnifos program_renderRipple;

	
	float step_s,step_t;
    
    CCSprite * backGroundSprite_outRef;
    
    
    

  








};
#endif
