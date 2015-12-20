#include "librarytree.h"


LibraryTree::LibraryTree(QWidget *parent)
	: QTreeWidget(parent)
{
	QStringList _typeList = ItemFactory::getInstance().itemTypeList();
	QTreeWidgetItem *_topItem;
	_topItem = new QTreeWidgetItem(QStringList() << "Items");
	Qt::ItemFlags _flag = _topItem->flags();
//	_flag &= ~Qt::ItemIsDragEnabled;
	_flag = _flag&~Qt::ItemIsDragEnabled;
	_topItem->setFlags(_flag);
	for each (QString _type in _typeList)
	{
		QTreeWidgetItem* _item = new QTreeWidgetItem(_topItem, QStringList() << _type);
	}
	addTopLevelItem(_topItem);

	QTreeWidgetItem *_pageTopItem;
	_pageTopItem = new QTreeWidgetItem(QStringList() << "Pages");
	_pageTopItem->setFlags(_flag);
	QTreeWidgetItem *_pageItem;
	_pageItem = new QTreeWidgetItem(_pageTopItem, QStringList() << "Page");


	addTopLevelItem(_pageTopItem);

	setDragEnabled(true);
	this->expandAll();
}

LibraryTree::~LibraryTree()
{

}

