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

						set("serverPort", (amf::Null*)nullptr);
						set("handshakeToken", (amf::Null*)nullptr);
						set("observerEncryptionKey", (amf::Null*)nullptr);
						set("observer", (amf::Null*)nullptr);
						set("serverIp", (amf::Null*)nullptr);
						set("gameId", (amf::Null*)nullptr);
						set("playerId", (amf::Null*)nullptr);
						set("observerServerPort", (amf::Null*)nullptr);
						set("encryptionKey", (amf::Null*)nullptr);
						set("observerServerIp", (amf::Null*)nullptr);
					}

					int getServerPort() const {
						return get("serverPort");
					}

					std::string getHandshakeToken() const {
						return get("handshakeToken");
					}

					std::string getObserverEncryptionKey() const {
						return get("observerEncryptionKey");
					}

					bool getObserver() const {
						return get("observer");
					}

					std::string getServerIp() const {
						return get("serverIp");
					}

					double getGameId() const {
						return get("gameId");
					}

					double getPlayerId() const {
						return get("playerId");
					}

					int getObserverServerPort() const {
						return get("observerServerPort");
					}

					std::string getEncryptionKey() const {
						return get("encryptionKey");
					}

					std::string getObserverServerIp() const {
						return get("observerServerIp");
					}

					void setServerPort(int value){
						get("serverPort") = value;
					}

					void setHandshakeToken(const std::string& value){
						get("handshakeToken") = value;
					}

					void setObserverEncryptionKey(const std::string& value){
						get("observerEncryptionKey") = value;
					}

					void setObserver(bool value){
						get("observer") = value;
					}

					void setServerIp(const std::string& value){
						get("serverIp") = value;
					}

					void setGameId(double value){
						get("gameId") = value;
					}

					void setPlayerId(double value){
						get("playerId") = value;
					}

					void setObserverServerPort(int value){
						get("observerServerPort") = value;
					}

					void setEncryptionKey(const std::string& value){
						get("encryptionKey") = value;
					}

					void setObserverServerIp(const std::string& value){
						get("observerServerIp") = value;
					}
				};
			};
		};
	};
};
