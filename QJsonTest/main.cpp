
#include <QtCore/QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QFile>
#include <QVariant>
#include <QVariantMap>
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
//QJsonObject
/*	qDebug() << "//QJsonObject";
	//生成json
	QJsonObject json;
	json.insert("name", QString("Qt"));
	json.insert("version",5);
	json.insert("windows",true);

	QJsonDocument document;
	document.setObject(json);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
	qDebug() << "byteArray:" << byteArray;
	QString jsonStr(byteArray);
	qDebug() << "jsonStr:" << jsonStr;
	//解析json
	QJsonParseError jsonError;
	QJsonDocument parseDocument = QJsonDocument::fromJson(byteArray, &jsonError);
	if (jsonError.error==QJsonParseError::NoError)
	{
		if (parseDocument.isObject())
		{
			QJsonObject obj = parseDocument.object();
			if (obj.contains("name"))
			{
				QJsonValue nameValue = obj.take("name");
				if (nameValue.isString())
				{
					QString name = nameValue.toString();
					qDebug() << "name:" << name;
				}
				if (obj.contains("version"))
				{
					QJsonValue versionValue = obj.take("version");
					if (versionValue.isDouble())
					{
						int version = versionValue.toVariant().toInt();
						qDebug() << "version:" << version;
					}
				}
				if (obj.contains("windows"))
				{
					QJsonValue windowsValue = obj.take("windows");
					if (windowsValue.isBool())
					{
						bool flag = windowsValue.toBool();
						qDebug() << "flag:" << flag;
					}
				}
			}
		}
	}
//QJsonArray 
	qDebug() << "//QJsonArray";
	//生成json
	QJsonArray json_array;
	json_array.insert(0, QString("Qt"));
	json_array.insert(1, QString("version"));
	json_array.insert(2, true);

	QJsonDocument jsonDocument;
	jsonDocument.setArray(json_array);
	QByteArray byte_array = jsonDocument.toJson(QJsonDocument::Compact);
	qDebug() << "byte_array:" << byte_array;
	QString json_str(byte_array);
	qDebug() << "json_str:" << json_str;
	//解析
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array, &json_error);
	if (json_error.error == QJsonParseError::NoError)
	{
		if (parse_doucment.isArray())
		{
			QJsonArray array = parse_doucment.array();
			int size = array.size();
			for (int i = 0; i < size; ++i)
			{
				QJsonValue value = array.at(i);
				qDebug() << value;
				if (value.isString())
				{
					QString name = value.toString();
					qDebug() << i << ":" << name;
				}
				else if (value.isBool())
				{
					bool flag = value.toBool();
					qDebug() << i << ":" << flag;
				}
			}
		}
	}
//QFile to QJson
	qDebug() << "//QFile to QJson";
	QFile _file("1.json");
	if (!_file.open(QIODevice::ReadWrite))
	{
		return 0;
	}
	QTextStream _stream(&_file);
	QString _str=_stream.readAll();
	QJsonParseError _err;
	QVariantMap _varMap;
	QJsonDocument _doc = QJsonDocument::fromJson(_str.toUtf8(),&_err);
	if (_err.error==QJsonParseError::NoError)
	{
		if (_doc.isObject())
		{
			_varMap = _doc.toVariant().toMap();
//			qDebug() << _varMap["screen"];


		}
	}
	QJsonObject _obj = QJsonObject::fromVariantMap(_varMap);

	QJsonValue _value = _obj.value("screen");
	QJsonObject _subObj=_value.toObject();
	qDebug() << "_subObj.value(\"@id\"):" << _subObj.value("@id");
//	qDebug() << "_obj.value(\"screen\"):" << _obj.value("screen");

	*/
	qDebug() << "*************************************************";

	QString _str("{\"page\": {\
					\"name\": \"EditorPage_0\",\
					\"property\" : [\
	{\"type\": \"10\", \"name\" : \"BackgroundPixmap\", \"value\" : \"\"}\
					],\
					\"page\": {\
		\"name\": \"EditorPage_0\",\
			\"property\" : [\
		{\"type\": \"10\", \"name\" : \"BackgroundPixmap\", \"value\" : \"\"}\
			]\
	}\
						}}");
	QJsonDocument _doc = QJsonDocument::fromJson(_str.toUtf8());
	QJsonObject _obj = _doc.object();
	QJsonObject _valObj = _obj.value("page").toObject();
//	QVariantMap _outmap = _obj.toVariantMap();
	QJsonObject::iterator _it = _obj.begin();
	QJsonObject::iterator _valIt = _valObj.begin();
//	QVariantMap _map = _obj.value("page").toObject().toVariantMap();
//	QVariantMap::iterator _it = _map.begin();
	while (_valIt != _valObj.end()){
		qDebug() << "_it.key():" << _valIt.key();
		qDebug() << "_it.value():" << _valIt.value();

		++_valIt;
	}


	return a.exec();
}
