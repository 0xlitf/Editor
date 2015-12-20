
#include <QtCore/QCoreApplication>
#include <QString>
#include <QDebug>
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QString str = "66";
	qDebug() << str.toInt();
	return a.exec();
}
