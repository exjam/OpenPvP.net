#pragma once

#include "amf/variant.h"
#include "champion.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class BotParticipant : public amf::Object {
				public:
					BotParticipant(){
						setName("com.riotgames.platform.gameclient.domain.BotParticipant");

						set("champion", (amf::Null*)nullptr);
						set("botSkillLevelName", (amf::Null*)nullptr);
						set("teamId", (amf::Null*)nullptr);
						set("botSkillLevel", (amf::Null*)nullptr);
					}

					const amf::Reference<Champion> getChampion() const {
						return get("champion").toObject();
					}

					std::string getBotSkillLevelName() const {
						return get("botSkillLevelName");
					}

					std::string getTeamId() const {
						return get("teamId");
					}

					double getBotSkillLevel() const {
						return get("botSkillLevel");
					}

					void setChampion(Champion* value){
						get("champion") = value;
					}

					void setBotSkillLevelName(const std::string& value){
						get("botSkillLevelName") = value;
					}

					void setTeamId(const std::string& value){
						get("teamId") = value;
					}

					void setBotSkillLevel(double value){
						get("botSkillLevel") = value;
					}
				};
			};
		};
	};
};
