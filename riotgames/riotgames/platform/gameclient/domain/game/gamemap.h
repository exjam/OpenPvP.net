#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace game {
					class GameMap : public amf::Object {
					public:
						GameMap(){
							setName("com.riotgames.platform.gameclient.domain.game.GameMap");

							set("mapId", (amf::Null*)nullptr);
							set("displayName", (amf::Null*)nullptr);
							set("name", (amf::Null*)nullptr);
							set("description", (amf::Null*)nullptr);
							set("totalPlayers", (amf::Null*)nullptr);
							set("minCustomPlayers", (amf::Null*)nullptr);
						}

						int getMapId() const {
							return get("mapId");
						}

						std::string getDisplayName() const {
							return get("displayName");
						}

						std::string getName() const {
							return get("name");
						}

						std::string getDescription() const {
							return get("description");
						}

						int getTotalPlayers() const {
							return get("totalPlayers");
						}

						int getMinCustomPlayers() const {
							return get("minCustomPlayers");
						}

						void setMapId(int value){
							get("mapId") = value;
						}

						void setDisplayName(const std::string& value){
							get("displayName") = value;
						}

						void setName(const std::string& value){
							get("name") = value;
						}

						void setDescription(const std::string& value){
							get("description") = value;
						}

						void setTotalPlayers(int value){
							get("totalPlayers") = value;
						}

						void setMinCustomPlayers(int value){
							get("minCustomPlayers") = value;
						}
					};
				};
			};
		};
	};
};
