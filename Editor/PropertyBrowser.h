#ifndef PropertyBrowser_h__
#define PropertyBrowser_h__
#include <QtWidgets/QWidget>
#include <QVariant>

class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtTreePropertyBrowser;
class QtProperty;
class QPushButton;


class PropertyBrowser :	public QWidget
{
	Q_OBJECT
public:
	PropertyBrowser(QWidget *parent=0);
	~PropertyBrowser(void);

	QObject *getCurrentObject()const
	{
		return m_currentObj;
	}
	void updatePropertyValue();

	void setCurrentObject(QObject *obj);


	protected slots:
		void propertyChanged(QtProperty *, const QVariant);

signals:
		void objNameChanged();
		void editScriptClicked();
		void delScriptClicked();
		
private:
	QObject *m_currentObj;

	QtVariantPropertyManager *m_variantManager;
	QtVariantEditorFactory *m_variantFactory;
	QtTreePropertyBrowser *m_variantEditor;

	QPushButton *m_btnEditScript, *m_btnDelScript;

};
#endif // PropertyBrowser_h__
