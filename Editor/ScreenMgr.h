#ifndef ScreenMgr_h__
#define ScreenMgr_h__

#include <QList>

class ScreenMgr
{
	friend class EditorScene;
	static ScreenMgr *instance;
	QList<EditorScene *> m_screens;
protected:
	ScreenMgr(void);

	void addScreen(EditorScene *scene);
	void removeScreen(EditorScene *scene);

public:
	static ScreenMgr &getInstance();
	EditorScene *getScreenByName(const QString &name) const;
};
#endif // ScreenMgr_h__
