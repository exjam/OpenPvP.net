#pragma once

#include "base64.h"
#include "messages.h"
#include "amf/variant.h"
#include "rtmp/client.h"
#include "rtmp/messages.h"

namespace flex {
	namespace messaging {
		using messages::CommandMessage;

		class ChannelSet {
		public:
			void login(const std::string& username, const std::string& password, const rtmp::CommandCallback& cb){
				CommandMessage* msg = new CommandMessage();
				msg->setBody(Base64::encode(username + ":" + password));
				msg->setOperation(CommandMessage::LOGIN);
				msg->setDestination("auth");

				rtmp::Client::instance().send(&rtmp::messages::Amf3Command(amf::Variant(msg)), cb);
			}

			void logout(){
				CommandMessage* msg = new CommandMessage();
				msg->setOperation(CommandMessage::LOGOUT);
				msg->setDestination("auth");

				rtmp::Client::instance().send(&rtmp::messages::Amf3Command(amf::Variant(msg)), std::bind(&ChannelSet::onLogout, this, std::placeholders::_1));
			}

		private:
			void onLogout(const amf::Variant& result){
			}

		private:
		};
	};
};
