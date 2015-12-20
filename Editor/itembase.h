#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QObject>
#include <QtWidgets/QGraphicsObject>
#include <QMetaProperty>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QtSvg/QSvgRenderer>
class EditorPage;
class EditorScene;
class ItemBase : public QObject, public QGraphicsItem
{
	Q_OBJECT

		Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
		Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
		Q_PROPERTY(bool visible READ getVisible WRITE setVisible)
		Q_PROPERTY(QPointF pos READ pos WRITE setPos)
		Q_PROPERTY(QSizeF size READ getSize WRITE setSize)
		Q_PROPERTY(qreal z READ zValue WRITE setZValue)

		Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
		Q_PROPERTY(qreal scale READ scale WRITE setScale)

		Q_PROPERTY(QPointF transformOriginPoint READ transformOriginPoint WRITE setTransformOriginPoint)

public:
	enum Type{
		ItemBaseType = QGraphicsItem::UserType + 11,
		HMILabelItemType = QGraphicsItem::UserType + 12,
		HMIButtonItemType = QGraphicsItem::UserType + 13,
		HMIValueMeterType = QGraphicsItem::UserType + 14,
		HMIValuePillarType = QGraphicsItem::UserType + 15,
		HMIListItemType = QGraphicsItem::UserType + 16,
		HMIDateTimeEditType = QGraphicsItem::UserType + 17,
		HMIRadioButtonItemType = QGraphicsItem::UserType + 18,
		HMITableWidgetItemType = QGraphicsItem::UserType + 19,
		HMIWidgetItemType = QGraphicsItem::UserType + 20,
		HMIDelayButtonItemType = QGraphicsItem::UserType + 21,

		HMIStrightOperatorType = QGraphicsItem::UserType + 25,
		HMIRotateOperatorType = QGraphicsItem::UserType + 26,
		HMISetValueButtonItemType = QGraphicsItem::UserType + 27,
		HMIInputLabelItemType = QGraphicsItem::UserType + 28,
	};
	ItemBase(QGraphicsItem * parent = 0);
	~ItemBase(void);

	virtual QString className()const;

	QString getName() const{ return objectName(); }
	void setName(const QString &name){ setObjectName(name); }

	QSizeF getSize() const { return m_size; }
	virtual void setSize(const QSizeF &size){ m_size = size; }

	QRectF boundingRect() const;

	void addChildItem(ItemBase *);

	virtual QString toXml() const;

	EditorScene *getEditorScene();
	EditorPage *getPage(){ return m_page; }

	bool getVisible() const { return m_visible; }
	void setVisible(bool v){ QGraphicsItem::setVisible(v); m_visible = v; }

	int type() const;

protected:
	virtual void tick(int ms){}
	friend class EditorPage;
	EditorPage *m_page;
	QSizeF m_size;
	QList<ItemBase *> m_childItems;
	bool m_visible; //item的可见性会继承父item的，在此记录一下，保证保存的时候显示的item的visible返回true
};

#endif // ITEMBASE_H
