#include "HelloWorldScene.h"
#include "InterfaceLoader.h"
#include "cocos-ext.h"
#include <QtDebug>

USING_NS_CC;
USING_NS_CC_EXT;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	FileUtils::getInstance()->addSearchPath("../QtCocos2d/Resources");
	FileUtils::getInstance()->addSearchResolutionsOrder("resource-auto");
	Director::getInstance()->setContentScaleFactor(2.0f);
	Director::getInstance()->setAnimationInterval(FLT_MIN);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto centerNode = Node::create();
	centerNode->setAnchorPoint(Point::ANCHOR_MIDDLE);
//	centerNode->setContentSize(visibleSize);
	centerNode->setPosition(origin + visibleSize/2);
	this->addChild(centerNode);

	auto frame = Sprite::create("system/frame_iphone4.png");
	frame->setAnchorPoint(Point::ANCHOR_MIDDLE);
	centerNode->addChild(frame);

	auto worldPos = centerNode->convertToWorldSpace(frame->getPosition());
	qDebug() << worldPos.x << "," << worldPos.y;

	auto listener = EventListenerMouse::create();
	listener->onMouseScroll = [this, frame](Event* event){
		EventMouse *e = dynamic_cast<EventMouse *>(event);
		if (NULL != e)
		{
			float scrollY = e->getScrollY();
			frame->setScale(scrollY / 10.0f + frame->getScale());
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto baseNode = Node::create();
	baseNode->setContentSize(Size(480, 320));
	baseNode->setPosition(baseNode->getContentSize() / -2 + frame->getContentSize()/2);
	frame->addChild(baseNode);
	worldPos = frame->convertToWorldSpace(baseNode->getPosition());
	qDebug() << worldPos.x << "," << worldPos.y;
	/*
	ControlButton * button = ControlButton::create();
	button->setTitleLabelForState(Label::createWithSystemFont("aaa", "MS Gothic", 12), Control::State::NORMAL);
	baseNode->addChild(button);
	*/
	_metaInfo = InterfaceLoader::getInstance().loadJSon("interface/scene/scenetest.json");
	if (_metaInfo)
	{
		_metaInfo->retain();
		baseNode->addChild(_metaInfo->getBaseNode());
	}
	    
    return true;
}


HelloWorld::~HelloWorld()
{
	CC_SAFE_RELEASE_NULL(_metaInfo);
}
