#include "PropertyBrowser.h"
#include <../Property/qtvariantproperty.h>
#include <../Property/qttreepropertybrowser.h>
#include <QDebug>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
//#include <HMICore/ScreenPageBase.h>

PropertyBrowser::PropertyBrowser(QWidget *parent):
QWidget(parent),m_currentObj(NULL)
{
	m_variantFactory = new QtVariantEditorFactory();
	m_variantManager = new QtVariantPropertyManager();	
	m_variantEditor = new QtTreePropertyBrowser(this);
	m_variantEditor->setFactoryForManager(m_variantManager, m_variantFactory);


	QObject::connect(m_variantManager,SIGNAL(valueChanged(QtProperty *, const QVariant)),this,SLOT(propertyChanged(QtProperty *, const QVariant)));

	QVBoxLayout *_layout = new QVBoxLayout(this);
	this->setLayout(_layout);
	_layout->addWidget(m_variantEditor);

	QHBoxLayout *_hLayout = new QHBoxLayout;
	_layout->addLayout(_hLayout);

	m_btnEditScript = new QPushButton(QString::fromLocal8Bit("编辑脚本"), this);
	_hLayout->addWidget(m_btnEditScript);
	connect(m_btnEditScript, SIGNAL(clicked(bool)), this,SIGNAL(editScriptClicked()));
	m_btnDelScript = new QPushButton(QString::fromLocal8Bit("删除脚本"), this);
	_hLayout->addWidget(m_btnDelScript);
	connect(m_btnDelScript, SIGNAL(clicked(bool)), this,SIGNAL(delScriptClicked()));

}

PropertyBrowser::~PropertyBrowser(void)
{
}

#include <QMetaProperty>

void PropertyBrowser::setCurrentObject(QObject *obj)
{
	qDebug() << "PropertyBrowser::setCurrentObject";
	m_variantManager->clear();//先清理，不考虑效率问题。
	m_variantEditor->clear();

	if(!obj)
	{
		m_currentObj = NULL;
		return;
	}

	m_currentObj = obj;
	
	QList<QByteArray> _list = obj->dynamicPropertyNames();
	const QMetaObject *_mo = obj->metaObject();
	int _count = _mo->propertyCount();
	for(int i = 0; i < _count; ++i)
	{
		QMetaProperty _pro = _mo->property(i);
		QString _pName = _pro.name();
		QVariant _value = obj->property(_pName.toStdString().c_str());

		QtVariantProperty *_p = m_variantManager->addProperty(_value.type(),_pName);
		m_variantEditor->addProperty(_p);
	}

	this->updatePropertyValue();	
}

void PropertyBrowser::updatePropertyValue()
{
	qDebug() << "PropertyBrowser::updatePropertyValue";
	if(!m_currentObj)
	{
		return;
	}

	//从对象更新属性时，会引发属性修改信号，先断掉连接。
	QObject::disconnect(m_variantManager,SIGNAL(valueChanged(QtProperty *, const QVariant)),this,SLOT(propertyChanged(QtProperty *, const QVariant)));


	QList<QtProperty *> _pList = m_variantEditor->properties();
	foreach(QtProperty *_p,_pList)
	{
		QString _pName = _p->propertyName();

		QVariant _value = m_currentObj->property(_pName.toStdString().c_str());

		m_variantManager->setValue(_p, _value);
	}

	//恢复连接
	QObject::connect(m_variantManager,SIGNAL(valueChanged(QtProperty *, const QVariant)),this,SLOT(propertyChanged(QtProperty *, const QVariant)));
}

void PropertyBrowser::propertyChanged(QtProperty *_p, const QVariant v)
{
	qDebug() << "PropertyBrowser::propertyChanged";
	if (!m_currentObj)
	{
		return;
	}

	QString _pName = _p->propertyName();
	if(m_variantEditor->properties().indexOf(_p)>-1)
	{
		m_currentObj->setProperty(_pName.toStdString().c_str(), v);
	}
	else
	{
		//非顶层属性，不设置。
	}

	if(_pName == "objectName") //对象名称改变后，通知对象列表更新
	{
		emit objNameChanged();
	}
}
