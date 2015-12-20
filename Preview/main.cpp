#include "preview.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Preview w;
	w.show();
	return a.exec();
}
