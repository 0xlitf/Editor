#ifndef ResourceMgr_h__
#define ResourceMgr_h__

#include <QtCore/QString>
#include <QtCore/QDir>


class ResourceMgr
{
	static ResourceMgr *instance;
public:
	static ResourceMgr &getInstance();
	QString abstractFileName(const QString &baseName);

protected:
	ResourceMgr(void);
	void setResourceDir(const QString &dir);
private:
	friend class EditorScene;
	QDir m_screenDir;
};
#endif // ResourceMgr_h__
