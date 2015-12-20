#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <QString>
#include <QStringList>
#include <QMap>
class ItemBase;
class ItemVirtualFactory{
public:
	virtual ItemBase *createItem(){
		return NULL;
	}
};

#define RegisterItemFactory(typename) class typename##Factory : public ItemVirtualFactory\
{\
public:\
	typename##Factory()\
{\
	ItemFactory::getInstance().registerFactory(QString(#typename),this);\
}\
	ItemBase *createItem()\
{\
	return new typename;\
}\
};\
typename##Factory _##typename##_factory;

class ItemFactory
{
public:
	ItemFactory();
	~ItemFactory();
	static ItemFactory &getInstance();
	ItemBase *createItem(QString &classname);
	QStringList itemTypeList();
	void registerFactory(QString &classname, ItemVirtualFactory *fa);
private:
	static ItemFactory *instance;
	QMap<QString, ItemVirtualFactory*> m_factories;
};

#endif // ITEMFACTORY_H
