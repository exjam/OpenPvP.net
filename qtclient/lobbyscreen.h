#ifndef LOBBY_SCREEN_H
#define LOBBY_SCREEN_H

#include <QWidget>
#include "ui_lobbyscreen.h"
#include "amf/variant.h"

class LobbyScreen : public QWidget
{
	Q_OBJECT

public:
	LobbyScreen(QWidget *parent = 0);
	~LobbyScreen();

	SummonerInfoWidget* getSummonerInfoWidget();

	void onGetStoreUrl(const amf::Variant& result);

public slots:
	void play();
	void home();
	void lore();
	void help();
	void store();
	void profile();
	void openUrl(const QString& url);

signals:
	void openStore(const QString& url);

private:
	Ui::LobbyScreen ui;
};

#endif
