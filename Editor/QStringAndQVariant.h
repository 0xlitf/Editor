#ifndef QStringAndQVariant_h__
#define QStringAndQVariant_h__
#include <QString>
#include <QVariant>

class QStringAndQVariant
{
public:
	QStringAndQVariant(void);
	~QStringAndQVariant(void);

	static QVariant stringToVariant(QVariant::Type type, const QString &);
	static QString vairantToString(const QVariant &);
};

#endif // QStringAndQVariant_h__
