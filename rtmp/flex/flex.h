#pragma once

#include "amf/amf.h"
#include "amf/amf3.h"

namespace flex {
	namespace messaging {
		namespace messages {
			class AbstractMessage : public amf::ObjectWrapper {
			public:
				AbstractMessage()
					: amf::ObjectWrapper(new amf3::Object("flex.messaging.messages.AbstractMessage"))
				{
				}

				AbstractMessage(amf::Object* obj)
					: amf::ObjectWrapper(obj)
				{
				}

				amf::Object* body(){
					return mObject->getProperty("body")->asObject();
				}

				amf::Entity* clientId(){
					return mObject->getProperty("clientId");
				}

				const std::string& destination(){
					return mObject->getProperty("destination")->asString();
				}

				amf::Object* headers(){
					return mObject->getProperty("body")->asObject();
				}

				const std::string& messageId(){
					return mObject->getProperty("messageId")->asString();
				}

				int timeToLive(){
					return mObject->getProperty("timeToLive")->asInt();
				}

				int timestamp(){
					return mObject->getProperty("timestamp")->asInt();
				}

				void setBody(amf::Object* value){
					mObject->set("body", (amf::Entity*)value);
				}

				void setClientId(amf::Entity* value){
					mObject->set("clientId", (amf::Entity*)value);
				}

				void setDestination(const std::string& value){
					mObject->set("destination", value);
				}

				void setHeaders(amf::Object* value){
					mObject->set("headers", (amf::Entity*)value);
				}

				void setMessageId(const std::string& value){
					mObject->set("messageId", value);
				}
				
				void setTimeToLive(int value){
					mObject->set("timeToLive", value);
				}

				void setTimestamp(int value){
					mObject->set("timestamp", value);
				}

			protected:
				void init(){
					setBody(new amf3::Array());
					setClientId(nullptr);
					setDestination("");
					setHeaders(new amf3::Object());
					setMessageId("");
					setTimeToLive(0);
					setTimestamp(0);
				}
			};

			class RemotingMessage : public AbstractMessage {
			public:
				RemotingMessage()
					: AbstractMessage(new amf3::Object("flex.messaging.messages.RemotingMessage"))
				{
				}

				RemotingMessage(amf::Object* obj)
					: AbstractMessage(obj)
				{
				}

				const std::string& operation(){
					return mObject->getProperty("operation")->asString();
				}

				const std::string& source(){
					return mObject->getProperty("source")->asString();
				}

				void setOperation(const std::string& value){
					mObject->set("operation", value);
				}

				void setSource(const std::string& value){
					mObject->set("source", value);
				}
				
			protected:
				void init(){
					AbstractMessage::init();

					setOperation("");
					setSource("");
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

				CommandMessage()
					: AbstractMessage(new amf3::Object("flex.messaging.messages.CommandMessage"))
				{
					init();
				}

				CommandMessage(amf::Object* obj)
					: AbstractMessage(obj)
				{
				}

				int operation(){
					return mObject->getProperty("operation")->asInt();
				}

				const std::string& correlationId(){
					return mObject->getProperty("correlationId")->asString();
				}

				void setOperation(int value){
					mObject->set("operation", value);
				}

				void setSource(const std::string& value){
					mObject->set("correlationId", value);
				}
				
			protected:
				void init(){
					AbstractMessage::init();

					setOperation(0);
					setSource("");
				}
			};
		};
	};
};
