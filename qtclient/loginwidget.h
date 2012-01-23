#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QtGui/QMainWindow>

#include <QString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>
#include <QNetworkAccessManager>

#include <QMessageBox>

#include "ui_loginwidget.h"
#include "riotgames/platform/gameclient/domain/serversessionobject.h"

namespace amf {
	class Variant;
};

class LoginWidget : public QWidget
{
	Q_OBJECT

public:
	LoginWidget(QWidget *parent = 0, Qt::WFlags flags = 0);
	~LoginWidget();

public slots:
	void login();
	void replyFinished(QNetworkReply* reply);
	void sslErrors(QNetworkReply* reply, const QList<QSslError>& errors);

	void passwordChanged(const QString& str);
	void usernameChanged(const QString& str);
	
	void onClientConnected();
	void onLoginResult(amf::Variant* result);
	
private:
	void loginResult(amf::Variant* result);
	void updateLoginButton();
	void loginError(const QString& error);

signals:
	void loginComplete();
	void receiveLoginResult(amf::Variant* result);

private:
	QString mAuthToken;
	QString mIpAddress;
	int mLoginStage;
	QNetworkAccessManager* mNetworkMan;
	Ui::LoginWidget ui;
	riotgames::platform::gameclient::domain::ServerSessionObject* mSession;
};

#endif
