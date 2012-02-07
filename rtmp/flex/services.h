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
					amf::Array* args = new amf::Array();
					invokeWithArgs(operation, callback, args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, const amf::Variant& arg1){
					amf::Array* args = new amf::Array();
					(*args) << arg1;

					invokeWithArgs(operation, callback, args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, const amf::Variant& arg1, const amf::Variant& arg2){
					amf::Array* args = new amf::Array();
					(*args) << arg1 << arg2;

					invokeWithArgs(operation, callback, args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, const amf::Variant& arg1, const amf::Variant& arg2,
				 const amf::Variant& arg3){
					amf::Array* args = new amf::Array();
					(*args) << arg1 << arg2 << arg3;

					invokeWithArgs(operation, callback, args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, const amf::Variant& arg1, const amf::Variant& arg2,
				 const amf::Variant& arg3, const amf::Variant& arg4){
					amf::Array* args = new amf::Array();
					(*args) << arg1 << arg2 << arg3 << arg4;

					invokeWithArgs(operation, callback, args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, const amf::Variant& arg1, const amf::Variant& arg2,
				 const amf::Variant& arg3, const amf::Variant& arg4, const amf::Variant& arg5){
					amf::Array* args = new amf::Array();
					(*args) << arg1 << arg2 << arg3 << arg4 << arg5;

					invokeWithArgs(operation, callback, args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, const amf::Variant& arg1, const amf::Variant& arg2,
				 const amf::Variant& arg3, const amf::Variant& arg4, const amf::Variant& arg5, const amf::Variant& arg6){
					amf::Array* args = new amf::Array();
					(*args) << arg1 << arg2 << arg3 << arg4 << arg5 << arg6;

					invokeWithArgs(operation, callback, args);
				}

				void invoke(const std::string& operation, const rtmp::CommandCallback& callback, const amf::Variant& arg1, const amf::Variant& arg2,
				 const amf::Variant& arg3, const amf::Variant& arg4, const amf::Variant& arg5, const amf::Variant& arg6, const amf::Variant& arg7){
					amf::Array* args = new amf::Array();
					(*args) << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << arg7;

					invokeWithArgs(operation, callback, args);
				}

			private:
				void invokeWithArgs(const std::string& operation, const rtmp::CommandCallback& result, const amf::Variant& args){
					flex::messaging::messages::RemotingMessage* msg = new flex::messaging::messages::RemotingMessage();
					msg->setDestination(mName);
					msg->setOperation(operation);
					msg->setBody(args);

					rtmp::Client::instance().send(&rtmp::messages::Amf3Command(amf::Variant(msg)), result);
				}

			private:
				std::string mName;
			};
		};
	};
};
