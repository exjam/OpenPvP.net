#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace rankedTeams {
					class TeamId : public amf::Object {
					public:
						TeamId(){
							setName("com.riotgames.team.TeamId");

							set("fullId", (amf::Null*)nullptr);
						}

						std::string getFullId() const {
							return get("fullId");
						}

						void setFullId(const std::string& value){
							get("fullId") = value;
						}
					};
				};
			};
		};
	};
};
