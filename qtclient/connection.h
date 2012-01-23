#ifndef CONNECTION_H
#define CONNECTION_H

#include "rtmp/client.h"
#include "amf/variant.h"

#include <QString>
#include <QThread>
#include <QMessageBox>
#include <functional>

class Connection : public QThread {
	Q_OBJECT

public:
	Connection()
		: mClient(rtmp::Client::instance())
	{
		mClient.registerEventHandler(std::bind(&Connection::clientEvent, this, std::placeholders::_1, std::placeholders::_2));
	}

	void connect(const QString& url){
		mUrl = url;
		start();
	}
	
	void run(){
		if(mClient.connect(mUrl.toStdString()))
			mClient.start();
		else
			emit disconnected();
	}

protected:
	void clientEvent(int evt, amf::Variant* data){
		switch(evt){
			case rtmp::Client::EVT_CONNECT:
				emit connected();
				break;
			case rtmp::Client::EVT_ERROR:
			case rtmp::Client::EVT_DISCONNECT:
				emit disconnected();
				break;
			default:
				QMessageBox::information(NULL, "Unhandled Client Event", QString("Unhandled event %1  from rtmp client.").arg(evt));
		}
	}

signals:
	void connected();
	void disconnected();

private:
	QString mUrl;
	rtmp::Client& mClient;
};

extern Connection* gConnection;

#endif
