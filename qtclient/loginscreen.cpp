#include "loginscreen.h"
#include "mainwindow.h"
#include "connection.h"

#include "amf/log.h"
#include "flex/channelset.h"
#include "riotgames/platform/common/services/loginservice.h"
#include "riotgames/platform/common/services/messagerouterservice.h"

LoginScreen::LoginScreen(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), mLoginStage(0), mNetworkMan(this)
{
	ui.setupUi(this);

	connect(&mNetworkMan, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	connect(&mNetworkMan, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));

	connect(gConnection, SIGNAL(connected()), this, SLOT(onClientConnected()));
}

LoginScreen::~LoginScreen(){
}

void LoginScreen::onLoginResult(amf::Variant* result){
	amf::Object* object = result->toObject();
	if(object->name().compare("flex.messaging.messages.ErrorMessage") == 0){
		QString str = QString("Error in %1:\n%2")
			.arg(QString::fromStdString(object->get("faultCode")->toString()))
			.arg(QString::fromStdString(object->get("faultString")->toString()));

		gMainWindow->showAlert("Error", str, AlertDialog::Ok);
	}else{
		amf::log::obj obj;
		obj << result;

		ServerSessionObject* session = (ServerSessionObject*)object->get("body")->copy()->toObject();

		flex::messaging::ChannelSet cs;
		cs.login(session->getAccountSummary()->getUsername(), session->getToken());

		riotgames::platform::common::services::messageRouterService.initialize(session);

		emit loginComplete(session);
	}
}

void LoginScreen::onClientConnected(){
	riotgames::platform::common::services::loginService.login(
		ui.username->text().toStdString(),
		ui.password->text().toStdString(),
		mAuthToken.toStdString(),
		"lolclient.lol.riotgames.com",
		mIpAddress.toStdString(),
		"en_US",
		"1.52.12_01_16_15_31",
		std::bind(&LoginScreen::onLoginResult, this, std::placeholders::_1));
}

void LoginScreen::sslErrors(QNetworkReply* reply, const QList<QSslError>& errors){
	mLoginStage = 0;
	updateLoginButton();
}

void LoginScreen::replyFinished(QNetworkReply* reply){
	if(mLoginStage == 1){
		if(reply->error() != QNetworkReply::NoError && reply->error() != QNetworkReply::ContentOperationNotPermittedError)
			return loginError("Could not connect to login server.");

		QString data = QString::fromAscii(reply->readAll().data());
		int pos = data.indexOf("\"token\":\"");
		if(pos == -1)
			return loginError("Invalid username/password combination. Please try again.");

		pos += strlen("\"token\":\"");
		mAuthToken = data.mid(pos, data.indexOf("\"", pos) - pos);

		mLoginStage = 2;
		mNetworkMan.get(QNetworkRequest(QUrl("http://ll.leagueoflegends.com/services/connection_info")));
	}else if(mLoginStage == 2){
		if(reply->error() != QNetworkReply::NoError)
			return loginError("Coult not retrieve connection info.");

		QString data = QString::fromAscii(reply->readAll().data());
		int pos = data.indexOf("\"ip_address\":\"");
		if(pos == -1)
			return loginError("Invalid connection info.");

		pos += strlen("\"ip_address\":\"");
		mIpAddress = data.mid(pos, data.indexOf("\"", pos) - pos);

		gConnection->connect("rtmps://prod.na1.lol.riotgames.com:2099");
	}
}

void LoginScreen::login(){
	if(!ui.login->isEnabled())
		return;

	gMainWindow->showStatusDialog("Retrieveing data from server", "Loading...");

	mLoginStage = 1;
	updateLoginButton();

	QString payload = QString("user=%1,password=%2").arg(ui.username->text()).arg(ui.password->text());
	QString data = QString("payload=%1").arg(QString(payload.toUtf8().toPercentEncoding()));

	QNetworkRequest req(QUrl("https://lq.na1.lol.riotgames.com/login-queue/rest/queue/authenticate"));
	req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant::fromValue(QString("application/x-www-form-urlencoded")));
	mNetworkMan.post(req, data.toUtf8());
}

void LoginScreen::passwordChanged(const QString& str){
	updateLoginButton();
}

void LoginScreen::usernameChanged(const QString& str){
	updateLoginButton();
}

void LoginScreen::updateLoginButton(){
	if(mLoginStage)
		ui.login->setEnabled(false);
	else
		ui.login->setEnabled(ui.username->text().length() && ui.password->text().length());
}

void LoginScreen::loginError(const QString& error){
	gMainWindow->hideStatusDialog();

	mLoginStage = 0;
	updateLoginButton();
	gMainWindow->showAlert("Login Error", error, AlertDialog::Ok);
}
