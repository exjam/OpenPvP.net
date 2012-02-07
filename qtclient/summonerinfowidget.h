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

	void setName(const QString& value){
		ui.name->setText(value);
	}

	void setIpCount(double value){
		ui.ipCount->setText(QString("%1").arg(value));
	}

	void setRpCount(double value){
		ui.rpCount->setText(QString("%1").arg(value));
	}

public slots:
	void _store(){
		emit store();
	}

	void _profile(){
		emit profile();
	}

	void _lore(){
		emit lore();
	}

	void _help(){
		emit help();
	}

signals:
	void store();
	void profile();
	void lore();
	void help();

private:
	Ui::SummonerInfo ui;
};

#endif
