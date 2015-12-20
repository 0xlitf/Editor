#include "editorscene.h"
#include "editorpage.h"
#include <QDebug>
#include <QTimerEvent>
#include <QFile>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDomDocument>
#include "ItemFactory.h"
#include <QList>
#include "QStringAndQVariant.h"
#include "ResourceMgr.h"
#include "ScreenMgr.h"
#include "editorview.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QMapIterator>
#include <QMultiMap>
//Q_DECLARE_METATYPE QMultiMap<QString,QVariant>
void setObjectProperty(QObject *obj, const QJsonArray &_array)
{
	int i = 0;
	QJsonObject _pe;
	if (_array.size() > 0)
	{
		_pe = _array.at(i).toObject();
	}
	while (i < _array.size())
	{
		_pe = _array.at(i).toObject();
//		setObjectProperty(obj, _pe);
		QVariant::Type _type = (QVariant::Type)_pe.value("type").toString().toInt();
		QString _name = _pe.value("name").toString();
		QString _value = _pe.value("value").toString();

		if (obj->metaObject()->indexOfProperty(_name.toStdString().c_str()) < 0)
		{
			//没有属性
			qDebug() << "Can not find property" << _name << "for object:" << obj->objectName();
			return;
		}

		obj->setProperty(_name.toStdString().c_str(), QStringAndQVariant::stringToVariant(_type, _value));
		//
		++i;
	}
//	const QMetaObject *_mo = obj->metaObject();


}

void initItemFromXml(ItemBase *_seItem, const QJsonObject &jsonObj)
{
	//名字

	if (!_seItem)
	{
		return;
	}
	_seItem->setName(jsonObj.find("itemName").value().toString());

	//属性
	QJsonObject _proE = jsonObj.find("property").value().toObject();

	QJsonArray _array = jsonObj.value("property").toArray();

	setObjectProperty(_seItem, _array);

}

void initPageFromXml(EditorPage *page, const QJsonObject &pageE)
{
	if (!page || pageE.isEmpty())
	{
		return;
	}
	page->setId(pageE.value("name").toString());
	qDebug() << "page name:" << pageE.value("name").toString();

	//页面元素
	qDebug() << QString::fromLocal8Bit("//yemian yuansu");
	QJsonArray _itemArray = pageE.value("sub item").toArray();
	QJsonObject _itemObj;
	if (!_itemArray.isEmpty())
	{
		int i = 0;
		while (i < _itemArray.size())
		{
			_itemObj = _itemArray[i].toObject();
			QString _className = _itemObj.value("className").toString();
			ItemBase *_seItem = ItemFactory::getInstance().createItem(_className);
			if (_seItem)
			{
				initItemFromXml(_seItem, _itemObj);
				page->addItem(_seItem);
			}
			++i;
		}
	}

	qDebug() << QString::fromLocal8Bit("//zi yemian");

	//子页面
	QJsonArray _pageArray = pageE.value("sub page").toArray();
	QJsonObject _cpe;
	if (!_pageArray.isEmpty())
	{
		int i = 0;
		while (i < _pageArray.size())
		{
			_cpe = _pageArray[i].toObject();
			EditorPage *_subPage = new EditorPage("subpage");
			initPageFromXml(_subPage, _cpe);
			page->addSubPage(_subPage);
			++i;
		}
	}

	//属性设置，页面是QGraphicsItemGroup，如果先设置页面的pos，然后调用addToGroup添加item时，会影响item的pos。故，先初始化页面上的item,然后设置页面的属性。
	qDebug() << QString::fromLocal8Bit("//shuxing shezhi");

	//	QJsonObject _proE = _it.value().toJsonObject();
	// 	QJsonObject _proE = _map.find("property").value().toJsonObject();
	// 	qDebug() << "QJsonObject:" << _proE;
	// 	qDebug() << "_proE.isEmpty():" << _proE.isEmpty();

	QJsonArray _array = pageE.value("property").toArray();
	setObjectProperty(page, _array);



	// 	QJsonObject _proE = pageE.value("property").toObject();
	//  	qDebug() << "QJsonObject:" << _proE;
	//  	qDebug() << "_proE.isEmpty():" << _proE.isEmpty();
	// 	while (!_proE.isEmpty())
	// 	{
	// 		qDebug() << "page property";
	// 		qDebug() << "property:" << _it.value();
	// 		setObjectProperty(page, _proE);
	// 		++_it;
	// 		_proE = _it.value().toJsonObject();
	// 	}
}

