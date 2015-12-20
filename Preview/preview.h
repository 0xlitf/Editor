#ifndef PREVIEW_H
#define PREVIEW_H

#include <QtWidgets/QMainWindow>
#include "ui_preview.h"

class Preview : public QMainWindow
{
	Q_OBJECT

public:
	Preview(QWidget *parent = 0);
	~Preview();

private:
	Ui::PreviewClass ui;
};

#endif // PREVIEW_H
