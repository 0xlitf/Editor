#ifndef EDITORSCENE_H
#define EDITORSCENE_H
#include "editorpage.h"
#include <QTime>
#include <QtWidgets/QGraphicsScene>
class EditorScene : public QGraphicsScene
{
	Q_OBJECT
		Q_PROPERTY(bool RepeatBkgPixmap READ getRepeatBkgPixmap WRITE setRepeatBkgPixmap)
		Q_PROPERTY(QString  BackgroundPixmap READ getBackgroundPixmap WRITE setBackgroundPixmap)
		Q_PROPERTY(QString CurrentPage READ getCurrentPage WRITE setCurrentPage)

public:
	/*HMIScene(QObject *parent=0);*/
	EditorScene(const QString &sceneFile, QObject *parent = 0);
	~EditorScene(void);

	void setSceneName(const QString &name){ setObjectName(name); }
	QString getSceneName(){ return objectName(); }

	EditorPage *getRootPage()
	{
		return m_rootPage;
	}

	EditorPage *getPageByFullName(const QString &fullName);

	void setRootPage(EditorPage *root);

	bool saveSceneFile(const QString &fileName);

	QString getBackgroundPixmap() const { return m_backgroundPixmapName; }
	void setBackgroundPixmap(const  QString &pname);

	void setRepeatBkgPixmap(bool repeat)
	{
		m_repeatBkgPixmap = repeat;
	}
	bool getRepeatBkgPixmap() const { return m_repeatBkgPixmap; }

	void commonEventReceive(const QString &eInfo);
	void commonEventRelease(const QString &eInfo);

	bool isNull() const;

	void setCurrentPage(const QString &fullName);
	QString getCurrentPage() const;

protected:
	void timerEvent(QTimerEvent *);
	void drawBackground(QPainter * painter, const QRectF & rect);
private:
	QString m_sceneName;
	EditorPage *m_rootPage;
	QString m_backgroundPixmapName;
	QPixmap m_bkgPixmap;
	bool m_repeatBkgPixmap;
	QTime m_lastTickTime;

	QString m_currentPage;
};

#endif // EDITORSCENE_H