void loadSceneFromXml(EditorScene *screen, const QJsonObject &jsonObj)
{
	qDebug() << "loadSceneFromXml";
	screen->setSceneName(jsonObj.value("screen").toObject().value("id").toString());

	//root page
	QJsonObject _rp = jsonObj.value("screen").toObject().value("root page").toObject();
	if (!_rp.isEmpty())
	{
		EditorPage *_rootPage = new EditorPage("root");
		initPageFromXml(_rootPage, _rp);
		screen->setRootPage(_rootPage);
	}

	//Screen 属性设置
	QJsonArray _array = jsonObj.value("screen").toObject().value("property").toArray();
	setObjectProperty(screen, _array);


}

EditorScene::EditorScene(const QString &sceneFile, QObject *parent) :
QGraphicsScene(QRectF(0.0, 0.0, 500, 500), parent), m_rootPage(NULL),
m_repeatBkgPixmap(false)
{
	qDebug() << "";
	ResourceMgr::getInstance().setResourceDir(QFileInfo(sceneFile).absolutePath());
	QFile _file(sceneFile);
	if (_file.open(QIODevice::ReadOnly))
	{
		QTextStream _stream(&_file);
		QString _str = _stream.readAll();
		QJsonParseError _err;
		QJsonDocument _doc = QJsonDocument::fromJson(_str.toUtf8(), &_err);
		QJsonObject _jsonRootObj;
		if (_err.error == QJsonParseError::NoError)
		{
			if (_doc.isObject())
			{
				_jsonRootObj = _doc.object();
				loadSceneFromXml(this, _jsonRootObj);
			}
		}
		_file.close();
	}
	else
	{
		m_rootPage = new EditorPage("root");
		this->addItem(m_rootPage);
		qDebug() << "cann't open scene file: " << sceneFile;
	}

	this->startTimer(60);
	ScreenMgr::getInstance().addScreen(this);
}

EditorScene::~EditorScene(void)
{
	this->removeItem(m_rootPage);
	delete(m_rootPage);
	ScreenMgr::getInstance().removeScreen(this);
}

bool EditorScene::isNull() const
{
	if (m_rootPage)
	{
		return false;
	}

	return true;
}

void EditorScene::setBackgroundPixmap(const  QString &pname)
{
	m_backgroundPixmapName = pname;
	m_bkgPixmap = QPixmap(ResourceMgr::getInstance().abstractFileName(m_backgroundPixmapName));
}

void EditorScene::setRootPage(EditorPage *root)
{
	if (m_rootPage)
	{
		this->removeItem(m_rootPage);
	}
	m_rootPage = root;
	this->addItem(m_rootPage);
}

void EditorScene::drawBackground(QPainter * painter, const QRectF & rect)
{
	QGraphicsScene::drawBackground(painter, rect);

	if (!m_bkgPixmap.isNull())
	{
		if (m_repeatBkgPixmap)
		{
			painter->fillRect(rect, QBrush(m_bkgPixmap));
		}
		else
		{
			painter->drawPixmap(sceneRect(), m_bkgPixmap, m_bkgPixmap.rect());
		}
	}
}

void EditorScene::timerEvent(QTimerEvent *e)
{
	int ms = 0;
	if (m_lastTickTime.isNull())
	{
		m_lastTickTime = QTime::currentTime();
	}
	else
	{
		QTime _cur = QTime::currentTime();
		ms = m_lastTickTime.msecsTo(_cur);
		m_lastTickTime = _cur;
	}


	if (m_rootPage)
	{
		m_rootPage->driveTick(ms);
	}
	this->update();
}

