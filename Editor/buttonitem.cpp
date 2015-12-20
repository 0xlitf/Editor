#include "itemfactory.h"
#include "buttonitem.h"
#include <QDebug>
ButtonItem::ButtonItem(QGraphicsItem *parent)
	: ItemBase(parent), 
	m_text("Button"),
	m_backColor(240, 240, 240, 255), 
	m_textColor(0, 0, 0, 255), 
	m_textAlignment(Qt::AlignVCenter | Qt::AlignHCenter),
	m_isPressed(false)
{
	this->setSize(QSizeF(80, 28));
}

ButtonItem::~ButtonItem()
{

}

void ButtonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */){
//	qDebug() << "ButtonItem::paint";
 	painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
 	QRectF _rect = boundingRect();
	if (m_isPressed)
	{
		if (m_pressedImage.isNull())
		{
			painter->setPen((m_backColor.alpha() == 0) ? QColor(0, 0, 0, 0) : m_backColor.darker(50));
			painter->setBrush(m_backColor);
			painter->drawRect(boundingRect());

			painter->setPen((m_backColor.alpha() == 0) ? QColor(0, 0, 0, 0) : m_backColor.lighter(50));
			painter->drawLine(_rect.bottomLeft(), _rect.topLeft());
			painter->drawLine(_rect.topLeft(), _rect.topRight());

			painter->setPen((m_backColor.alpha() == 0) ? QColor(0, 0, 0, 0) : m_backColor.darker(50));
			painter->drawLine(_rect.bottomLeft(), _rect.bottomRight());
			painter->drawLine(_rect.bottomRight(), _rect.topRight());
		}
		else
		{
			if (getSplash() && bJT)
			{
				qDebug() << "bJT:" << bJT;
				if (m_svgRendererSplash.isValid())
				{
					m_svgRendererSplash.render(painter, _rect);
				}
				else
				{
					painter->drawPixmap(_rect, m_SplashImage, m_SplashImage.rect());
				}
			}
			else
			{
				if (m_svgRendererPress.isValid())
				{
					m_svgRendererPress.render(painter, _rect);
				}
				else
				{
					painter->drawPixmap(_rect, m_pressedImage, m_pressedImage.rect());
				}
			}

		}

	}
	else
	{
		if (m_normalImage.isNull())
		{
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
		else
		{
			/*painter->drawPixmap(_rect, m_normalImage, m_normalImage.rect());*/
			if (getSplash() && bJT)
			{
				qDebug() << "bJT:" << bJT;
				if (m_svgRendererSplash.isValid())
				{
					m_svgRendererSplash.render(painter, _rect);
				}
				else
				{
					painter->drawPixmap(_rect, m_SplashImage, m_SplashImage.rect());
				}
			}
			else
			{
				if (m_svgRenderer.isValid())
				{
					m_svgRenderer.render(painter, _rect);
				}
				else
				{
					painter->drawPixmap(_rect, m_normalImage, m_normalImage.rect());
				}
			}
		}
	}

	painter->setPen(m_textColor);
	painter->setFont(m_font);
	painter->drawText(_rect, m_text, QTextOption(m_textAlignment));

}


int ButtonItem::type() const
{
//	return ItemBase::ButtonItemType;
	return 0;
}

void ButtonItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	event->accept();
//	if (m_eventHandler)m_eventHandler->onMoved(this, event);
}
void ButtonItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	m_isPressed = true;
	event->accept();
	this->update();
//	if (m_eventHandler)m_eventHandler->onPressed(this, event);
}
void ButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
// 	if (this->boundingRect().contains(event->pos()))
// 	{
// 		emit clicked();
// 		if (m_eventHandler)m_eventHandler->onClicked(this, event);
// 	}
// 	m_isPressed = false;
// 	event->accept();
// 	this->update();
// 	if (m_eventHandler)m_eventHandler->onRelease(this, event);
}

// void ButtonItem::setPressedImage(const  QString &pname)
// {
// 	m_pressedImage = QPixmap(ResourceMgr::getInstance().abstractFileName(pname));
// 	m_pressedImageName = pname;
// 	m_svgRendererPress.load(ResourceMgr::getInstance().abstractFileName(pname));
// }
// 
// void ButtonItem::setNormalImage(const  QString &pname)
// {
// 	m_normalImage = QPixmap(ResourceMgr::getInstance().abstractFileName(pname));
// 	m_normalImageName = pname;
// 	m_svgRenderer.load(ResourceMgr::getInstance().abstractFileName(pname));
// 
// }
// 
// void ButtonItem::setSplashImage(const  QString &pname)
// {
// 	if (getSplash())//‘ –Ì…¡À∏
// 	{
// 		m_SplashImage = QPixmap(ResourceMgr::getInstance().abstractFileName(pname));
// 		m_SplashImageName = pname;
// 		m_svgRendererSplash.load(ResourceMgr::getInstance().abstractFileName(pname));
// 	}
// }

RegisterItemFactory(ButtonItem)