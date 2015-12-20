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
	/* 添加子页面
	/************************************************************************/
	void addSubPage(EditorPage *p);

	/************************************************************************/
	/* 移除子页面
	/************************************************************************/
	void removeSubPage(const QString &id);
	void removeSubPage(EditorPage *p);

	/************************************************************************/
	/* 得到父页面
	/************************************************************************/
	EditorPage *getParentPage()
	{
		return m_parentPage;
	}

	//得到子页面
	//tianlu 2014.9.10
	EditorPage *getSubPage(const QString &id);

	QStringList getSubPageNames();

	QString getFullName();

	/************************************************************************/
	/* 得到祖宗页面
	/************************************************************************/
	EditorPage *getAncestor()
	{
		EditorPage *_p = getParentPage();
		if (!_p)//没有父亲时，自己当祖宗
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
	/* 得到当前活动页面
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
	/* 返回页面的ID，也可以用名称作为ID
	/************************************************************************/
	virtual QString getId() const{ return objectName(); }

	void setId(const QString &id){ this->setObjectName(id); }

	virtual void DataRefresh(){}

	/************************************************************************/
	/* 显示子页面（按ID显示）
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

	//关闭所有后代的页面

	void closeGenerationPage()
	{
		foreach(EditorPage *p, m_subPages)
		{
			p->closeGenerationPage();

			p->setVisible(false);
		}
	}

	/************************************************************************/
	/* 直接跳转到制定的后代页面，ids字符串将各代id连接，用“.”分割
	/************************************************************************/
	void goToGenerationPage(const QString &ids);

	/************************************************************************/
	/* 此页面显示时，按下外围按键会将消息传递给页面对象
	/************************************************************************/
	virtual void commonEventReceive(const QString &eInfo);

	/************************************************************************/
	/* 此页面显示时，松开外围按键会将消息传递给页面对象
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
