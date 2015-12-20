#ifndef PageEventHandler_h__
#define PageEventHandler_h__

#include <QObject>

class EditorPage;
class PageEventHandler : public QObject
{
	Q_OBJECT
public:
	PageEventHandler(void);
	~PageEventHandler(void);

	virtual void tick(EditorPage *e, int ms){}

	virtual void pageAboutToShow(EditorPage *e){}

	virtual void pageHasHide(EditorPage *e){}

	virtual void commonEventReceive(EditorPage *e, const QString &eInfo){}

	virtual void commonEventRelease(EditorPage *e, const QString &eInfo){}

	
};
#endif // PageEventHandler_h__
