#include "mainwindow.h"
#include "statusdialog.h"

#include <QTimer>
#include <QDateTime>

#include "loginscreen.h"
#include "lobbyscreen.h"
#include "summonerinfowidget.h"

#include "flex/channelset.h"
#include "riotgames/platform/common/services/loginservice.h"
#include "riotgames/platform/common/services/inventoryservice.h"
#include "riotgames/platform/common/services/messagerouterservice.h"
#include "riotgames/platform/gameclient/services/matchmakerservice.h"
#include "riotgames/platform/gameclient/services/clientfacadeservice.h"
#include "riotgames/platform/gameclient/services/summonerruneservice.h"
#include "riotgames/platform/gameclient/services/teamservice.h"
#include "riotgames/platform/gameclient/services/summonerservice.h"
#include "riotgames/platform/gameclient/domain/inventory/activeboosts.h"

using namespace riotgames::platform::common::services;
using namespace riotgames::platform::gameclient::services;
using namespace riotgames::platform::gameclient::domain;

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), mStatusDialog(new StatusDialog(this)), mHeartbeatCount(0), mSummonerID(0.0)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground, true);
	qApp->setStyleSheet(styleSheet());
	
	mHeartbeatTimer = new QTimer();
	connect(mHeartbeatTimer, SIGNAL(timeout()), this, SLOT(performHeartbeat()));
	connect(this, SIGNAL(_internalAlert(QString,QString,AlertDialog::Buttons)), this, SLOT(doAlert(QString,QString,AlertDialog::Buttons)));
	connect(this, SIGNAL(_internalHideStatusDialog()), this, SLOT(doHideStatusDialog()));

	qRegisterMetaType< amf::Reference<ServerSessionObject> >("amf::Reference<ServerSessionObject>");
	changeScreen(new LoginScreen());
	connect(mCurrentScreen, SIGNAL(loginComplete(const amf::Reference<ServerSessionObject>&)), this, SLOT(onLoginComplete(const amf::Reference<ServerSessionObject>&)));
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

void MainWindow::onLoginComplete(const amf::Reference<ServerSessionObject>& session){	
	gMainWindow->setStatusDialogMessage("Receiving summoner data...");
	changeScreen(new LobbyScreen());

	mServerSession = session;

	flex::messaging::ChannelSet cs;
	cs.login(mServerSession->getAccountSummary()->getUsername(), mServerSession->getToken(), std::bind(&MainWindow::onChannelSetLogin, this, std::placeholders::_1));

	clientFacadeService.getLoginDataPacketForUser(std::bind(&MainWindow::onLoginDataPacket, this, std::placeholders::_1));
	matchmakerService.getAvailableQueues(std::bind(&MainWindow::onAvailableQueues, this, std::placeholders::_1));
	inventoryService.getSumonerActiveBoosts(std::bind(&MainWindow::onActiveBoosts, this, std::placeholders::_1));
	inventoryService.getAvailableChampions(std::bind(&MainWindow::onAvailableChampions, this, std::placeholders::_1));
	summonerTeamService.findOrCreateLocalPlayer(std::bind(&MainWindow::onCreatePlayer, this, std::placeholders::_1));
	
	performHeartbeat();
	mHeartbeatTimer->start(60000);
}

void MainWindow::onChannelSetLogin(const amf::Variant& message){
	messageRouterService.initialize(mServerSession);
	messageRouterService.addGameListener(std::bind(&MainWindow::onGameMessage, this, std::placeholders::_1));
	messageRouterService.addClientListener(std::bind(&MainWindow::onClientMessage, this, std::placeholders::_1));
	messageRouterService.addBroadcastListener(std::bind(&MainWindow::onBroadcastMessage, this, std::placeholders::_1));
}

void MainWindow::onGameMessage(const amf::Variant& message){
}

void MainWindow::onClientMessage(const amf::Variant& message){
}

void MainWindow::onBroadcastMessage(const amf::Variant& message){
}

void MainWindow::onActiveBoosts(const amf::Variant& result){
	using inventory::ActiveBoosts;
	amf::Reference<ActiveBoosts> boosts = result.toObject()->get("body").toObject();
	mSummonerID = boosts->getSummonerId();
	summonerRuneService.getSummonerRuneInventory(mSummonerID, std::bind(&MainWindow::onRuneInventory, this, std::placeholders::_1));
}

void MainWindow::onGetSummonerByAccountId(const amf::Variant& result){
}

void MainWindow::onGetSummonerByName(const amf::Variant& result){
}

void MainWindow::onRuneInventory(const amf::Variant& result){
}

void MainWindow::onAvailableChampions(const amf::Variant& result){
}

void MainWindow::onAvailableQueues(const amf::Variant& result){
}

void MainWindow::onCreatePlayer(const amf::Variant& result){
}

#include "riotgames/platform/gameclient/domain/logindatapacket.h"
void MainWindow::onLoginDataPacket(const amf::Variant& result){
	using riotgames::platform::gameclient::domain::LoginDataPacket;
	amf::Reference<LoginDataPacket> data = result.toObject()->get("body").toObject();
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

void MainWindow::onHeartbeatReply(const amf::Variant& result){
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
