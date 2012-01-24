#pragma once

#include "amf/amf.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {

				class PlayerCredentialsDTO : public amf::Object {
				public:
					PlayerCredentialsDTO(){
						setName("com.riotgames.platform.game.PlayerCredentialsDTO");

						set("serverPort", new amf::Null());
						set("handshakeToken", new amf::Null());
						set("observerEncryptionKey", new amf::Null());
						set("observer", new amf::Null());
						set("serverIp", new amf::Null());
						set("gameId", new amf::Null());
						set("playerId", new amf::Null());
						set("observerServerPort", new amf::Null());
						set("encryptionKey", new amf::Null());
						set("observerServerIp", new amf::Null());
					}

					int getServerPort(){
						return get("serverPort")->toInt();
					}

					std::string getHandshakeToken(){
						return get("handshakeToken")->toString();
					}

					std::string getObserverEncryptionKey(){
						return get("observerEncryptionKey")->toString();
					}

					bool getObserver(){
						return get("observer")->toBool();
					}

					std::string getServerIp(){
						return get("serverIp")->toString();
					}

					double getGameId(){
						return get("gameId")->toDouble();
					}

					double getPlayerId(){
						return get("playerId")->toDouble();
					}

					int getObserverServerPort(){
						return get("observerServerPort")->toInt();
					}

					std::string getEncryptionKey(){
						return get("encryptionKey")->toString();
					}

					std::string getObserverServerIp(){
						return get("observerServerIp")->toString();
					}

					void setServerPort(int value){
						set("serverPort", amf::object_creator_t(value).mValue);
					}

					void setHandshakeToken(const std::string& value){
						set("handshakeToken", amf::object_creator_t(value).mValue);
					}

					void setObserverEncryptionKey(const std::string& value){
						set("observerEncryptionKey", amf::object_creator_t(value).mValue);
					}

					void setObserver(bool value){
						set("observer", amf::object_creator_t(value).mValue);
					}

					void setServerIp(const std::string& value){
						set("serverIp", amf::object_creator_t(value).mValue);
					}

					void setGameId(double value){
						set("gameId", amf::object_creator_t(value).mValue);
					}

					void setPlayerId(double value){
						set("playerId", amf::object_creator_t(value).mValue);
					}

					void setObserverServerPort(int value){
						set("observerServerPort", amf::object_creator_t(value).mValue);
					}

					void setEncryptionKey(const std::string& value){
						set("encryptionKey", amf::object_creator_t(value).mValue);
					}

					void setObserverServerIp(const std::string& value){
						set("observerServerIp", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
