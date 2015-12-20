#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include <QTreeWidget>
#include <QDropEvent>
#include "editorscene.h"
#include "editorviewbase.h"
class SelectItemProxy;
class EditorView : public EditorViewBase
{
	Q_OBJECT
public:
	EditorView(QWidget * parent = 0);
	~EditorView(void);

	void createScene(const QString &screenName);
	void loadScene(const QString &sceneFile);//在编辑器中加载屏时，不加载脚本。

	void delSelectItem();

	ItemBase *getSelectItem() const;
	void setSelectItem(ItemBase *item);

	void copyItem();
	void pasteItem();

	void editScriptForPage(ItemBase *item);
	void delScriptForPage(ItemBase *item);
	public slots:
signals :
	void newItemByDrag();
	void selectItemChanged(QObject *);


protected:
	void dragEnterEvent(QDragEnterEvent * event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
	void resizeEvent(QResizeEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

	void keyPressEvent(QKeyEvent * event);
	void keyReleaseEvent(QKeyEvent * event);

	//void mouseDoubleClickEvent ( QMouseEvent * event );

private:
	SelectItemProxy *m_selectItemProxy;


};

#endif // EDITORVIEW_H
