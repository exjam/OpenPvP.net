#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "alertdialog.h"
class StatusDialog;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = Qt::FramelessWindowHint);
	~MainWindow();

	int showAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons);

	void setStatusDialogTitle(const QString& title);
	void setStatusDialogMessage(const QString& message);
	
	void hideStatusDialog();
	void showStatusDialog(const QString& title, const QString& message);

private slots:
	void onLoginComplete();
	void onLoginDataPacket(amf::Variant* result);
	void onAvailableQueues(amf::Variant* result);

private:
	Ui::MainWindowClass ui;
	StatusDialog* mStatusDialog;
};

extern MainWindow* gMainWindow;

#endif // MAINWINDOW_H
