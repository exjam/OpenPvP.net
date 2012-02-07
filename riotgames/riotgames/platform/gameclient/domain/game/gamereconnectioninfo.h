#pragma once

#include "amf/variant.h"
#include "../gamedto.h"
#include "../playercredentialsdto.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace game {
					class GameReconnectionInfo : public amf::Object {
					public:
						GameReconnectionInfo(){
							setName("com.riotgames.platform.game.GameReconnectionInfo");

							set("game", (amf::Null*)nullptr);
							set("reconnectDelay", (amf::Null*)nullptr);
							set("playerCredentials", (amf::Null*)nullptr);
						}

						const amf::Reference<GameDTO> getGame() const {
							return get("game").toObject();
						}

						int getReconnectDelay() const {
							return get("reconnectDelay");
						}

						const amf::Reference<PlayerCredentialsDTO> getPlayerCredentials() const {
							return get("playerCredentials").toObject();
						}

						void setGame(GameDTO* value){
							get("game") = value;
						}

						void setReconnectDelay(int value){
							get("reconnectDelay") = value;
						}

						void setPlayerCredentials(PlayerCredentialsDTO* value){
							get("playerCredentials") = value;
						}
					};
				};
			};
		};
	};
};
