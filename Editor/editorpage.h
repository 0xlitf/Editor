#ifndef EDITORPAGE_H
#define EDITORPAGE_H

#include "itembase.h"

#include <QObject>
#include <QGraphicsItemGroup>
#include <QDebug>

class PageEventHandler;
class EditorScene;
class EditorPage : public QObject,public QGraphicsItemGroup
{
	Q_OBJECT
		Q_PROPERTY(QPointF pos READ pos WRITE setPos)
		Q_PROPERTY(QSizeF size READ getSize WRITE setSize)
		Q_PROPERTY(QColor BackColor READ backColor WRITE setBackColor)
		Q_PROPERTY(QColor FrameColor READ frameColor WRITE setFrameColor)
		Q_PROPERTY(int FrameWidth READ frameWidth WRITE setFrameWidth)
		Q_PROPERTY(QString BackgroundPixmap READ getBackgroundPixmap WRITE setBackgroundPixmap)
public:
	EditorPage(const QString &id);
	~EditorPage();


	/************************************************************************/
	/* �����ҳ��
	/************************************************************************/
	void addSubPage(EditorPage *p);

	/************************************************************************/
	/* �Ƴ���ҳ��
	/************************************************************************/
	void removeSubPage(const QString &id);
	void removeSubPage(EditorPage *p);

	/************************************************************************/
	/* �õ���ҳ��
	/************************************************************************/
	EditorPage *getParentPage()
	{
		return m_parentPage;
	}

	//�õ���ҳ��
	//tianlu 2014.9.10
	EditorPage *getSubPage(const QString &id);

	QStringList getSubPageNames();

	QString getFullName();

	/************************************************************************/
	/* �õ�����ҳ��
	/************************************************************************/
	EditorPage *getAncestor()
	{
		EditorPage *_p = getParentPage();
		if (!_p)//û�и���ʱ���Լ�������
		{
			return this;
		}

		while (_p->getParentPage())
		{
			_p = _p->getParentPage();

		}
		return _p;
	}





	/************************************************************************/
	/* �õ���ǰ�ҳ��
	/************************************************************************/
	EditorPage *getCurrentPage()
	{
		if (this->isVisible())
		{
			foreach(EditorPage *_sp, m_subPages)
			{
				if (_sp->isVisible())
				{
					return _sp->getCurrentPage();
				}
			}
			return this;
		}
		else
		{
			return NULL;
		}
	}


	/************************************************************************/
	/* ����ҳ���ID��Ҳ������������ΪID
	/************************************************************************/
	virtual QString getId() const{ return objectName(); }

	void setId(const QString &id){ this->setObjectName(id); }

	virtual void DataRefresh(){}

	/************************************************************************/
	/* ��ʾ��ҳ�棨��ID��ʾ��
	/************************************************************************/
	void goToSubPageById(const QString &id)
	{
		EditorPage *_tp = NULL;
		foreach(EditorPage *p, m_subPages)
		{
			if (p->getId() == id)_tp = p;
		}
		if (!_tp)
		{
			qDebug() << "Can't find page with id=" << id;
			return;
		}

		closeGenerationPage();
		qDebug() << "show" << _tp->getId() << this->getId() << this->isVisible();
		_tp->setVisible(true);
		update();
	}

	//�ر����к����ҳ��

	void closeGenerationPage()
	{
		foreach(EditorPage *p, m_subPages)
		{
			p->closeGenerationPage();

			p->setVisible(false);
		}
	}

	/************************************************************************/
	/* ֱ����ת���ƶ��ĺ��ҳ�棬ids�ַ���������id���ӣ��á�.���ָ�
	/************************************************************************/
	void goToGenerationPage(const QString &ids);

	/************************************************************************/
	/* ��ҳ����ʾʱ��������Χ�����Ὣ��Ϣ���ݸ�ҳ�����
	/************************************************************************/
	virtual void commonEventReceive(const QString &eInfo);

	/************************************************************************/
	/* ��ҳ����ʾʱ���ɿ���Χ�����Ὣ��Ϣ���ݸ�ҳ�����
	/************************************************************************/
	virtual void commonEventRelease(const QString &eInfo);

	void addItem(ItemBase *_item);

	void removeItem(ItemBase *_item);

	int itemCount() const
	{
		return m_items.size();
	}

	ItemBase *getItemByName(const QString &name);



	ItemBase *getItemByIndex(int index)
	{
		if (index < 0 || index >= m_items.size()) return NULL;

		return m_items.at(index);
	}

	QString toXml() const;

	void setSize(const QSizeF &size){ m_size = size; }
	QSizeF getSize() const{ return m_size; }

	QColor backColor() { return m_backColor; }
	void setBackColor(const QColor &c){ m_backColor = c; }

	QColor frameColor() { return m_frameColor; }
	void setFrameColor(const QColor &c){ m_frameColor = c; }

	int frameWidth() const { return m_frameWidth; }
	void setFrameWidth(int w){ m_frameWidth = w; }

	QRectF boundingRect() const;

	void setBackgroundPixmap(const QString &pName);
	QString getBackgroundPixmap() const { return m_backPixmapName; }

//	void setEventHandler(PageEventHandler *eh){ m_eventHander = eh; }

	EditorScene *getEditorScene() const;

protected:
	friend class EditorScene;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	void driveTick(int ms);
	virtual void tick(int ms);

	QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant & value);



private:
	void setParentPage(EditorPage *pp){ m_parentPage = pp; }
	void showPageByFullName(EditorPage *p, QStringList &_idlist);

	QSizeF m_size;
	QColor m_backColor;
	QColor m_frameColor;
	int m_frameWidth;

	QString m_backPixmapName;
	QPixmap m_backPixmap;

	EditorPage *m_parentPage;      //
	QList<EditorPage*> m_subPages;

	QList<ItemBase *> m_items;

	PageEventHandler *m_eventHander;

};

#endif // EDITORPAGE_H
