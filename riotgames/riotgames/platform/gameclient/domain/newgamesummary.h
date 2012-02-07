#pragma once

#include "amf/variant.h"
#include "gamezone.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class NewGameSummary : public amf::Object {
				public:
					NewGameSummary(){
						setName("com.riotgames.platform.gameclient.domain.NewGameSummary");

						set("gameZone", (amf::Null*)nullptr);
						set("gameId", (amf::Null*)nullptr);
					}

					const amf::Reference<GameZone> getGameZone() const {
						return get("gameZone").toObject();
					}

					std::string getGameId() const {
						return get("gameId");
					}

					void setGameZone(GameZone* value){
						get("gameZone") = value;
					}

					void setGameId(const std::string& value){
						get("gameId") = value;
					}
				};
			};
		};
	};
};
