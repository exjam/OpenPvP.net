#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class GameZone : public amf::Object {
				public:
					GameZone(){
						setName("com.riotgames.platform.gameclient.domain.GameZone");

						set("gameZonePort", (amf::Null*)nullptr);
						set("gameZoneHost", (amf::Null*)nullptr);
					}

					int getGameZonePort() const {
						return get("gameZonePort");
					}

					std::string getGameZoneHost() const {
						return get("gameZoneHost");
					}

					void setGameZonePort(int value){
						get("gameZonePort") = value;
					}

					void setGameZoneHost(const std::string& value){
						get("gameZoneHost") = value;
					}
				};
			};
		};
	};
};
