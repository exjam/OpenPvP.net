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
			void login(const std::string& username, const std::string& password){
				CommandMessage msg;
				msg.setBody(amf::Variant::fromValue(Base64::encode(username + ":" + password)));
				msg.setOperation(CommandMessage::LOGIN);
				msg.setDestination("auth");

				rtmp::Client::instance().send(&rtmp::messages::Amf3Command((amf::Object*)&msg), std::bind(&ChannelSet::onLogin, this, std::placeholders::_1));
			}

			void logout(){
				CommandMessage msg;
				msg.setOperation(CommandMessage::LOGOUT);
				msg.setDestination("auth");

				rtmp::Client::instance().send(&rtmp::messages::Amf3Command((amf::Object*)&msg), std::bind(&ChannelSet::onLogout, this, std::placeholders::_1));
			}

		private:
			void onLogin(amf::Variant* result){
			}

			void onLogout(amf::Variant* result){
			}

		private:
		};
	};
};
