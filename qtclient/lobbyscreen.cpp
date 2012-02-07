#include "lobbyscreen.h"
#include "webpage.h"

#include "riotgames/platform/common/services/loginservice.h"
using namespace riotgames::platform::common::services;

LobbyScreen::LobbyScreen(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(this, SIGNAL(openStore(QString)), this, SLOT(openUrl(QString)));
	
	ui.webView->setPage(new WebPage());
	ui.webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
	
	openUrl("http://leagueoflegends.com/board/forumdisplay.php?f=2");
}

LobbyScreen::~LobbyScreen(){
}

SummonerInfoWidget* LobbyScreen::getSummonerInfoWidget(){
	return ui.summonerInfo;
}

void LobbyScreen::openUrl(const QString& url){
	ui.webView->load(QUrl(url));
}

void LobbyScreen::onGetStoreUrl(const amf::Variant& result){
	emit openStore(QString::fromStdString(result.toObject()->get("body")));
}

void LobbyScreen::store(){
	loginService.getStoreUrl(std::bind(&LobbyScreen::onGetStoreUrl, this, std::placeholders::_1));
}

void LobbyScreen::profile(){
}

void LobbyScreen::lore(){
}

void LobbyScreen::help(){
}

void LobbyScreen::play(){
}

void LobbyScreen::home(){
}
