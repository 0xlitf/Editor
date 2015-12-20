#include "ResourceMgr.h"
#include <QDir>
#include <QDebug>
#include <QtWidgets/QApplication>

ResourceMgr::ResourceMgr(void):m_screenDir(qApp->applicationDirPath())
{
}
ResourceMgr *ResourceMgr::instance=NULL;
ResourceMgr &ResourceMgr::getInstance()
{
	if(!instance)
	{
		instance = new ResourceMgr;
	}
	return *instance;
}

void ResourceMgr::setResourceDir(const QString &dir)
{
	m_screenDir.setPath(dir);
	if(!m_screenDir.exists())
	{
		qDebug()<<"dir is not exists:"<<dir;
		m_screenDir.setPath(qApp->applicationDirPath());
	}

	if(!m_screenDir.cd("resource"))
	{
		m_screenDir.mkdir("resource");
		m_screenDir.cd("resource");
	}
}

QString ResourceMgr::abstractFileName(const QString &baseName)
{
	qDebug()<<m_screenDir<<baseName;

	if(baseName.isEmpty())
	{
		return "";
	}
	if(m_screenDir.exists(baseName))
	{
		return m_screenDir.absoluteFilePath(baseName);
	}
	return "";
	
}