#include "SelectItemProxy.h"
#include "ItemBase.h"
#include <QPainter>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class SelectItemProxyDrager : public QGraphicsItem
{
public:
	enum DragDirection
	{
		NoDrag=0,
		horizontal,
		vertical,
		HorAndVer
	};

	SelectItemProxyDrager(SelectItemProxy *proxy, SelectItemProxyDrager::DragDirection dir=SelectItemProxyDrager::NoDrag):
	  QGraphicsItem(proxy),m_isPressed(false),m_direction(dir),m_proxy(proxy)
	{
		switch(m_direction)
		{
		case HorAndVer:
			this->setCursor(QCursor(Qt::SizeFDiagCursor));
			break;
		case horizontal:
			this->setCursor(QCursor(Qt::SizeHorCursor));
			break;
		case vertical:
			this->setCursor(QCursor(Qt::SizeVerCursor));
			break;
		default:
			break;
		}
	}

	QRectF boundingRect() const
	{
		double length = 5.0;
		return QRectF(-length/2.0,-length/2.0,length,length);
	}
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */)
	{
		painter->setPen(Qt::red);
		painter->setBrush(Qt::red);
		painter->drawRect(boundingRect());
	}
	void mouseMoveEvent(QGraphicsSceneMouseEvent * event )
	{
		if(m_isPressed)
		{
			QPointF currentParentPos=this->mapToParent(this->mapFromScene(event->scenePos()));
			QPointF buttonDownParentPos= this->mapToParent(this->mapFromScene(event->lastScenePos()));

			QPointF _vec=currentParentPos - buttonDownParentPos;

			switch(m_direction)
			{
			case HorAndVer:
				break;
			case horizontal:
				_vec.setY(0.0);
				break;
			case vertical:
				_vec.setX(0.0);
				break;
			default:
				_vec=QPointF(0.0,0.0);
			}

			m_proxy->resize(_vec.x(),_vec.y());
		}
		
	}
	void mousePressEvent ( QGraphicsSceneMouseEvent * event )
	{
		if(event->button() == Qt::LeftButton)
		{
			m_lastPos = this->pos();
			m_isPressed = true;
			event->accept();
		}		
	}

	void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
	{
		m_isPressed = false;
		event->accept();
	}

private:
	SelectItemProxy *m_proxy;
	bool m_isPressed;
	QPointF m_lastPos;

	DragDirection m_direction;
};

SelectItemProxy::SelectItemProxy(QGraphicsItem *parent):
QGraphicsItem(parent),m_item(NULL),m_isPressed(false)
{
	m_ltDrager = new SelectItemProxyDrager(this);
	m_tDrager = new SelectItemProxyDrager(this);
	m_rtDrager = new SelectItemProxyDrager(this);
	m_rDrager = new SelectItemProxyDrager(this,SelectItemProxyDrager::horizontal);
	m_rbDrager = new SelectItemProxyDrager(this,SelectItemProxyDrager::HorAndVer);
	m_bDrager = new SelectItemProxyDrager(this,SelectItemProxyDrager::vertical);
	m_lbDrager = new SelectItemProxyDrager(this);
	m_lDrager = new SelectItemProxyDrager(this);

}

void SelectItemProxy::updateDragerPos()
{
	QRectF _rect = boundingRect();

	m_ltDrager->setPos(_rect.topLeft());
	m_tDrager->setPos((_rect.left()+_rect.right())/2.0, _rect.top());
	m_rtDrager->setPos(_rect.topRight());
	m_rDrager->setPos(_rect.right(),(_rect.top() + _rect.bottom())/2.0);
	m_rbDrager->setPos(_rect.bottomRight());
	m_bDrager->setPos((_rect.left()+_rect.right())/2.0,_rect.bottom());
	m_lbDrager->setPos(_rect.bottomLeft());
	m_lDrager->setPos(_rect.left(),(_rect.top()+_rect.bottom())/2.0);
}

SelectItemProxy::~SelectItemProxy(void)
{
}


void SelectItemProxy::resize(double x, double y)
{
	if(m_item)
	{
		m_item->setSize(m_item->getSize() + QSizeF(x,y));
		this->updateDragerPos();
	}
}

void SelectItemProxy::setHMIItem(ItemBase *item)
{
// 	this->setParentItem(item); //2015年8月14日16:21:07 不注释新建屏添加元件会报错
// 	m_item = item;
// 	if(!m_item)
// 	{
// 		QGraphicsScene *_scene = this->scene();
// 		if(_scene)
// 			_scene->removeItem(this);
// 	}

	updateDragerPos();
}

void SelectItemProxy::mouseMoveEvent(QGraphicsSceneMouseEvent * event )
{
	if(m_isPressed)
	{
		QPointF currentParentPos=this->mapToParent(this->mapFromScene(event->scenePos()));
		QPointF buttonDownParentPos= this->mapToParent(this->mapFromScene(event->lastScenePos()));

		QPointF _vec=currentParentPos - buttonDownParentPos;

		if(m_item)
		{
			m_item->setPos(m_item->pos() + _vec);
		}
	}
}
void SelectItemProxy::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	if(event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
		event->accept();
	}	
}
void SelectItemProxy::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
	m_isPressed = false;
}

QRectF SelectItemProxy::boundingRect() const
{
	if(m_item)
	{
		return m_item->boundingRect();
	}
	else
	{
		return QRectF(0,0,20,20);
	}
}

void SelectItemProxy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */)
{
	/*painter->setPen(Qt::red);
	painter->drawRect(boundingRect());*/
}

bool SelectItemProxy::itemIsProxy(QGraphicsItem *item)
{
	if(item==this 
		|| item==m_ltDrager
		|| item==m_tDrager
		|| item==m_rtDrager
		|| item==m_rDrager
		|| item==m_rbDrager
		|| item==m_bDrager
		|| item==m_lbDrager
		|| item==m_lDrager)
	{
		return true;
	}
	return false;
}