void EditorScene::commonEventReceive(const QString &eInfo)
{
	if (m_rootPage)
	{
		EditorPage *_cp = m_rootPage->getCurrentPage();
		_cp->commonEventReceive(eInfo);
	}

}

void EditorScene::commonEventRelease(const QString &eInfo)
{
	if (m_rootPage)
	{
		EditorPage *_cp = m_rootPage->getCurrentPage();
		_cp->commonEventRelease(eInfo);
	}
}

void EditorScene::setCurrentPage(const QString &fullName)
{
	if (!m_rootPage)
	{
		return;
	}

	QStringList _names = fullName.split(".");
	if (_names.isEmpty())
	{
		return;
	}

	QString _rootPageName = _names.takeFirst();

	if (m_rootPage->getId() != _rootPageName)
	{
		qDebug() << "root page name is error @ EditorScene::setCurrentPage(const QString &fullName) :" << fullName;
		return;
	}

	if (_names.isEmpty())
	{
		m_rootPage->closeGenerationPage();
		return;
	}

	m_rootPage->goToGenerationPage(_names.join("."));
}

EditorPage *getSubPage(EditorPage *p, QStringList &names)
{
	if (names.isEmpty())
	{
		return p;
	}
	QString _subId = names.takeFirst();
	foreach(QString _id, p->getSubPageNames())
	{
		if (_id == _subId)
		{
			return getSubPage(p->getSubPage(_id), names);
		}
	}
	return NULL;
}

EditorPage *EditorScene::getPageByFullName(const QString &fullName)
{
	QStringList _names = fullName.split(".");
	if (_names.isEmpty())
	{
		return NULL;
	}
	if (!m_rootPage || m_rootPage->getId() != _names.at(0))
	{
		return NULL;
	}

	if (m_rootPage->getId() == _names.takeFirst())
	{
		return getSubPage(m_rootPage, _names);
	}
	else
	{
		return NULL;
	}

}

QString EditorScene::getCurrentPage() const
{
	if (m_rootPage)
	{
		return m_rootPage->getCurrentPage()->getFullName();
	}
	return QString();
}

bool EditorScene::saveSceneFile(const QString &fileName)
{
	if (fileName.isEmpty())
	{
		qDebug() << "ERROR: call EditorScene::saveSceneFile(const QString &fileName) with empty fileName";
		return false;
	}
	QFile _file(fileName);
	if (!_file.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		return false;
	}
	QTextStream _stream(&_file);
	QString _str;
	_str += QString("{\n    \"screen\": {\n        \"id\": \"%1\",\n").arg(getSceneName());//screen id
	const QMetaObject *_mo = this->metaObject();
	int _count = _mo->propertyCount();
	_str += "        \"property\": [\n";//screen property
	for (int i = 0; i < _count; ++i)
	{
		QString _pName = _mo->property(i).name();
		if (_pName == "objectName")continue;//objectName作为sceneName记录，此处忽略
		QVariant _value = this->property(_pName.toStdString().c_str());
		_str += QString("            { \"type\": \"%1\", \"name\": \"%2\", \"value\": \"%3\" }").arg(int(_value.type())).arg(_pName).arg(QStringAndQVariant::vairantToString(_value));
		if (i != _count - 1)
			_str += ",\n";
	}
	_str += "],\n";
	_str += "        \"root page\": ";//root page property
	_str += m_rootPage->toXml();
	_str += QString("    }");
	_str += QString("\n}");

	QRegExp _reRightBrace("\\,(\\s*)\\}");
	QRegExp _reRightBracket("\\,(\\s*)\\]");
	_str.replace(_reRightBrace, "\\1}");
	_str.replace(_reRightBracket, "\\1]");
	_stream << _str;
	_stream.flush();
	_file.close();
	return true;
}