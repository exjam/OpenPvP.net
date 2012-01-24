#ifndef SUMMONER_INFO_H
#define SUMMONER_INFO_H

#include <QWidget>
#include "ui_summonerinfo.h"

class SummonerInfoWidget : public QWidget
{
	Q_OBJECT

public:
	SummonerInfoWidget(QWidget *parent = 0)
		: QWidget(parent)
	{
		ui.setupUi(this);
	}

	~SummonerInfoWidget(){
	}

private:
	Ui::SummonerInfo ui;
};

#endif
