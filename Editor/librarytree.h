#ifndef LIBRARYTREE_H
#define LIBRARYTREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "itemfactory.h"
class LibraryTree : public QTreeWidget
{
	Q_OBJECT

public:
	LibraryTree(QWidget *parent);
	~LibraryTree();

private:
};

#endif // LIBRARYTREE_H
