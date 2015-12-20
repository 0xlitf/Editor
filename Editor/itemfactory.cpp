#include "itemfactory.h"
#include <QDebug>
ItemFactory *ItemFactory::instance = NULL;

ItemFactory::ItemFactory()
{

}

ItemFactory::~ItemFactory()
{

}

ItemFactory& ItemFactory::getInstance(){
	if (!instance)
		instance = new ItemFactory;
	return *instance;
}

ItemBase* ItemFactory::createItem(QString &classname){
	if (!m_factories.contains(classname))
	{
		return NULL;
	}
	return m_factories[classname]->createItem();
}
void ItemFactory::registerFactory(QString &classname, ItemVirtualFactory *fa){
	if (m_factories.contains(classname))
	{
		return;
	}
	m_factories[classname] = fa;
}

QStringList ItemFactory::itemTypeList(){
	return m_factories.keys();
}
