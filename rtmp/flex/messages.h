#pragma once

#include "amf/variant.h"

namespace flex {
	namespace messaging {
		namespace messages {
			class AbstractMessage : public amf::Object {
			public:
				AbstractMessage(){
					setName("flex.messaging.messages.AbstractMessage");

					set("body", new amf::Array());
					set("clientId", new amf::Null());
					set("destination", "");
					set("messageId", "1337");
					set("timeToLive", 0);
					set("timestamp", 0);

					amf::Object* headers = new amf::Object();
					(*headers)
						<< amf::var("DSEndpoint", "my-rtmps")
						<< amf::var("DSId", "1337");
						
					set("headers", headers);
					defineObject();
				}

				const amf::Variant& body(){
					return get("body");
				}

				amf::Object* clientId(){
					return get("clientId");
				}

				std::string destination(){
					return get("destination");
				}

				amf::Object* headers(){
					return get("headers");
				}

				std::string messageId(){
					return get("messageId");
				}

				int timeToLive(){
					return get("timeToLive");
				}

				int timestamp(){
					return get("timestamp");
				}

				void setBody(const amf::Variant& value){
					set("body", value);
				}

				void setClientId(const std::string& value){
					get("clientId") = value;
				}

				void setDestination(const std::string& value){
					get("destination") = value;
				}

				void setHeaders(amf::Object* value){
					set("headers", value);
				}

				void setMessageId(const std::string& value){
					get("messageId") = value;
				}
				
				void setTimeToLive(int value){
					get("timeToLive") = value;
				}

				void setTimestamp(int value){
					get("timestamp") = value;
				}
			};

			class RemotingMessage : public AbstractMessage {
			public:
				RemotingMessage(){
					setName("flex.messaging.messages.RemotingMessage");

					set("operation", "");
					set("source", "");
					headers()->set("DSRequestTimeout", 60);

					defineObject();
				}

				std::string operation(){
					return get("operation");
				}

				std::string source(){
					return get("source");
				}

				void setOperation(const std::string& value){
					get("operation") = value;
				}

				void setSource(const std::string& value){
					get("source") = value;
				}
			};

			class CommandMessage : public AbstractMessage {
			public:
				typedef enum {
					SUBSCRIBE,
					UNSUBSCRIBE,
					POLL,
					CLIENT_SYNC = 4,
					CLIENT_PING,
					CLUSTER_REQUEST = 7,
					LOGIN,
					LOGOUT,
					SESSION_INVALIDATE,
					CONNECT = 20,
					DISCONNECT,
					UNKNOWN = 10000,
				} Operation;

				CommandMessage(){
					setName("flex.messaging.messages.CommandMessage");

					set("operation", new amf::Integer());
					set("correlationId", new amf::String());
					defineObject();
				}

				int operation(){
					return get("operation");
				}

				std::string correlationId(){
					return get("correlationId");
				}

				void setOperation(int value){
					get("operation") = value;
				}

				void setCorrelationId(const std::string& value){
					get("correlationId") = value;
				}
			};
		};
	};
};
