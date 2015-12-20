// 
// #include <QtCore/QCoreApplication>
// #include <QFile>
// #include <QDomDocument>
// #include <QJsonDocument>
// #include <QJsonObject>
// int main(int argc, char *argv[])
// {
// 	QFile _xmlFile;
// 	_xmlFile.open(QIODevice::ReadOnly);
// 	QCoreApplication a(argc, argv);
// 	QDomDocument _xmlDoc("xmlDoc");
// 	_xmlDoc.setContent(&_xmlFile);
// 	QDomElement _re = _xmlDoc.documentElement();
// 
// 
// 
// 
// 	return a.exec();
// }

#include <QDebug>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
//#include <sys/time.h>
#include <time.h>
#include <QString>

#include "xml2json.hpp"

using namespace std;

// int64_t getCurrentTime()
// {
// 	struct timeval tval;
// 	gettimeofday(&tval, NULL);
// 	return tval.tv_sec * 1000000LL + tval.tv_usec;
// }

int main(int argc, const char *argv[])
{
	//file<> fdoc("track_orig.xml");
	string xml_str, json_str;
	ifstream inf;
	ofstream outf;
	ostringstream oss;
	char BOM[4] = {(char)0xEF, (char)0xBB, (char)0xBF, '\0'};
	int64_t start_time, end_time;

// 	inf.open("test_track_1.xml");
// 	outf.open("test_track_1.js.txt");
// 	oss.clear();
// 	oss << inf.rdbuf();
// 	xml_str = oss.str();
// 	inf.close();
// //	start_time = getCurrentTime();
// 	json_str = xml2json(xml_str.c_str());
// //	end_time = getCurrentTime();
// 	cout << "time1: " << end_time - start_time << endl;
// 	outf << BOM << json_str;
// 	outf.close();
// 
// 	inf.open("test_track_2.xml");
// 	outf.open("test_track_2.js.txt");
// 	oss.clear();
// 	oss << inf.rdbuf();
// 	xml_str = oss.str();
// 	inf.close();
// //	start_time = getCurrentTime();
// 	json_str = xml2json(xml_str.c_str());
// //	end_time = getCurrentTime();
// 	cout << "time2: " << end_time - start_time << endl;
// 	outf << BOM << json_str;
// 	outf.close();
// 
// 	inf.open("test_track_3.xml");
// 	outf.open("test_track_3.js.txt");
// 	oss.clear();
// 	oss << inf.rdbuf();
// 	xml_str = oss.str();
// 	inf.close();
// //	start_time = getCurrentTime();
// 	json_str = xml2json(xml_str.c_str());
// //	end_time = getCurrentTime();
// 	cout << "time3: " << end_time - start_time << endl;
// 	outf << BOM << json_str;
// 	outf.close();


	inf.open("2.xml");
	outf.open("2.json");
	oss.clear();
	oss << inf.rdbuf();
	xml_str = oss.str();
	inf.close();
	//	start_time = getCurrentTime();
	json_str = xml2json(xml_str.c_str());
	//	end_time = getCurrentTime();
	cout << "time3: " << end_time - start_time << endl;
	outf << BOM << json_str;
	outf.close();



	QString _str(",   }");
	qDebug() << "_str:" << _str;
	QRegExp _re("(\\,)(\\s*)(\\})");
	_re.indexIn(",   }");
//	if (pos1 > -1) {
		QString s1 = _re.cap(1);
		QString s2 = _re.cap(2);
		QString s3 = _re.cap(3);
		//	s.chop(1);
		qDebug() << "s1:" << s1;
		qDebug() << "s2:" << s2;
		qDebug() << "s3:" << s3;
//	}
//	qDebug() << "s.chop(1):" << s.chop(1);
	_str.replace(_re, "\\3+}");
	qDebug() << _str;

	QRegExp rxlen("(\\d+)(?:\\s*)(cm|inch)");
	int pos = rxlen.indexIn("Length: 189cm");
	if (pos > -1) {
		QString value = rxlen.cap(1); // "189"
		QString unit = rxlen.cap(2);  // "cm"
		// ...
	}
	system("pause");
	return 0;
}
