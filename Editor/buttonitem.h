#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include "itembase.h"
#include <QPainter>
class ButtonEventHandler;
class ButtonItem : public ItemBase
{
	Q_OBJECT
		Q_PROPERTY(QString text READ getText WRITE setText)
		Q_PROPERTY(QString Mask READ getMask WRITE setMask)
		Q_PROPERTY(int alignment READ getAlignment WRITE setAlignment)
		Q_PROPERTY(QFont font READ getFont WRITE setFont)

		Q_PROPERTY(QColor TextColor READ textColor WRITE setTextColor)
		Q_PROPERTY(QColor BackColor READ backColor WRITE setBackColor)
public:
	ButtonItem(QGraphicsItem *parent = 0);
	~ButtonItem(void);

	void setText(const QString &text){ m_text = text; }
	QString getText() const { return m_text; }
	void setMask(const QString &mk){ m_mask = mk; }
	QString getMask() const { return m_mask; }

	void setAlignment(int ali){ m_textAlignment = (Qt::Alignment)ali; }
	void setAlignment(Qt::AlignmentFlag ali){ m_textAlignment = ali; }
	int getAlignment(){ return (int)m_textAlignment; }

	QFont getFont(){ return m_font; }
	void setFont(QFont f){ m_font = f; }

	QColor textColor() { return m_textColor; }
	void setTextColor(const QColor &c){ m_textColor = c; }

	QColor backColor() { return m_backColor; }
	void setBackColor(const QColor &c){ m_backColor = c; }

	QString getNormalImage() const { return m_normalImageName; }
	void setNormalImage(const  QString &pname);

	QString getPressedImage() const { return m_pressedImageName; }
	void setPressedImage(const  QString &pname);

	void setSplash(const bool& _bSplash){ bSplash = _bSplash; }
	bool getSplash() const { return bSplash; }

	QString getSplashImage() const { return m_SplashImageName; }
	void setSplashImage(const  QString &pname);

	void setEventHander(ButtonEventHandler *eh){ m_eventHandler = eh; }

	int type() const;
	bool m_isPressed;
	bool bSplash;
	bool bJT;
	public slots:
signals :
	void clicked();

protected:
	QSvgRenderer m_svgRenderer;
	QSvgRenderer m_svgRendererPress;
	QSvgRenderer m_svgRendererSplash;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	QString m_text;
	QString m_mask;
	Qt::Alignment m_textAlignment;
	QFont m_font;
	QColor m_textColor;
	QColor m_backColor;

	QString m_normalImageName;
	QPixmap m_normalImage;
	QString m_pressedImageName;
	QPixmap m_pressedImage;

	QString m_SplashImageName;
	QPixmap m_SplashImage;


	ButtonEventHandler *m_eventHandler;
};

#endif // BUTTONITEM_H
