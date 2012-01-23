#pragma once

#include "types.h"
#include "rtmp/client.h"
#include "rtmp/messages.h"
#include "flex/messages.h"

#include <iostream>
#include <vector>
#include <functional>

namespace flex {
	namespace messaging {
		class Consumer {
			typedef std::function<void(amf::Variant*)> MessageListener;

		public:
			Consumer(){
			}

			std::string destination(){
				return mDestination;
			}

			std::string clientId(){
				return mClientId;
			}

			void setDestination(const std::string& value){
				mDestination = value;
			}

			void subscribe(const std::string& clientid){
				mClientId = clientid;

				rtmp::Client::instance().registerConsumer(this);
				
				flex::messaging::messages::CommandMessage msg;
				msg.setClientId(mClientId);
				msg.setDestination(mDestination);
				msg.setOperation(flex::messaging::messages::CommandMessage::SUBSCRIBE);
				rtmp::Client::instance().send(&rtmp::messages::Amf3Command((amf::Object*)&msg), std::bind(&Consumer::onSubscribe, this, std::placeholders::_1));
			}

			void addListener(const MessageListener& listener){
				mListeners.push_back(listener);
			}

			void onMessage(amf::Variant* message){
				for(auto itr = mListeners.begin(); itr != mListeners.end(); ++itr)
					(*itr)(message);
			}

		private:
			void onSubscribe(amf::Variant* result){
				std::cout << "Consumer " << mClientId << " acknowledged" << std::endl;
			}

		private:
			std::string mClientId;
			std::string mDestination;
			std::vector<MessageListener> mListeners;
		};
	};
};
