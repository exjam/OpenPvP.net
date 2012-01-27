#include "mainwindow.h"
#include "statusdialog.h"

#include <QTimer>
#include <QDateTime>

#include "riotgames/platform/common/services/loginservice.h"
#include "riotgames/platform/common/services/inventoryservice.h"
#include "riotgames/platform/gameclient/services/matchmakerservice.h"
#include "riotgames/platform/gameclient/services/clientfacadeservice.h"
#include "riotgames/platform/gameclient/services/summonerruneservice.h"
#include "riotgames/platform/gameclient/services/teamservice.h"
#include "riotgames/platform/gameclient/services/summonerservice.h"
#include "riotgames/platform/gameclient/domain/inventory/activeboosts.h"

using namespace riotgames::platform::common::services;
using namespace riotgames::platform::gameclient::services;
using namespace riotgames::platform::gameclient::domain;
#include "loginscreen.h"
#include "lobbyscreen.h"
#include "summonerinfowidget.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), mStatusDialog(new StatusDialog(this)), mServerSession(0), mHeartbeatCount(0), mSummonerID(0.0)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground, true);
	qApp->setStyleSheet(styleSheet());
	
	mHeartbeatTimer = new QTimer();
	connect(mHeartbeatTimer, SIGNAL(timeout()), this, SLOT(performHeartbeat()));
	connect(this, SIGNAL(_internalAlert(QString,QString,AlertDialog::Buttons)), this, SLOT(doAlert(QString,QString,AlertDialog::Buttons)));
	connect(this, SIGNAL(_internalHideStatusDialog()), this, SLOT(doHideStatusDialog()));

	changeScreen(new LoginScreen());
	connect(mCurrentScreen, SIGNAL(loginComplete(ServerSessionObject*)), this, SLOT(onLoginComplete(ServerSessionObject*)));
}

MainWindow::~MainWindow()
{
}

/*
for logout:
loginService.logout(serverSessionToken)
channelset.logout
*/

void MainWindow::changeScreen(QWidget* screen){
	mCurrentScreen = screen;

	QLayout* layout = ui.screenContainer->layout();
	layout->removeWidget(layout->itemAt(0)->widget());
	layout->addWidget(mCurrentScreen);
}

void MainWindow::onLoginComplete(ServerSessionObject* session){	
	gMainWindow->setStatusDialogMessage("Receiving summoner data...");
	changeScreen(new LobbyScreen());

	mServerSession = session;

	clientFacadeService.getLoginDataPacketForUser(std::bind(&MainWindow::onLoginDataPacket, this, std::placeholders::_1));
	matchmakerService.getAvailableQueues(std::bind(&MainWindow::onAvailableQueues, this, std::placeholders::_1));
	inventoryService.getSumonerActiveBoosts(std::bind(&MainWindow::onActiveBoosts, this, std::placeholders::_1));
	inventoryService.getAvailableChampions(std::bind(&MainWindow::onAvailableChampions, this, std::placeholders::_1));
	summonerTeamService.findOrCreateLocalPlayer(std::bind(&MainWindow::onCreatePlayer, this, std::placeholders::_1));
	
	performHeartbeat();
	mHeartbeatTimer->start(60000);
}

void MainWindow::onActiveBoosts(amf::Variant* result){
	inventory::ActiveBoosts* boosts = (inventory::ActiveBoosts*)result->toObject()->get("body")->toObject();
	mSummonerID = boosts->getSummonerId();
	summonerRuneService.getSummonerRuneInventory(mSummonerID, std::bind(&MainWindow::onRuneInventory, this, std::placeholders::_1));
}

void MainWindow::onGetSummonerByAccountId(amf::Variant* result){
}

void MainWindow::onGetSummonerByName(amf::Variant* result){
}

void MainWindow::onRuneInventory(amf::Variant* result){
}

void MainWindow::onAvailableChampions(amf::Variant* result){
}

void MainWindow::onAvailableQueues(amf::Variant* result){
}

void MainWindow::onCreatePlayer(amf::Variant* result){
}

#include "riotgames/platform/gameclient/domain/logindatapacket.h"
void MainWindow::onLoginDataPacket(amf::Variant* result){
	using riotgames::platform::gameclient::domain::LoginDataPacket;
	LoginDataPacket* data = (LoginDataPacket*)result->toObject()->get("body")->toObject();
	auto summonerData = data->getAllSummonerData();
	if(summonerData){
		auto summoner = summonerData->getSummoner();
	
		if(summoner){
			LobbyScreen* screen = (LobbyScreen*)mCurrentScreen;
			SummonerInfoWidget* widget = screen->getSummonerInfoWidget();
			widget->setRpCount(data->getRpBalance());
			widget->setIpCount(data->getIpBalance());
			widget->setName(QString::fromStdString(summoner->getName()));
			hideStatusDialog();
		}
	}
}

void MainWindow::onHeartbeatReply(amf::Variant* result){
}

void MainWindow::performHeartbeat(){
	using namespace riotgames::platform::common::services;

	QString datetime = QDateTime::currentDateTime().toString(Qt::ISODate);
	datetime.replace(4, 1, '/');
	datetime.replace(7, 1, '/');
	datetime.replace(10, 1, ' ');

	int lastSep = datetime.lastIndexOf(':');
	if(lastSep > 19){
		datetime.insert(19, " UTC");
		datetime.remove(datetime.lastIndexOf(':'), 1);
	}else{
		datetime.append(" UTC+0000");
	}

	loginService.performLCDSHeartBeat(
		mServerSession->getAccountSummary()->getAccountId(), mServerSession->getToken(), ++mHeartbeatCount, datetime.toStdString(),
		std::bind(&MainWindow::onHeartbeatReply, this, std::placeholders::_1));
}

void MainWindow::showAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons){
	emit _internalAlert(title, message, buttons);
}

int MainWindow::doAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons){
	hideStatusDialog();

	AlertDialog* dlg = new AlertDialog(title, message, buttons, this);
	dlg->setWindowModality(Qt::WindowModal);
	return dlg->exec();
}

void MainWindow::setStatusDialogTitle(const QString& title){
	mStatusDialog->setTitle(title);
}

void MainWindow::setStatusDialogMessage(const QString& message){
	mStatusDialog->setMessage(message);
}

void MainWindow::showStatusDialog(const QString& title, const QString& message){
	setStatusDialogTitle(title);
	setStatusDialogMessage(message);
	mStatusDialog->setModal(true);
	mStatusDialog->setWindowModality(Qt::WindowModal);
	mStatusDialog->show();
}

void MainWindow::hideStatusDialog(){
	emit _internalHideStatusDialog();
}

void MainWindow::doHideStatusDialog(){
	mStatusDialog->hide();
}

void MainWindow::minimise(){
	setWindowState(windowState() | Qt::WindowMinimized);
}
