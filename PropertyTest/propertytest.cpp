#include "propertytest.h"
#include "../Property/qtpropertymanager.h"
#include "../Property/qteditorfactory.h"
#include "../Property/qttreepropertybrowser.h"
#include "../Property/qtpropertybrowser.h"
#include <QWidget>
#include <QLayout>
PropertyTest::PropertyTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QWidget *w = new QWidget(this);
	QtBoolPropertyManager *boolManager = new QtBoolPropertyManager(w);
	QtIntPropertyManager *intManager = new QtIntPropertyManager(w);
	QtStringPropertyManager *stringManager = new QtStringPropertyManager(w);
	QtSizePropertyManager *sizeManager = new QtSizePropertyManager(w);
	QtRectPropertyManager *rectManager = new QtRectPropertyManager(w);
	QtSizePolicyPropertyManager *sizePolicyManager = new QtSizePolicyPropertyManager(w);
	QtEnumPropertyManager *enumManager = new QtEnumPropertyManager(w);
	QtGroupPropertyManager *groupManager = new QtGroupPropertyManager(w);

	QtProperty *item0 = groupManager->addProperty("QObject");
	QtProperty *item1 = stringManager->addProperty("objectName");
	QtProperty *item2 = boolManager->addProperty("enable");
	QtProperty *item3 = rectManager->addProperty("geometry");
	QtProperty *item4 = sizePolicyManager->addProperty("sizePolicy");
	QtProperty *item5 = sizeManager->addProperty("sizeIncrement");
	QtProperty *item6 = intManager->addProperty("value");
	QtProperty *item7 = boolManager->addProperty("mouseTracking");
	QtProperty *item8 = enumManager->addProperty("enum");

	item0->addSubProperty(item1);
	item0->addSubProperty(item2);
	item0->addSubProperty(item3);
	item0->addSubProperty(item4);
	item0->addSubProperty(item5);
	item0->addSubProperty(item6);
	item0->addSubProperty(item7);
	item0->addSubProperty(item8);

	QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory(w);
	QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(w);
	QtSliderFactory *sliderFactory = new QtSliderFactory(w);
	QtScrollBarFactory *scrollBarFactory = new QtScrollBarFactory(w);
	QtLineEditFactory *lineEditFactory = new QtLineEditFactory(w);
	QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory(w); 

	QtAbstractPropertyBrowser *editor = new QtTreePropertyBrowser();
	editor->setFactoryForManager(boolManager, checkBoxFactory);
	editor->setFactoryForManager(intManager, spinBoxFactory);
	editor->setFactoryForManager(stringManager, lineEditFactory);
	editor->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
	editor->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
	editor->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
	editor->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
	editor->setFactoryForManager(enumManager, comboBoxFactory);

	editor->addProperty(item0);
	QHBoxLayout *hLayout = new QHBoxLayout(ui.centralWidget);
	hLayout->addWidget(w);
	QHBoxLayout *hLayout2 = new QHBoxLayout(w);
	hLayout2->addWidget(editor);
}

PropertyTest::~PropertyTest()
{

}
