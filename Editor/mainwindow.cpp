#include "mainwindow.h"
#include <QVBoxLayout>
#include "editorscene.h"
#include <QFileDialog>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_isANewFile(true), m_fileIsSaved(true)
{
	ui.setupUi(this);
	setWindowIcon(QIcon("pencil-square-o.png"));
	setupLibraryTree();
	setupListItem();
	setupMenuBar();
	setupToolBar();
	setupPropertyTree();
	setupCentralWidget();
	createNewScreenFile();
	showMaximized();
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateItemList(){
	qDebug() << "MainWindow::updateItemList";
	while (ui.treeWidget_itemList->topLevelItemCount() > 0)
	{
		delete ui.treeWidget_itemList->takeTopLevelItem(0);
	}
	EditorScene *_screen = m_editorView->getEditorScene();
	QString _sName = _screen->objectName();
	QString _className = _screen->metaObject()->className();

	QTreeWidgetItem *_topItem = new QTreeWidgetItem(QStringList() << _sName << _className);
	_topItem->setData(0, Qt::UserRole, int(_screen));

	EditorPage *_rootPage = _screen->getRootPage();
	updatePageList(_topItem, _rootPage);

	ui.treeWidget_itemList->addTopLevelItem(_topItem);
	ui.treeWidget_itemList->expandAll();

}

void MainWindow::updatePageList(QTreeWidgetItem *_item, EditorPage *_p){
	qDebug() << "MainWindow::updatePageList";
	if (!_item || !_p)
	{
		return;
	}
	QString _id = _p->getId();
	QString _className = _p->metaObject()->className();

	QTreeWidgetItem *_pItem = new QTreeWidgetItem(QStringList() << _id << _className);
	_pItem->setData(0, Qt::UserRole, int(_p));
	_item->addChild(_pItem);

	QStringList _SubPNamelist = _p->getSubPageNames();
	for each (QString _sId in _SubPNamelist)
	{
		EditorPage *_subp = _p->getSubPage(_sId);
		updatePageList(_pItem, _subp);
	}
	int _itemcount = _p->itemCount();
	for (int i = 0; i < _itemcount; ++i)
	{
		ItemBase *_seIB = _p->getItemByIndex(i);

		QTreeWidgetItem *_seIBItem = new QTreeWidgetItem(QStringList() << _seIB->getName() << _seIB->metaObject()->className());
		_seIBItem->setData(0, Qt::UserRole, int(_seIB));
		_pItem->addChild(_seIBItem);
	}
}

void MainWindow::on_action_new_triggered(){
	if (!m_fileIsSaved)
	{
		QMessageBox *_msgBox=new QMessageBox;
		QPushButton *yes = _msgBox->addButton(QString::fromLocal8Bit("yes"), QMessageBox::YesRole);
		QPushButton *no = _msgBox->addButton(QString::fromLocal8Bit("no"), QMessageBox::NoRole);
		QPushButton *cancel = _msgBox->addButton(QMessageBox::Cancel);
		_msgBox->setText("this file is not saved,\ndo you want to save it?");
		_msgBox->exec();
		if (_msgBox->clickedButton() == yes)
		{
			on_action_save_triggered();
			m_fileIsSaved = true;
		}
		if (_msgBox->clickedButton() == no)
		{
			createNewScreenFile();
		}
		if (_msgBox->clickedButton() == cancel)
		{
		}
		return;
	}
	else
	{
		createNewScreenFile();
	}
}

void MainWindow::on_action_open_triggered(){
	m_fileIsSaved = true;
	QString _pn = QFileDialog::getOpenFileName(this, "open", "./", "(*.json);;(*.*)");
	if (_pn.isEmpty())
		return;
	m_currentFileName = _pn;
	setWindowTitle(_pn);
	m_editorView->loadScene(_pn);
	m_screenFileName = _pn;
	updateItemList();
	ui.treeWidget_itemList->setCurrentItem(ui.treeWidget_itemList->topLevelItem(NULL));
}

void MainWindow::on_action_close_triggered(){
	on_action_new_triggered();
}

void MainWindow::on_action_save_triggered(){
	if (!m_fileIsSaved)
	{
		QString _fileName = QFileDialog::getSaveFileName(this, "save file", "./" + m_currentFileName, "screen files(*.json)");
	}
	if ((!QFile::exists(m_currentFileName)))
	{
		return;
	}
	EditorScene *_scene = m_editorView->getEditorScene();
	if (_scene)
	{
		if (!_scene->saveSceneFile(m_screenFileName))
		{
			QMessageBox::warning(this, "warning", QString::fromLocal8Bit("failed"));
		}
		m_isANewFile = false;
		m_fileIsSaved = true;
	}
}

void MainWindow::on_actionPreview_triggered(){

}

void MainWindow::setupLibraryTree(){
	LibraryTree *libraryTree;
	libraryTree = new LibraryTree(ui.dockWidget_library);
	ui.dockWidget_library->setWidget(libraryTree);
}

void MainWindow::setupListItem(){
	ui.treeWidget_itemList->setCurrentItem(ui.treeWidget_itemList->topLevelItem(0));//加上本行，否则第一个原件属性不显示 2015年8月12日16:05:47
}

void MainWindow::setupMenuBar(){

}

void MainWindow::setupToolBar(){

	ui.action_new->setIcon(QIcon("64file.png"));
	ui.action_open->setIcon(QIcon("64folder-open.png"));
	ui.action_save->setIcon(QIcon("save.png"));
	ui.action_close->setIcon(QIcon("close.png"));
	ui.actionPreview->setIcon(QIcon("64play.png"));

	ui.toolBar->addAction(ui.action_new);
	ui.toolBar->addAction(ui.action_open);
	ui.toolBar->addAction(ui.action_save);
	ui.toolBar->addAction(ui.action_close);
	ui.toolBar->addAction(ui.actionPreview);
}

void MainWindow::setupPropertyTree(){
	m_propertyBrwoser = new PropertyBrowser(ui.dockWidgetContents_propertyTree);
	ui.verticalLayout_propertyTree->addWidget(m_propertyBrwoser);
}

void MainWindow::setupCentralWidget(){

	m_editorView = new EditorView(ui.centralWidget);
	ui.centralWidgetVerticalLayout->addWidget(m_editorView);
	connect(m_editorView, SIGNAL(newItemByDrag()), SLOT(onItemCreated()));
	connect(m_editorView, SIGNAL(selectItemChanged(QObject *)), SLOT(onSelectItemChangedInView(QObject *)));
}

void MainWindow::onItemCreated()
{
	this->updateItemList();
}

void MainWindow::onSelectItemChangedInView(QObject *obj)
{
	qDebug() << "MainWindow::onSelectItemChangedInView";
	m_propertyBrwoser->setCurrentObject(obj);
	m_fileIsSaved = false;
}

void MainWindow::on_treeWidget_itemList_currentItemChanged(QTreeWidgetItem * current, QTreeWidgetItem * previous)
{
	qDebug() << "MainWindow::on_treeWidget_itemList_currentItemChanged";
	if (current)
	{
		QObject *_obj = (QObject *)current->data(0, Qt::UserRole).toInt();

		m_propertyBrwoser->setCurrentObject(_obj);

		ItemBase *_item = dynamic_cast<ItemBase *>(_obj);
		if (_item)
		{
			m_editorView->setSelectItem(_item);
		}
		else
		{
			EditorPage *_p = dynamic_cast<EditorPage *>(_obj);
			if (_p) //设置为当前页面
			{
				EditorPage *_ancP = _p->getAncestor();
				if (_p == _ancP)
				{
					_p->closeGenerationPage();
				}
				else
				{
					QString _fname = _p->getFullName();
					QStringList _names = _fname.split(".");
					_names.takeFirst();
					_ancP->goToGenerationPage(_names.join("."));
				}

			}

		}
	}
	else
	{
		m_propertyBrwoser->setCurrentObject(NULL);
		qDebug() << "PropertyBrowser::setCurrentObject(NULL)";

	}
}

void MainWindow::createNewScreenFile(){
	int i = 0;
	QString _fileName = "blankpage_" + QString::number(i) + ".json";
	if (m_fileIsSaved || m_isANewFile)
	{
		while (QFile::exists(_fileName))
		{
			++i;
			_fileName = "blankpage_" + QString::number(i) + ".json";
		}
	}

	setWindowTitle(_fileName);
	m_isANewFile = true;
	m_editorView->createScene(_fileName);
	m_editorView->getEditorScene()->setSceneName(_fileName);
	m_currentFileName = _fileName;
	m_screenFileName = _fileName;
	updateItemList();
}
