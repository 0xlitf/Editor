#ifndef PROPERTYTEST_H
#define PROPERTYTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_propertytest.h"

class PropertyTest : public QMainWindow
{
	Q_OBJECT

public:
	PropertyTest(QWidget *parent = 0);
	~PropertyTest();

private:
	Ui::PropertyTestClass ui;
};

#endif // PROPERTYTEST_H
