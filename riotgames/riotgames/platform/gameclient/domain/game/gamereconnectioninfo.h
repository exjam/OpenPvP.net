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

							set("game", new amf::Null());
							set("reconnectDelay", new amf::Null());
							set("playerCredentials", new amf::Null());
						}

						GameDTO* getGame(){
							return (GameDTO*)get("game")->toObject();
						}

						int getReconnectDelay(){
							return get("reconnectDelay")->toInt();
						}

						PlayerCredentialsDTO* getPlayerCredentials(){
							return (PlayerCredentialsDTO*)get("playerCredentials")->toObject();
						}

						void setGame(GameDTO* value){
							set("game", (Variant*)value);
						}

						void setReconnectDelay(int value){
							set("reconnectDelay", amf::object_creator_t(value).mValue);
						}

						void setPlayerCredentials(PlayerCredentialsDTO* value){
							set("playerCredentials", (Variant*)value);
						}
					};
				};
			};
		};
	};
};
