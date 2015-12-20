#ifndef EDITORVIEWBASE_H
#define EDITORVIEWBASE_H

#include <QGraphicsView>
class EditorScene;

class EditorViewBase : public QGraphicsView
{
	Q_OBJECT
public:
	EditorViewBase(QWidget * parent = 0, bool redirect = true);
	~EditorViewBase(void);

	EditorScene *getEditorScene(){ return m_scene; }
	void setEditorScene(EditorScene *scene);

	void loadScene(const QString &sceneFile);

protected:
	void resizeEvent(QResizeEvent *event);
private:
	void loadScriptFile(const QString &sname);
	EditorScene *m_scene;
};

#endif // EDITORVIEWBASE_H
