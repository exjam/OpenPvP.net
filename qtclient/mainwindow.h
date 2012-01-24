#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "alertdialog.h"
#include "riotgames/platform/gameclient/domain/serversessionobject.h"

class StatusDialog;
using riotgames::platform::gameclient::domain::ServerSessionObject;

class QTimer;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = Qt::FramelessWindowHint);
	~MainWindow();

	void setStatusDialogTitle(const QString& title);
	void setStatusDialogMessage(const QString& message);
	
	void hideStatusDialog();
	void showStatusDialog(const QString& title, const QString& message);
	
	void showAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons);

	void changeScreen(QWidget* screen);
public slots:
	int doAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons);

private slots:
	void onLoginComplete(ServerSessionObject* session);

	void performHeartbeat();
	void onHeartbeatReply(amf::Variant* result);

	void onLoginDataPacket(amf::Variant* result);
	void onActiveBoosts(amf::Variant* result);
	void onAvailableChampions(amf::Variant* result);
	void onAvailableQueues(amf::Variant* result);
	void onCreatePlayer(amf::Variant* result);
	void onRuneInventory(amf::Variant* result);

signals:
	void _internalAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons);

private:
	QWidget* mCurrentScreen;

	Ui::MainWindowClass ui;
	StatusDialog* mStatusDialog;
	
	QTimer* mHeartbeatTimer;
	int mHeartbeatCount;
	ServerSessionObject* mServerSession;
	double mSummonerID;
};

extern MainWindow* gMainWindow;

#endif // MAINWINDOW_H
