/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *action_new;
    QAction *action_open;
    QAction *action_close;
    QAction *action_save;
    QAction *actionPreview;
    QWidget *centralWidget;
    QVBoxLayout *centralWidgetVerticalLayout;
    QMenuBar *menuBar;
    QMenu *flieMenu;
    QMenu *viewMenu;
    QDockWidget *dockWidget_library;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QDockWidget *dockWidget_itemList;
    QWidget *dockWidgetContents_itemList;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeWidget_itemList;
    QDockWidget *dockWidget_propertyTree;
    QWidget *dockWidgetContents_propertyTree;
    QVBoxLayout *verticalLayout_propertyTree;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(817, 562);
        MainWindowClass->setFocusPolicy(Qt::NoFocus);
        action_new = new QAction(MainWindowClass);
        action_new->setObjectName(QStringLiteral("action_new"));
        action_open = new QAction(MainWindowClass);
        action_open->setObjectName(QStringLiteral("action_open"));
        action_close = new QAction(MainWindowClass);
        action_close->setObjectName(QStringLiteral("action_close"));
        action_save = new QAction(MainWindowClass);
        action_save->setObjectName(QStringLiteral("action_save"));
        actionPreview = new QAction(MainWindowClass);
        actionPreview->setObjectName(QStringLiteral("actionPreview"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidgetVerticalLayout = new QVBoxLayout(centralWidget);
        centralWidgetVerticalLayout->setObjectName(QStringLiteral("centralWidgetVerticalLayout"));
        centralWidgetVerticalLayout->setContentsMargins(0, 0, 0, 0);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 817, 23));
        flieMenu = new QMenu(menuBar);
        flieMenu->setObjectName(QStringLiteral("flieMenu"));
        viewMenu = new QMenu(menuBar);
        viewMenu->setObjectName(QStringLiteral("viewMenu"));
        MainWindowClass->setMenuBar(menuBar);
        dockWidget_library = new QDockWidget(MainWindowClass);
        dockWidget_library->setObjectName(QStringLiteral("dockWidget_library"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        dockWidget_library->setWidget(dockWidgetContents);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_library);
        dockWidget_itemList = new QDockWidget(MainWindowClass);
        dockWidget_itemList->setObjectName(QStringLiteral("dockWidget_itemList"));
        dockWidgetContents_itemList = new QWidget();
        dockWidgetContents_itemList->setObjectName(QStringLiteral("dockWidgetContents_itemList"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_itemList);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        treeWidget_itemList = new QTreeWidget(dockWidgetContents_itemList);
        treeWidget_itemList->setObjectName(QStringLiteral("treeWidget_itemList"));

        verticalLayout_2->addWidget(treeWidget_itemList);

        dockWidget_itemList->setWidget(dockWidgetContents_itemList);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_itemList);
        dockWidget_propertyTree = new QDockWidget(MainWindowClass);
        dockWidget_propertyTree->setObjectName(QStringLiteral("dockWidget_propertyTree"));
        dockWidgetContents_propertyTree = new QWidget();
        dockWidgetContents_propertyTree->setObjectName(QStringLiteral("dockWidgetContents_propertyTree"));
        verticalLayout_propertyTree = new QVBoxLayout(dockWidgetContents_propertyTree);
        verticalLayout_propertyTree->setObjectName(QStringLiteral("verticalLayout_propertyTree"));
        verticalLayout_propertyTree->setContentsMargins(0, 0, 0, 0);
        dockWidget_propertyTree->setWidget(dockWidgetContents_propertyTree);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_propertyTree);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindowClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(flieMenu->menuAction());
        menuBar->addAction(viewMenu->menuAction());
        flieMenu->addAction(action_new);
        flieMenu->addAction(action_open);
        flieMenu->addAction(action_save);
        flieMenu->addAction(action_close);
        viewMenu->addAction(actionPreview);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0));
        action_new->setText(QApplication::translate("MainWindowClass", "New", 0));
        action_new->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+N", 0));
        action_open->setText(QApplication::translate("MainWindowClass", "Open", 0));
        action_open->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0));
        action_close->setText(QApplication::translate("MainWindowClass", "Close", 0));
        action_close->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+C", 0));
        action_save->setText(QApplication::translate("MainWindowClass", "Save", 0));
        action_save->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", 0));
        actionPreview->setText(QApplication::translate("MainWindowClass", "Preview", 0));
        flieMenu->setTitle(QApplication::translate("MainWindowClass", "File", 0));
        viewMenu->setTitle(QApplication::translate("MainWindowClass", "View", 0));
        dockWidget_library->setWindowTitle(QApplication::translate("MainWindowClass", "Library", 0));
        dockWidget_itemList->setWindowTitle(QApplication::translate("MainWindowClass", "Object Struct", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_itemList->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindowClass", "ClassName", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindowClass", "Name", 0));
        dockWidget_propertyTree->setWindowTitle(QApplication::translate("MainWindowClass", "Property Struct", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindowClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
