#include "EditorView.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTreeWidgetItem>
#include <QDropEvent>
#include <QClipboard>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QDomElement>
#include <QDomDocument>
#include <QFileInfo>
#include <QStringAndQVariant.h>
#include "EditorPage.h"
#include "ItemFactory.h"
#include "SelectItemProxy.h"
#include "EditorScene.h"
void setObjectProperty(QObject *obj, const QDomElement&pe);

void initItemFromXml(ItemBase *_seItem, const QDomElement&itemE);

EditorView::EditorView(QWidget * parent) :
EditorViewBase(parent, false), m_selectItemProxy(new SelectItemProxy)
{
	this->setAcceptDrops(true);
	this->setFrameShape(QFrame::StyledPanel);

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);


}

EditorView::~EditorView(void)
{
}

void EditorView::createScene(const QString &screenName)
{
	EditorScene *_scene = new EditorScene(screenName);
	this->setEditorScene(_scene);
	_scene->setSceneName(QFileInfo(screenName).baseName());

}

void EditorView::loadScene(const QString &sceneFile)
{
	qDebug() << "EditorView::loadScene";
	EditorScene *_scene = getEditorScene();
	EditorScene *_newScene = new EditorScene(sceneFile);
	this->setEditorScene(_newScene);
	QString _newSceneFile = QFileInfo(sceneFile).baseName();
	if (_newScene->getSceneName() != _newSceneFile)
	{
		_newScene->setSceneName(_newSceneFile);
	}

	if (_scene)
	{
		_scene->removeItem(m_selectItemProxy);
		delete _scene;
	}
}

void EditorView::dragEnterEvent(QDragEnterEvent * event)
{
	qDebug() << "dragEnterEvent";
	event->accept();
}

void EditorView::dragMoveEvent(QDragMoveEvent *event)
{
	event->accept();
}

void EditorView::dropEvent(QDropEvent *event)
{
	qDebug() << "QDropEvent* event";
	const QMimeData *_md = event->mimeData();
	QTreeWidget *_tree = dynamic_cast<QTreeWidget *>(event->source());
	QString _className;
	if (_tree)
	{
		QTreeWidgetItem *_item = _tree->currentItem();
		if (_item)
		{
			_className = _item->text(0);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	EditorScene *_scene = this->getEditorScene();

	if (!_scene)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请先创建屏。"));
		return;
	}

	if (_className == "Page")
	{
		EditorPage *_cp = _scene->getRootPage()->getCurrentPage();
		QString _newId = QString("EditorPage_%1").arg(_cp->getSubPageNames().size());
		EditorPage *_newPage = new EditorPage(_newId);
		_cp->addSubPage(_newPage);

		_cp->goToSubPageById(_newId);

	}
	else
	{
		EditorPage *_cp = _scene->getRootPage()->getCurrentPage();

		ItemBase *_item = ItemFactory::getInstance().createItem(_className);
		_item->setName(_className.toLower());
		_cp->addItem(_item);
		//先添加到页面再设置位置
		QPointF _p = _cp->mapFromScene(this->mapToScene(event->pos()));
		_item->setPos(_p.x(), _p.y());
		m_selectItemProxy->setHMIItem(_item);
		emit selectItemChanged((QObject*)_item);
	}

	emit newItemByDrag();
}

void EditorView::delSelectItem()
{
	ItemBase *_current = m_selectItemProxy->getHMIItem();
	if (!_current)
	{
		return;
	}

	m_selectItemProxy->setHMIItem(NULL);

	//_current->
	EditorPage *_page = _current->getPage();
	_page->removeItem(_current);
	delete _current;
}

ItemBase *EditorView::getSelectItem() const
{
	if (!m_selectItemProxy) return NULL;
	return m_selectItemProxy->getHMIItem();
}

void EditorView::setSelectItem(ItemBase *item)
{
	if (!m_selectItemProxy) return;
	m_selectItemProxy->setHMIItem(item);
}

void EditorView::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	setSceneRect(this->rect());
}

void EditorView::mousePressEvent(QMouseEvent *event)
{
	QGraphicsView::mousePressEvent(event);
	QList<QGraphicsItem *> _items = this->items(event->pos());
	foreach(QGraphicsItem *_item, _items)
	{
		if (_item == m_selectItemProxy)//选中操纵器
		{
			return;
		}

		ItemBase *_hmiItem = dynamic_cast<ItemBase *>(_item);
		if (_hmiItem)
		{
			m_selectItemProxy->setHMIItem(_hmiItem);
			emit selectItemChanged(_hmiItem);
			return;
		}

		EditorPage *_page = dynamic_cast<EditorPage *>(_item);
		if (_page)
		{
			m_selectItemProxy->setHMIItem(NULL);
			emit selectItemChanged(_page);
			return;
		}
	}

	m_selectItemProxy->setHMIItem(NULL);
	emit selectItemChanged(NULL);

}
// #include "RotateOperatorEditDialog.h"
// #include "StraightOperatorEditDialog.h"

