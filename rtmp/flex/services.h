#pragma once

#include "messages.h"
#include "amf/variant.h"
#include "rtmp/client.h"
#include "rtmp/messages.h"

namespace flex {
	namespace messaging {
		namespace services {
			class Service {
			public:
				Service(const std::string& name)
					: mName(name)
				{
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback){
						amf::Array args;
						invokeWithArgs(operation, callback, &args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, amf::Variant* arg1){
						amf::Array args;
						args << arg1;

						invokeWithArgs(operation, callback, &args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, amf::Variant* arg1, amf::Variant* arg2){
						amf::Array args;
						args << arg1 << arg2;

						invokeWithArgs(operation, callback, &args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, amf::Variant* arg1, amf::Variant* arg2, amf::Variant* arg3){
						amf::Array args;
						args << arg1 << arg2 << arg3;

						invokeWithArgs(operation, callback, &args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, amf::Variant* arg1, amf::Variant* arg2, amf::Variant* arg3, amf::Variant* arg4){
						amf::Array args;
						args << arg1 << arg2 << arg3 << arg4;

						invokeWithArgs(operation, callback, &args);
				}

			private:
				void invokeWithArgs(const std::string& operation, const rtmp::CommandCallback& result, amf::Array* args){
					flex::messaging::messages::RemotingMessage msg;
					msg.setDestination(mName);
					msg.setOperation(operation);
					msg.setBody(args);

					rtmp::Client::instance().send(&rtmp::messages::Amf3Command((amf::Object*)&msg), result);
				}

			private:
				std::string mName;
			};
		};
	};
};
