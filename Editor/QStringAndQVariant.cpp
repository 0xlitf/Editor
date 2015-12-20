#include "QStringAndQVariant.h"
#include <QRectF>
#include <QStringList>
#include <QColor>
#include <Qt>
QStringAndQVariant::QStringAndQVariant(void)
{
}

QStringAndQVariant::~QStringAndQVariant(void)
{
}


QVariant QStringAndQVariant::stringToVariant(QVariant::Type type, const QString &str)
{
	switch(type)
	{
	case QVariant::Bool:
		{
			if(str.compare("true",Qt::CaseInsensitive)==0)
			{
				return QVariant(true);
			}
			else
			{
				return QVariant(false);
			}
		}
	case QVariant::PointF:
		{
			QStringList _argv=str.split(",");
			if(_argv.size()!=2)
			{
				return QVariant(QPointF());
			}
			bool _ok = false;
			double _x = _argv[0].toDouble(&_ok);
			if(!_ok) _x = 0.0;
			double _y = _argv[1].toDouble(&_ok);
			if(!_ok) _y = 0.0;
			return QVariant(QPointF(_x,_y));
		}
	case QVariant::SizeF:
		{
			QStringList _argv=str.split(",");
			if(_argv.size()!=2)
			{
				return QVariant(QSizeF());
			}
			bool _ok = false;
			double _w = _argv[0].toDouble(&_ok);
			if(!_ok) _w = 0.0;
			double _h = _argv[1].toDouble(&_ok);
			if(!_ok) _h = 0.0;
			return QVariant(QSizeF(_w,_h));
		}
	case QVariant::RectF:
		{
			QStringList _argv=str.split(",");
			if(_argv.size()!=4)
			{
				return QVariant(QRectF());
			}
			bool _ok = false;
			double _x = _argv[0].toDouble(&_ok);
			if(!_ok) _x = 0.0;
			double _y = _argv[1].toDouble(&_ok);
			if(!_ok) _y = 0.0;
			double _w = _argv[2].toDouble(&_ok);
			if(!_ok) _w = 0.0;
			double _h = _argv[3].toDouble(&_ok);
			if(!_ok) _h = 0.0;
			return QVariant(QRectF(_x,_y,_w,_h));
		}
	case QVariant::Color:
		{
			QStringList _argv=str.split(",");
			if(_argv.size()!=4)
			{
				return QVariant(QColor());
			}
			bool _ok = false;
			int _red = _argv[0].toInt(&_ok);
			if(!_ok) _red = 0;
			int _green = _argv[1].toInt(&_ok);
			if(!_ok) _green = 0;
			int _black = _argv[2].toInt(&_ok);
			if(!_ok) _black = 0;
			int _alpha = _argv[3].toInt(&_ok);
			if(!_ok) _alpha = 0;
			return QVariant(QColor(_red,_green,_black,_alpha));
		}
	case QVariant::Int:
		{
			QVariant(str.toInt());
		}
	case QVariant::String:
		{
			QString _strcopy=str;
			_strcopy.replace("&lt;","<");
			_strcopy.replace("&rt;",">");			
			_strcopy.replace("&apos;","'");
			_strcopy.replace("&quot;","\"");
			_strcopy.replace("&amp;","&");
			return QVariant(_strcopy);
		}
	default:
		return QVariant(str);
	}
	return QVariant();
}

QString QStringAndQVariant::vairantToString(const QVariant &var)
{
	switch(var.type())
	{
	case QVariant::Bool:
		{
			bool _ok = var.value<bool>();
			if(_ok)
			{
				return "true";
			}
			else
			{
				return "false";
			}
		}
	case QVariant::PointF:
		{
			QPointF _pf = var.value<QPointF>();
			return QString("%1,%2").arg(_pf.x()).arg(_pf.y());
		}
	case QVariant::SizeF:
		{
			QSizeF _sizef = var.value<QSizeF>();
			return QString("%1,%2").arg(_sizef.width()).arg(_sizef.height());
		}
	case QVariant::RectF:
		{
			QRectF _rectf = var.value<QRectF>();
			return QString("%1,%2,%3,%4").arg(_rectf.x()).arg(_rectf.y()).arg(_rectf.width()).arg(_rectf.height());
		}
	case QVariant::Color:
		{
			QColor _color = var.value<QColor>();
			return QString("%1,%2,%3,%4").arg(_color.red()).arg(_color.green()).arg(_color.blue()).arg(_color.alpha());
		}
	case QVariant::String:
		{
			QString _strcopy = var.value<QString>();
			_strcopy.replace("&","&amp;");
			_strcopy.replace("<","&lt;");
			_strcopy.replace(">","&rt;");			
			_strcopy.replace("'","&apos;");
			_strcopy.replace("\"","&quot;");
			return _strcopy;
		}
	default:
		return var.toString();
		break;
	}
	return QString();
}