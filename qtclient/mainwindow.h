#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

#include "alertdialog.h"

#include "amf/variant.h"
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
	void minimise();
	int doAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons);

private slots:
	void doHideStatusDialog();

	void onLoginComplete(const amf::Reference<ServerSessionObject>& session);

	void performHeartbeat();
	void onHeartbeatReply(const amf::Variant& result);

	void onLoginDataPacket(const amf::Variant& result);
	void onActiveBoosts(const amf::Variant& result);
	void onAvailableChampions(const amf::Variant& result);
	void onAvailableQueues(const amf::Variant& result);
	void onCreatePlayer(const amf::Variant& result);
	void onRuneInventory(const amf::Variant& result);
	void onGetSummonerByName(const amf::Variant& result);
	void onGetSummonerByAccountId(const amf::Variant& result);
	
	void onChannelSetLogin(const amf::Variant& message);
	void onGameMessage(const amf::Variant& message);
	void onClientMessage(const amf::Variant& message);
	void onBroadcastMessage(const amf::Variant& message);

signals:
	void _internalHideStatusDialog();
	void _internalAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons);

private:
	QWidget* mCurrentScreen;

	Ui::MainWindowClass ui;
	StatusDialog* mStatusDialog;
	
	QTimer* mHeartbeatTimer;
	int mHeartbeatCount;
	amf::Reference<ServerSessionObject> mServerSession;
	double mSummonerID;
};

extern MainWindow* gMainWindow;

#endif // MAINWINDOW_H
