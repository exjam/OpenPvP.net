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

							set("fullId", new amf::Null());
						}

						std::string getFullId(){
							return get("fullId")->toString();
						}

						void setFullId(const std::string& value){
							set("fullId", amf::object_creator_t(value).mValue);
						}
					};
				};
			};
		};
	};
};
