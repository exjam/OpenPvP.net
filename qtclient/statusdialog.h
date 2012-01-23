#ifndef STATUSDIALOG_H
#define STATUSDIALOG_H

#include <QDialog>
#include "ui_alert.h"

class StatusDialog : public QDialog
{
	Q_OBJECT

public:
	StatusDialog(QWidget *parent = 0, Qt::WFlags flags = Qt::FramelessWindowHint)
		: QDialog(parent, flags)
	{
		ui.setupUi(this);

		ui.line_bot->hide();
		ui.buttons->hide();

		setAttribute(Qt::WA_TranslucentBackground, true);
	}

	~StatusDialog(){
	}

	void setTitle(const QString& title){
		ui.title->setText(title);
	}

	void setMessage(const QString& message){
		ui.text->setText(message);
	}

private:
	Ui::AlertDialog ui;
};

#endif
