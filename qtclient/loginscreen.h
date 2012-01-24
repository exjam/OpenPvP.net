#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <QtGui/QMainWindow>

#include <QString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>
#include <QNetworkAccessManager>

#include <QMessageBox>

#include "ui_loginscreen.h"
#include "riotgames/platform/gameclient/domain/serversessionobject.h"

namespace amf {
	class Variant;
};

using riotgames::platform::gameclient::domain::ServerSessionObject;

class LoginScreen : public QWidget
{
	Q_OBJECT

public:
	LoginScreen(QWidget *parent = 0, Qt::WFlags flags = 0);
	~LoginScreen();

public slots:
	void login();
	void replyFinished(QNetworkReply* reply);
	void sslErrors(QNetworkReply* reply, const QList<QSslError>& errors);

	void passwordChanged(const QString& str);
	void usernameChanged(const QString& str);
	
	void onClientConnected();

private:
	void onLoginResult(amf::Variant* result);
	void updateLoginButton();
	void loginError(const QString& error);

signals:
	void loginComplete(ServerSessionObject* session);
	void receiveLoginResult(amf::Variant* result);

private:
	QString mAuthToken;
	QString mIpAddress;
	int mLoginStage;
	QNetworkAccessManager mNetworkMan;
	Ui::LoginScreen ui;
};

#endif
