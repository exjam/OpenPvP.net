#ifndef LOBBY_SCREEN_H
#define LOBBY_SCREEN_H

#include <QWidget>
#include "ui_lobbyscreen.h"

class LobbyScreen : public QWidget
{
	Q_OBJECT

public:
	LobbyScreen(QWidget *parent = 0)
		: QWidget(parent)
	{
		ui.setupUi(this);
	}

	~LobbyScreen(){
	}

private:
	Ui::LobbyScreen ui;
};

#endif
