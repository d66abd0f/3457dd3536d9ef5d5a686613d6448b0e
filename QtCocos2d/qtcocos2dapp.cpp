#include "qtcocos2dapp.h"
#include "Classes/AppDelegate.h"
#include "Classes/CocosQtPort/CCQGLView.h"

QtCocos2dApp::QtCocos2dApp(QWidget *parent)
: QMainWindow(parent)
, _appDelegate(NULL)
, _glWidget(NULL)
{
	ui.setupUi(this);
//	AppDelegate app;
//	cocos2d::Application::getInstance()->run();
}

QtCocos2dApp::~QtCocos2dApp()
{

}

void QtCocos2dApp::closeEvent(QCloseEvent *)
{
	cocos2d::Director::getInstance()->end();
	qApp->quit();
}

void QtCocos2dApp::setGLView(QWidget *glWidget)
{
	_glWidget = glWidget;

	if (_glWidget)
	{
		ui.Layout_GLViewFrame->addWidget(_glWidget);
//		ui.GLWidget->setWidget(_glWidget);
//		setCentralWidget(ui.GLWidget);
	}
}