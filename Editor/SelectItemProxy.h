#ifndef SelectItemProxy_h__
#define SelectItemProxy_h__

#include <QtWidgets/QGraphicsItem>
class ItemBase;

class SelectItemProxyDrager;
class SelectItemProxy : public QGraphicsItem
{
public:
	SelectItemProxy(QGraphicsItem *parent=0);
	~SelectItemProxy(void);

	QRectF boundingRect() const;

	void setHMIItem(ItemBase *item);
	ItemBase *getHMIItem() const {return m_item;}

	bool itemIsProxy(QGraphicsItem *item);

	void resize(double x, double y);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);

	void updateDragerPos();
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	ItemBase *m_item;
	SelectItemProxyDrager *m_ltDrager;
	SelectItemProxyDrager *m_tDrager;
	SelectItemProxyDrager *m_rtDrager;
	SelectItemProxyDrager *m_rDrager;
	SelectItemProxyDrager *m_rbDrager;
	SelectItemProxyDrager *m_bDrager;
	SelectItemProxyDrager *m_lbDrager;
	SelectItemProxyDrager *m_lDrager;
	bool m_isPressed;
};
#endif // SelectItemProxy_h__
