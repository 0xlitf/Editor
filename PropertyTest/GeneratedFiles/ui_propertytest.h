/********************************************************************************
** Form generated from reading UI file 'propertytest.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYTEST_H
#define UI_PROPERTYTEST_H

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

class Ui_PropertyTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PropertyTestClass)
    {
        if (PropertyTestClass->objectName().isEmpty())
            PropertyTestClass->setObjectName(QStringLiteral("PropertyTestClass"));
        PropertyTestClass->resize(600, 400);
        menuBar = new QMenuBar(PropertyTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        PropertyTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PropertyTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PropertyTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PropertyTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PropertyTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PropertyTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PropertyTestClass->setStatusBar(statusBar);

        retranslateUi(PropertyTestClass);

        QMetaObject::connectSlotsByName(PropertyTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *PropertyTestClass)
    {
        PropertyTestClass->setWindowTitle(QApplication::translate("PropertyTestClass", "PropertyTest", 0));
    } // retranslateUi

};

namespace Ui {
    class PropertyTestClass: public Ui_PropertyTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYTEST_H
