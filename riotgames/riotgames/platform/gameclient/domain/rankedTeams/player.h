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

							set("playerId", new amf::Null());
							set("createdTeams", new amf::Array());
							set("playerTeams", new amf::Array());
						}

						double getPlayerId(){
							return get("playerId")->toDouble();
						}

						amf::Array* getCreatedTeams(){
							return get("createdTeams")->toArray();
						}

						amf::Array* getPlayerTeams(){
							return get("playerTeams")->toArray();
						}

						void setPlayerId(double value){
							set("playerId", amf::object_creator_t(value).mValue);
						}

						void setCreatedTeams(amf::Array* value){
							set("createdTeams", (Variant*)value);
						}

						void setPlayerTeams(amf::Array* value){
							set("playerTeams", (Variant*)value);
						}
					};
				};
			};
		};
	};
};
