#include "ScreenMgr.h"
#include "EditorScene.h"

ScreenMgr::ScreenMgr(void)
{
}

ScreenMgr *ScreenMgr::instance = NULL;

ScreenMgr &ScreenMgr::getInstance()
{
	if(!instance)
	{
		instance = new ScreenMgr;
	}
	return *instance;
}

void ScreenMgr::addScreen(EditorScene *scene)
{
	if(!m_screens.contains(scene))
		m_screens.append(scene);
}

void ScreenMgr::removeScreen(EditorScene *scene)
{
	m_screens.removeOne(scene);
}

EditorScene *ScreenMgr::getScreenByName(const QString &name) const
{
	foreach(EditorScene *sc,m_screens)
	{
		if(sc->getSceneName()==name)
		{
			return sc;
		}
	}
	return NULL;
}