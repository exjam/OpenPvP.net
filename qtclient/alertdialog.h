#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include <QDialog>
#include "ui_alert.h"

class AlertDialog : public QDialog
{
	Q_OBJECT

public:
	enum Buttons {
		Ok = 1,
		Cancel = 1 << 1,
		Yes = 1 << 2,
		No = 1 << 3,
	};

	AlertDialog(const QString& title, const QString& message, Buttons buttons = Ok, QWidget *parent = 0, Qt::WFlags flags = Qt::FramelessWindowHint)
		: QDialog(parent, flags)
	{
		ui.setupUi(this);
		ui.title->setText(title);
		ui.text->setText(message);

		if(!(buttons & Ok))
			ui.ok->hide();

		if(!(buttons & Cancel))
			ui.cancel->hide();

		if(!(buttons & Yes))
			ui.yes->hide();

		if(!(buttons & No))
			ui.no->hide();
		
		setAttribute(Qt::WA_TranslucentBackground, true);
	}

	~AlertDialog(){
	}

private:
	Ui::AlertDialog ui;
};

#endif
