#include "qtcocos2dapp.h"
#include <QtWidgets/QApplication>

#include "Classes/AppDelegate.h"
#include "Classes/CocosQtPort/CCQGLView.h"
#include "cocos2d.h"

int main(int argc, char *argv[])
{
	/*
	QApplication a(argc, argv);
	QtCocos2dApp w;
	w.show();
	return a.exec();
	*/

	AppDelegate app(argc, argv);
	return cocos2d::CCQApplication::getInstance()->run();
}
