#pragma once

#include "stringify.h"
#include "flex/consumer.h"
#include "../../gameclient/domain/serversessionobject.h"

#include <sstream>
#include <functional>

namespace riotgames {
	namespace platform {
		namespace common {
			namespace services {
				using namespace flex::messaging;
				using namespace riotgames::platform::gameclient::domain;

				class MessageRouterService {
					typedef std::function<void(const amf::Variant&)> MessageListener;
				public:
					MessageRouterService(){
						mGame = new Consumer();
						mClient = new Consumer();
						mBroadcast = new Consumer();
					}

					~MessageRouterService(){
						if(mGame)
							delete mGame;

						if(mClient)
							delete mClient;

						if(mBroadcast)
							delete mBroadcast;
					}

					void initialize(ServerSessionObject* object){
						std::string accountId = stringify((unsigned int)object->getAccountSummary()->getAccountId());

						mGame->setDestination("messagingDestination");
						mGame->subscribe("gn-" + accountId);
						
						mClient->setDestination("messagingDestination");
						mClient->subscribe("cn-" + accountId);
						
						mBroadcast->setDestination("messagingDestination");
						mBroadcast->subscribe("bc-" + accountId);
					}

					void addGameListener(const MessageListener& listener){
						mGame->addListener(listener);
					}

					void addClientListener(const MessageListener& listener){
						mClient->addListener(listener);
					}

					void addBroadcastListener(const MessageListener& listener){
						mBroadcast->addListener(listener);
					}

				private:
					Consumer* mGame;
					Consumer* mClient;
					Consumer* mBroadcast;
				};

				extern MessageRouterService messageRouterService;
			};
		};
	};
};

/*
Example Notifications:

Recv>AMF3_COMMAND
{ object DSA
	body = { object com.riotgames.platform.messaging.StoreFulfillmentNotification
		data = { object com.riotgames.platform.catalog.runes.RuneQuantity
			dataVersion = 0
			futureData = (null)
			quantity = 1
			runeId = 5058
		}
		inventoryType = "RUNE"
		ip = 4770
		rp = 474
	}
	clientId = "cn-*"
	destination = "messagingDestination"
	headers = { object 
		DSSubtopic = "cn-*"
	}
	messageId = "*"
	timestamp = *
}
Recv>AMF3_COMMAND
{ object DSA
	body = { object com.riotgames.platform.messaging.StoreAccountBalanceNotification
		ip = 4755
		rp = 474
	}
	clientId = "cn-*"
	destination = "messagingDestination"
	headers = { object 
		DSSubtopic = "cn-*"
	}
	messageId = "*"
	timestamp = *
}
*/