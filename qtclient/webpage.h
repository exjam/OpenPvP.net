#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QFile>
#include <QDebug>
#include <QWebPage>
#include <QWebFrame>
#include <QDateTime>
#include <QAbstractNetworkCache>

class ParentSandboxBridge : public QObject { 
    Q_OBJECT
	Q_PROPERTY(QVariant storeUnavailableMessage READ storeUnavailableMessage);

public:
    ParentSandboxBridge(){
	}

public slots:
    Q_INVOKABLE bool testIfUserIsInQueue(){
		return true;
	}

    Q_INVOKABLE bool testIsNameValid(const QString& name){
		/*  
		var _loc_2:* = this.wordFilter.containsOffensiveWords(param1, true);
        var _loc_3:* = this.wordFilter.containsRestrictedWords(param1, true);
        var _loc_4:* = this.wordFilter.getInvalidCharacters(param1);
        return !_loc_2 && !_loc_3 && _loc_4 == null;
		*/

		return true;
	}

    Q_INVOKABLE void openInventoryBrowser(const QString& item){
		openInventoryBrowser(item, "");
	}

    Q_INVOKABLE void openInventoryBrowser(const QString& item, const QString& skin){
	}

    Q_INVOKABLE void showInternalBrowser(const QString& purchaseRpUrl){
		showInternalBrowser(purchaseRpUrl, "");
	}

    Q_INVOKABLE void showInternalBrowser(const QString& purchaseRpUrl, const QString& returnUrl){
	}

    Q_INVOKABLE void hideInternalBrowser(){
	}

    Q_INVOKABLE void updateRiotPoints(double rp){
	}

    Q_INVOKABLE void updateInfluencePoints(double rp){
	}

    Q_INVOKABLE void playChooseMe(const QString& skin){
	}

    Q_INVOKABLE void setAJAXHttpStatus(int status){
	}

    Q_INVOKABLE void openExternalURL(const QString& url){
	}

    Q_INVOKABLE void sessionExpired(){
		sessionExpired("", "");
	}

    Q_INVOKABLE void sessionExpired(const QString& s1){
		sessionExpired(s1, "");
	}

    Q_INVOKABLE void sessionExpired(const QString& s1, const QString& s2){
	}

	QVariant storeUnavailableMessage(){
		return QVariant::fromValue(QString("Store unavailable."));
	}
};

class WebCache : public QAbstractNetworkCache {
	Q_OBJECT

public:
	WebCache(QAbstractNetworkCache* oldCache)
		: mOldCache(oldCache)
	{
	}

	~WebCache(){
	}

	qint64 cacheSize() const {
		if(mOldCache)
			return mOldCache->cacheSize();
		else
			return 100 * 1024 * 1024;
	}

	QIODevice* data(const QUrl& url){
		if(QFile* file = isLocalCache(url.toString()))
			return file;
		
		if(mOldCache)
			return mOldCache->data(url);
		else
			return NULL;
	}

	void insert(QIODevice * device){
		if(mOldCache)
			mOldCache->insert(device);
	}

	QNetworkCacheMetaData metaData(const QUrl& url){
		QString str = url.toString();
		if(QFile* file = isLocalCache(str)){
			delete file;
			QNetworkCacheMetaData meta;
			meta.setUrl(url);
			meta.setExpirationDate(QDateTime::currentDateTime().addDays(1));
			return meta;
		}

		if(mOldCache)
			return mOldCache->metaData(url);
		else
			return QNetworkCacheMetaData();
	}

	QIODevice* prepare(const QNetworkCacheMetaData& metaData){
		if(QFile* file = isLocalCache(metaData.url().toString())){
			delete file;
			return NULL;
		}
		
		if(mOldCache)
			return mOldCache->prepare(metaData);
		else
			return NULL;
	}

	bool remove(const QUrl& url){
		if(mOldCache)
			return mOldCache->remove(url);
		else
			return true;
	}

	void updateMetaData(const QNetworkCacheMetaData& metaData){
		if(mOldCache)
			mOldCache->clear();
	}

	void clear(){
		if(mOldCache)
			mOldCache->clear();
	}

private:
	QFile* isLocalCache(const QString& url){
		QString str = url;
		int pos = str.indexOf("/img/");
		if(pos > 0){
			str = str.mid(pos + 5);
			str.insert(0, "assets/storeImages/");
			pos = str.indexOf('?');
			if(pos > 0)
				str = str.left(pos);
			
			QFile* file = new QFile(str);
			if(file->open(QIODevice::ReadOnly))
				return file;

			delete file;
		}

		return NULL;
	}

private:
	QAbstractNetworkCache* mOldCache;
};

class WebPage : public QWebPage {
	Q_OBJECT

public:
	WebPage(QObject* parent = 0)
		: QWebPage(parent)
	{
		mBridge = new ParentSandboxBridge();
		connect(mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(onJavaScriptWindowObjectCleared()));

		networkAccessManager()->setCache(new WebCache(networkAccessManager()->cache()));
	}

	virtual void javaScriptConsoleMessage(const QString & message, int lineNumber, const QString & sourceID){
		qDebug() << " Line:" << lineNumber << " SourceID:" << sourceID << " " << message;
		QWebPage::javaScriptConsoleMessage(message, lineNumber, sourceID);
	}

public slots:
	void onJavaScriptWindowObjectCleared(){
		mainFrame()->addToJavaScriptWindowObject("parentSandboxBridge", mBridge);
	}

private:
	ParentSandboxBridge* mBridge;
};

#endif
