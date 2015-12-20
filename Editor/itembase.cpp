#include "itembase.h"
#include "editorscene.h"
#include "QStringAndQVariant.h"

ItemBase::ItemBase(QGraphicsItem * parent) :
QObject(), QGraphicsItem(parent), m_page(NULL), m_size(40, 20), m_visible(true)
{
}

ItemBase::~ItemBase(void)
{
}

QString ItemBase::className() const
{
	const QMetaObject *_mo = this->metaObject();
	if (_mo) return _mo->className();
	return "";
}
void ItemBase::addChildItem(ItemBase *ci)
{
	if (m_childItems.indexOf(ci) > -1)
	{
		return;
	}

	ci->setParentItem(this);

	m_childItems.append(ci);
}

int ItemBase::type() const
{
	return ItemBase::ItemBaseType;
}
QRectF ItemBase::boundingRect() const
{
	return QRectF(QPointF(0.0, 0.0), m_size);
}

QString ItemBase::toXml() const
{
	const QMetaObject *_mo = this->metaObject();

	QString _str = QString("    {\n        \"type\":\"item\",\n        \"className\": \"%1\",\n        \"itemName\" : \"%2\",\n").arg(_mo->className()).arg(getName());

	int _count = _mo->propertyCount();
	_str += "        \"property\": [";
	for (int i = 0; i < _count; ++i)
	{
		QString _pName = _mo->property(i).name();
		if (_pName == "objectName")continue;//objectName作为itemName记录，此处忽略
		QVariant _value = this->property(_pName.toStdString().c_str());
		_str += QString("\n            {\"type\": \"%1\", \"name\": \"%2\", \"value\": \"%3\" }").arg(int(_value.type())).arg(_pName).arg(QStringAndQVariant::vairantToString(_value));
		if (i != _count - 1)
		{
			_str += ",";
		}
	}

	_str += "],\n";
	_str += "            },\n";
	return _str;

}

EditorScene *ItemBase::getEditorScene()
{
	QGraphicsScene *_screen = scene();
	if (_screen)
	{
		return dynamic_cast<EditorScene *>(_screen);
	}
	return NULL;

}