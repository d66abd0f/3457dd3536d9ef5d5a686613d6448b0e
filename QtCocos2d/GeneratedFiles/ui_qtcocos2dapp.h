/********************************************************************************
** Form generated from reading UI file 'qtcocos2dapp.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCOCOS2DAPP_H
#define UI_QTCOCOS2DAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtCocos2dAppClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QFrame *GLViewFrame;
    QGridLayout *Layout_GLViewFrame;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtCocos2dAppClass)
    {
        if (QtCocos2dAppClass->objectName().isEmpty())
            QtCocos2dAppClass->setObjectName(QStringLiteral("QtCocos2dAppClass"));
        QtCocos2dAppClass->resize(1108, 836);
        centralWidget = new QWidget(QtCocos2dAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        GLViewFrame = new QFrame(centralWidget);
        GLViewFrame->setObjectName(QStringLiteral("GLViewFrame"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(GLViewFrame->sizePolicy().hasHeightForWidth());
        GLViewFrame->setSizePolicy(sizePolicy1);
        GLViewFrame->setMinimumSize(QSize(1000, 600));
        GLViewFrame->setMaximumSize(QSize(1000, 600));
        GLViewFrame->setFrameShape(QFrame::StyledPanel);
        GLViewFrame->setFrameShadow(QFrame::Plain);
        GLViewFrame->setLineWidth(0);
        Layout_GLViewFrame = new QGridLayout(GLViewFrame);
        Layout_GLViewFrame->setSpacing(0);
        Layout_GLViewFrame->setContentsMargins(11, 11, 11, 11);
        Layout_GLViewFrame->setObjectName(QStringLiteral("Layout_GLViewFrame"));
        Layout_GLViewFrame->setContentsMargins(0, 0, 0, 0);

        gridLayout->addWidget(GLViewFrame, 0, 0, 1, 1);

        QtCocos2dAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtCocos2dAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1108, 23));
        QtCocos2dAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtCocos2dAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtCocos2dAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtCocos2dAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtCocos2dAppClass->setStatusBar(statusBar);

        retranslateUi(QtCocos2dAppClass);

        QMetaObject::connectSlotsByName(QtCocos2dAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtCocos2dAppClass)
    {
        QtCocos2dAppClass->setWindowTitle(QApplication::translate("QtCocos2dAppClass", "QtCocos2dApp", 0));
    } // retranslateUi

};

namespace Ui {
    class QtCocos2dAppClass: public Ui_QtCocos2dAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCOCOS2DAPP_H