void EditorView::keyPressEvent(QKeyEvent * event)
{
	QGraphicsView::keyPressEvent(event);
	if (!event->isAutoRepeat())this->setDragMode(QGraphicsView::ScrollHandDrag);
}

void EditorView::keyReleaseEvent(QKeyEvent * event)
{
	QGraphicsView::keyReleaseEvent(event);
	if (!event->isAutoRepeat())this->setDragMode(QGraphicsView::NoDrag);
}

void EditorView::mouseDoubleClickEvent(QMouseEvent * event)
{
	QGraphicsView::mouseDoubleClickEvent(event);
	QList<QGraphicsItem *> _items = this->items(event->pos());
// 	foreach(QGraphicsItem *_item, _items)
// 	{
// 		HMIRotateOperator *_roItem = dynamic_cast<HMIRotateOperator *>(_item);
// 		if (_roItem)
// 		{
// 			RotateOperatorEditDialog _setDialog(this);
// 			_setDialog.setJiWei(_roItem->getJiwei());
// 			if (_setDialog.exec() == QDialog::Accepted)
// 			{
// 				_roItem->setJiwei(_setDialog.getJiweis());
// 			}
// 			break;
// 		}
// 
// 		HMIStraightOperator *_soItem = dynamic_cast<HMIStraightOperator *>(_item);
// 		if (_soItem)
// 		{
// 			StraightOperatorEditDialog _setDialog(this);
// 			_setDialog.setJiWei(_soItem->getJiwei());
// 			if (_setDialog.exec() == QDialog::Accepted)
// 			{
// 				_soItem->setJiwei(_setDialog.getJiweis());
// 			}
// 			break;
// 
// 		}
// 
// 		HMIListItem* _li = dynamic_cast<HMIListItem*>(_item);
// 		if (_li)
// 		{//找到类名为HMIListItem的item
// 
// 			ListItem m_listItemEditDialog;
// 
// 			m_listItemEditDialog.addItems(_li->getTextStrList());
// 
// 			m_listItemEditDialog.exec();
// 
// 			bool _bIscancel = m_listItemEditDialog.getCancelButton();
// 			if (!_bIscancel)
// 			{
// 				QStringList _textListAfter = m_listItemEditDialog.getItemTextList();
// 				_li->addItems(_textListAfter);
// 			}
// 
// 			break;//遍历找到最顶层的Item就行了
// 		}
// 
// 		/*HMITableWidgetItems*/
// 
// 		HMITableWidgetItem* _tableWidgetItem = dynamic_cast<HMITableWidgetItem*>(_item);
// 		if (_tableWidgetItem)
// 		{
// 			addtablewidgetitems _addtableItems(this);
// 			_addtableItems.resetTableWidget(_tableWidgetItem->getTableWidget());
// 			_addtableItems.updateWidgetButtons();
// 			_addtableItems.exec();
// 			if (_addtableItems.isOkButtonClicked())
// 			{
// 				_tableWidgetItem->setTableWidget(_addtableItems.getTableWidgetItems());
// 			}
// 			break;
// 		}
// 	}
}

void EditorView::copyItem()
{
	if (!m_selectItemProxy)
		return;
	ItemBase *_currentItem = m_selectItemProxy->getHMIItem();
	if (!_currentItem)
		return;

	QClipboard *clipboard = qApp->clipboard();
	if (!clipboard) return;
	clipboard->setText(_currentItem->toXml());
}

void EditorView::pasteItem()
{
// 	QClipboard *clipboard = qApp->clipboard();
// 	if (!clipboard) return;
// 
// 	QString _txt = clipboard->text();
// 	if (_txt.isEmpty()) return;
// 
// 	EditorScene *_scene = this->getEditorScene();
// 	if (!_scene)
// 	{
// 		return;
// 	}
// 	EditorPage *_rootp = _scene->getRootPage();
// 	if (!_rootp || !_rootp->getCurrentPage())
// 	{
// 		return;
// 	}
// 
// 	QDomDocument _doc("item");
// 	if (!_doc.setContent(_txt))
// 		return;
// 
// 	QDomElement _e = _doc.firstChildElement("item");
// 
// 	if (_e.isNull()) return;
// 
// 	QString _className = _e.attribute("calssName");
// 	ItemBase *_item = ItemFactory::getInstance().createItem(_className);
// 	if (_item)
// 	{
// 		_rootp->getCurrentPage()->addItem(_item);
// 		initItemFromXml(_item, _e);
// 		//_item->setPos(_item->pos() * 1.2);
// 		m_selectItemProxy->setHMIItem(_item);
// 		emit selectItemChanged(_item);
// 		emit newItemByDrag();
// 	}


}

void EditorView::editScriptForPage(ItemBase *item)
{

}

void EditorView::delScriptForPage(ItemBase *item)
{

}