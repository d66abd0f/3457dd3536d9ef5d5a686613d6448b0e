#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "InterfaceLoader.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();        
    CREATE_FUNC(HelloWorld);

	virtual ~HelloWorld();

	MetaInfo* _metaInfo;
};

#endif // __HELLOWORLD_SCENE_H__
