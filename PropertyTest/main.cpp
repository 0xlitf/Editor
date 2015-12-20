#include "propertytest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PropertyTest w;
	w.show();
	return a.exec();
}
