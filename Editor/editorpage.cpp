#include "editorpage.h"
#include <QPainter>
#include <QPen>
#include <QMetaObject>
#include <QMetaProperty>
#include "QStringAndQVariant.h"
#include "PageEventHandler.h"
#include "editorscene.h"
#include <ResourceMgr.h>


EditorPage::EditorPage(const QString &id)
	:m_parentPage(NULL), m_size(100.0, 100.0), m_backColor(100, 100, 100, 100),
	m_frameColor(100, 100, 100, 100), m_frameWidth(1), m_eventHander(NULL)
{
	setHandlesChildEvents(false);//子Item 可能响应事件
	this->setSize(m_size);
	this->setObjectName(id);
	update();
}

EditorPage::~EditorPage()
{
	foreach(EditorPage *_p, m_subPages)
	{
		this->removeSubPage(_p);
		delete _p;
	}

	foreach(ItemBase *_item, m_items)
	{
		this->removeItem(_item);
		delete _item;
	}
	delete m_eventHander;
}

void EditorPage::addSubPage(EditorPage *p)
{
	p->hide();

	m_subPages.append(p);
	p->setParentPage(this);

	this->addToGroup(p);
}

void EditorPage::setBackgroundPixmap(const QString &pName)
{
	m_backPixmap = QPixmap(ResourceMgr::getInstance().abstractFileName(pName));
	m_backPixmapName = pName;
}

void EditorPage::removeSubPage(const QString &id)
{
	foreach(EditorPage *_p, m_subPages)
	{
		if (_p->getId() == id)
		{
			removeSubPage(_p);
			return;
		}
	}

}

void EditorPage::removeSubPage(EditorPage *p)
{
	if (!m_subPages.contains(p))
	{
		return;
	}

	m_subPages.removeOne(p);
	this->removeFromGroup(p);
}

ItemBase *EditorPage::getItemByName(const QString &name)
{
	foreach(ItemBase *_item, m_items)
	{
		if (_item->getName() == name)
		{
			return _item;
		}
	}
	return NULL;
}

EditorPage *EditorPage::getSubPage(const QString &id)
{
	foreach(EditorPage *p, m_subPages)
	{
		if (p->getId() == id)return p;
	}
	qDebug() << "Can't find page with id=" << id;
	return NULL;
}

void EditorPage::addItem(ItemBase *_item)
{
	if (m_items.contains(_item))
		return;
	this->addToGroup(_item);
	m_items.append(_item);
	_item->m_page = this;
}

void EditorPage::removeItem(ItemBase *_item)
{
	qDebug() << "removeItem head";
	if (m_items.indexOf(_item) > -1)
	{
		m_items.removeOne(_item);
		this->removeFromGroup(_item);
		_item->m_page = NULL;
	}
	qDebug() << "removeItem end";
}

QStringList EditorPage::getSubPageNames()
{
	QStringList _list;
	foreach(EditorPage *_sp, m_subPages)
	{
		_list << _sp->getId();
	}
	return _list;
}

QRectF EditorPage::boundingRect() const
{
	if (m_size.isNull())
	{
		return QGraphicsItemGroup::boundingRect();
	}
	else
	{
		return QRectF(QPointF(0.0, 0.0), m_size);
	}

}

void EditorPage::showPageByFullName(EditorPage *p, QStringList &_idlist)
{
	if (!p)return;

	if (_idlist.isEmpty())
	{
		foreach(EditorPage *_sp, p->m_subPages)
		{
			_sp->setVisible(false);
		}
		return;
	}


	QString _cpName = _idlist.takeFirst();
	EditorPage *_subPage = NULL;
	foreach(EditorPage *_sp, p->m_subPages)
	{
		if (_sp->getId() == _cpName)
		{
			_sp->setVisible(true);
			_subPage = _sp;
		}
		else
		{
			_sp->setVisible(false);
		}
	}

	if (_subPage)
	{
		showPageByFullName(_subPage, _idlist);
	}
	else
	{
		qDebug() << "ERROR:Cann't find sub page" << _cpName << " in page " << getId();
	}


}

void EditorPage::goToGenerationPage(const QString &ids)
{
	QStringList _idlist = ids.split(".");

	showPageByFullName(this, _idlist);
}

QString EditorPage::getFullName()
{
	EditorPage *_p = this->getParentPage();
	if (_p)
	{
		return _p->getFullName() + "." + this->getId();
	}
	return this->getId();
}

