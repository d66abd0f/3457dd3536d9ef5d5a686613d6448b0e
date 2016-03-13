#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Classes/CocosQtPort/CCQGLView.h"

USING_NS_CC;

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		auto qglview = CCQGLView::getInstance();
		director->setOpenGLView(qglview);
		_mainWindow.setGLView(qglview->getGLWidget());

		QSize viewSize = QSize(qglview->getViewSize().width, qglview->getViewSize().height);

		Director::getInstance()->getOpenGLView()->setDesignResolutionSize(viewSize.width(), viewSize.height(), ResolutionPolicy::SHOW_ALL);
		qglview->getGLWidget()->setMinimumSize(viewSize);
		qglview->getGLWidget()->setMaximumSize(viewSize);
		_mainWindow.show();
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
