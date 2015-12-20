#include "editorviewbase.h"
#include "EditorView.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QFile>
#include "EditorPage.h"
#include "EditorScene.h"
#include "ItemBase.h"
#include "EditorScene.h"
#include <QFileInfo>
#include <QtWidgets/QApplication>
#include <QFileInfo>

EditorViewBase::EditorViewBase(QWidget * parent, bool redirect) :
QGraphicsView(parent), m_scene(NULL)
{
	//初始化python环境
// 	if (!Py_IsInitialized())
// 	{
// 		Py_Initialize();
// 		PyRun_SimpleString("import sys");
// 		QString _cmd = QString("sys.path.append('%1')").arg(qApp->applicationDirPath() + "/library.o");
// 		PyRun_SimpleString(_cmd.toStdString().c_str());
// 
// 		if (redirect)
// 		{
// 
// 			QString _cmd = QString("").arg(QFileInfo(qApp->applicationFilePath()).baseName());
// 			PyRun_SimpleString(_cmd.toStdString().c_str());
// 		}
// 	}

	this->setFrameShape(QFrame::NoFrame);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
}

EditorViewBase::~EditorViewBase(void)
{
	//Py_Finalize();
}

void EditorViewBase::setEditorScene(EditorScene *scene)
{
	this->setScene(scene);
	m_scene = scene;
}


void EditorViewBase::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);

	QRectF _ref = m_scene->sceneRect();
	_ref.setSize(_ref.size() - QSizeF(1.0, 1.0));
	fitInView(_ref);
}

void EditorViewBase::loadScene(const QString &sceneFile)
{
	EditorScene *_scene = getEditorScene();
	EditorScene *_newScene = new EditorScene(sceneFile);
	this->setEditorScene(_newScene);
	if (_scene)
	{
		delete _scene;
	}
	loadScriptFile(sceneFile);
}

void setScriptForPage(EditorPage *p, const QString &dir, const QString &screenName)
{
	QString _fullName = p->getFullName().replace(".", "_");

	if (QFile::exists(dir + "/" + screenName + "/" + _fullName + ".py"))
	{
		QString _cmd = QString("import %1\n\
							   							   _scene=HMICore.jsonMgr.getInstance().getScreenByName('%2')\n\
														   							   if _scene:\n\
																					   							       #print _scene\n\
																													   								       _p = _scene.getPageByFullName('%3')\n\
																																						   									       if _p:\n\
																																																   										           _p.setEventHandler(%4._instance)\n\
																																																												   												   ").arg(screenName + "." + _fullName)
																																																																								   .arg(screenName)
																																																																								   .arg(p->getFullName())
																																																																								   .arg(screenName + "." + _fullName/*+"."+p->getId()*/);

//		PyRun_SimpleString(_cmd.toStdString().c_str());

	}


	foreach(QString _id, p->getSubPageNames())
	{
		EditorPage *_cp = p->getSubPage(_id);
		setScriptForPage(_cp, dir, screenName);
	}
}

void EditorViewBase::loadScriptFile(const QString &sname)
{


	//setScript for page
	EditorScene *_scene = this->getEditorScene();
	if (!_scene)
	{
		return;
	}

	EditorPage *_rootPage = _scene->getRootPage();
	if (!_rootPage)
	{
		return;
	}

//	PyRun_SimpleString("import sys");


	QString _scriptPath = QFileInfo(sname).absolutePath() + "/ScreenScript";

	QString _setPathCmd = QString("sys.path.append('%1')").arg(_scriptPath);
//	PyRun_SimpleString(_setPathCmd.toStdString().c_str());

//	PyRun_SimpleString("import HMICore");
	//PyRun_SimpleString("allPageHandler=[]");//将所有页面的事件处理对象放到列表中，防止被析构
	setScriptForPage(_rootPage, _scriptPath, _scene->getSceneName());
}