void EditorPage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */)
{
//	qDebug() << "EditorPage::paint";
	QPen _pen;
	_pen.setColor(m_frameColor);
	_pen.setWidth(m_frameWidth);
	painter->setPen(_pen);
	painter->setBrush(m_backColor);
	painter->drawRect(boundingRect());

	if (!m_backPixmap.isNull())
	{
		painter->drawPixmap(boundingRect(), m_backPixmap, m_backPixmap.rect());
	}

	painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
	QRectF _rect = boundingRect();

	painter->setPen((m_backColor.alpha() == 0) ? QColor(0, 0, 0, 0) : m_backColor.darker(50));
	painter->setBrush(m_backColor);
	painter->drawRect(boundingRect());

	painter->setPen((m_backColor.alpha() == 0) ? QColor(0, 0, 0, 0) : m_backColor.darker(50));
	painter->drawLine(_rect.bottomLeft(), _rect.topLeft());
	painter->drawLine(_rect.topLeft(), _rect.topRight());

	painter->setPen((m_backColor.alpha() == 0) ? QColor(0, 0, 0, 0) : m_backColor.lighter(50));
	painter->drawLine(_rect.bottomLeft(), _rect.bottomRight());
	painter->drawLine(_rect.bottomRight(), _rect.topRight());

}

void EditorPage::commonEventReceive(const QString &eInfo)
{
	if (m_eventHander)
	{
		m_eventHander->commonEventReceive(this, eInfo);
	}
}

void EditorPage::commonEventRelease(const QString &eInfo)
{
	if (m_eventHander)
	{
		m_eventHander->commonEventRelease(this, eInfo);
	}
}

void EditorPage::tick(int ms)
{
	if (m_eventHander)
	{
		m_eventHander->tick(this, ms);
	}
}

EditorScene *EditorPage::getEditorScene() const
{
	QGraphicsScene *_scene = this->scene();
	return dynamic_cast<EditorScene *>(_scene);
}

QVariant EditorPage::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant & value)
{
	switch (change)
	{
		case QGraphicsItem::ItemVisibleChange:
			{
				bool _isVisible = value.value<bool>();
				if (_isVisible && m_eventHander)
				{
					m_eventHander->pageAboutToShow(this);
				}
			}
		case QGraphicsItem::ItemVisibleHasChanged:
			{
				bool _isVisible = value.value<bool>();
				if (!_isVisible && m_eventHander)
				{
					m_eventHander->pageHasHide(this);
				}
			}
	}
	return QGraphicsItem::itemChange(change, value);
}

QString EditorPage::toXml() const
{
	QString _str = QString("     {\n        \"type\":\"page\",\n        \"name\": \"%1\",\n").arg(this->getId());

	//保存除ID之外的属性

	const QMetaObject *_mo = this->metaObject();
	int _count = _mo->propertyCount();
	_str += "        \"property\": [";
	for (int i = 0; i < _count; ++i)
	{
		QString _pName = _mo->property(i).name();
		if (_pName == "objectName")continue;//objectName作为ID记录，此处忽略
		QVariant _value = this->property(_pName.toStdString().c_str());
		_str += QString("\n            { \"type\": \"%1\", \"name\": \"%2\", \"value\": \"%3\" }").arg(int(_value.type())).arg(_pName).arg(QStringAndQVariant::vairantToString(_value));
		if (i != _count - 1)
		{
			_str += ",";
		}
//		_str += QString("<property type=\"%1\" name=\"%2\" value=\"%3\"/>").arg(int(_value.type())).arg(_pName).arg(QStringAndQVariant::vairantToString(_value));
	}
	_str += "],\n";


	//保存item
	_str += "        \"sub item\": [";//sub item property
	foreach(ItemBase *_ib, m_items)
	{
		_str += _ib->toXml();
	}
	_str += "        ],\n";//sub item property


	//子页面
	_str += "        \"sub page\": [";//sub page property
	foreach(EditorPage *p, m_subPages)
	{
		_str += p->toXml();
	}
	_str += "        ],\n";//sub page property

	_str += "            },\n";

	return _str;
}

void EditorPage::driveTick(int ms)
{
	tick(ms);

	foreach(ItemBase *_item, m_items)
	{
		_item->tick(ms);
	}

	foreach(EditorPage *_sp, m_subPages)
	{
		_sp->driveTick(ms);
	}
}