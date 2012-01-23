#include "mainwindow.h"
#include "statusdialog.h"

#include "riotgames/platform/gameclient/services/matchmakerservice.h"
#include "riotgames/platform/gameclient/services/clientfacadeservice.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), mStatusDialog(new StatusDialog(this))
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground, true);
	qApp->setStyleSheet(styleSheet());

	connect(ui.loginWidget, SIGNAL(loginComplete()), this, SLOT(onLoginComplete()));
}

MainWindow::~MainWindow()
{

}

/*
for logout:
loginService.logout(serverSessionToken)
channelset.logout
*/

void MainWindow::onLoginComplete(){
	using namespace riotgames::platform::gameclient::services;

	clientFacadeService.getLoginDataPacketForUser(std::bind(&MainWindow::onLoginDataPacket, this, std::placeholders::_1));
	matchmakerService.getAvailableQueues(std::bind(&MainWindow::onAvailableQueues, this, std::placeholders::_1));
	
	/*
	TODO:
	inventoryService.getSumonerActiveBoosts
	inventoryService.getAvailableChampions
	summonerRuneService.getSummonerRuneInventory
	matchmakerService.getAvailableQueues
	loginService.performLCDSHeartBeat(accountID, serverSessionToken, 1, fulltext date/time eg: "Mon Jan 23 2012 05:27:16 GMT+0000")
	summonerTeamService.createPlayer
	*/
}

void MainWindow::onLoginDataPacket(amf::Variant* result){
}

void MainWindow::onAvailableQueues(amf::Variant* result){
}

int MainWindow::showAlert(const QString& title, const QString& message, AlertDialog::Buttons buttons){
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
	mStatusDialog->hide();
}