/********************************************************************************
** Form generated from reading UI file 'Windows.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWS_H
#define UI_WINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WindowsClass)
    {
        if (WindowsClass->objectName().isEmpty())
            WindowsClass->setObjectName(QStringLiteral("WindowsClass"));
        WindowsClass->resize(600, 400);
        menuBar = new QMenuBar(WindowsClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        WindowsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WindowsClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WindowsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(WindowsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        WindowsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(WindowsClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WindowsClass->setStatusBar(statusBar);

        retranslateUi(WindowsClass);

        QMetaObject::connectSlotsByName(WindowsClass);
    } // setupUi

    void retranslateUi(QMainWindow *WindowsClass)
    {
        WindowsClass->setWindowTitle(QApplication::translate("WindowsClass", "Windows", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WindowsClass: public Ui_WindowsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWS_H
