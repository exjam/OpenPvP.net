#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace rankedTeams {
					class Player : public amf::Object {
					public:
						Player(){
							setName("com.riotgames.team.Player");

							set("playerId", (amf::Null*)nullptr);
							set("createdTeams", new amf::Array());
							set("playerTeams", new amf::Array());
						}

						double getPlayerId() const {
							return get("playerId");
						}

						const amf::Reference<amf::Array> getCreatedTeams() const {
							return get("createdTeams");
						}

						const amf::Reference<amf::Array> getPlayerTeams() const {
							return get("playerTeams");
						}

						void setPlayerId(double value){
							get("playerId") = value;
						}

						void setCreatedTeams(amf::Array* value){
							get("createdTeams") = value;
						}

						void setPlayerTeams(amf::Array* value){
							get("playerTeams") = value;
						}
					};
				};
			};
		};
	};
};
