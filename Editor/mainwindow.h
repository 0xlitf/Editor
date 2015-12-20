#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <librarytree.h>
#include <QMessageBox>
#include "PropertyBrowser.h"
#include <editorview.h>
#include <QFile>
#include <QTime>
#include <QDebug>
#include <QDateTime>
class MainWindow : public QMainWindow
{
	Q_OBJECT
//public
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	bool m_fileIsSaved;
	bool m_isANewFile;
	QString m_currentFileName;
	void updateItemList();
	void updatePageList(QTreeWidgetItem *_item, EditorPage *_p);
	void createNewScreenFile();

//protected
	protected slots:
	void on_action_new_triggered();
	void on_action_open_triggered();
	void on_action_close_triggered();
	void on_action_save_triggered();
	void on_actionPreview_triggered();

	void onItemCreated();
	void onSelectItemChangedInView(QObject *);
	void on_treeWidget_itemList_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);


//private
private:
	void setupLibraryTree();
	void setupListItem();
	void setupMenuBar();
	void setupToolBar();
	void setupPropertyTree();
	void setupCentralWidget();

	Ui::MainWindowClass ui;
	EditorView* m_editorView;
	QString m_screenFileName;
	PropertyBrowser *m_propertyBrwoser;
};

#endif // MAINWINDOW_H
