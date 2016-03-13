#ifndef QTCOCOS2DAPP_H
#define QTCOCOS2DAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_qtcocos2dapp.h"

class AppDelegate;
namespace Ui {
	class QtCocos2dApp;
}

class QtCocos2dApp : public QMainWindow
{
	Q_OBJECT

public:
	QtCocos2dApp(QWidget *parent = 0);
	~QtCocos2dApp();

	void setGLView(QWidget *glWidget);

protected:
	void closeEvent(QCloseEvent *);

private:
	AppDelegate         *_appDelegate;
	QWidget             *_glWidget;

private:
	Ui::QtCocos2dAppClass ui;
};

#endif // QTCOCOS2DAPP_H
