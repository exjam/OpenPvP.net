#pragma once

#include "amf/variant.h"
#include "teamid.h"
#include "../abstractdomainobject.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace rankedTeams {
					class TeamInfo : public AbstractDomainObject {
					public:
						TeamInfo(){
							setName("com.riotgames.team.TeamInfo");

							set("name", (amf::Null*)nullptr);
							set("tag", (amf::Null*)nullptr);
							set("teamId", (amf::Null*)nullptr);
							set("memberStatusString", (amf::Null*)nullptr);
						}

						std::string getName() const {
							return get("name");
						}

						std::string getTag() const {
							return get("tag");
						}

						const amf::Reference<TeamId> getTeamId() const {
							return get("teamId").toObject();
						}

						std::string getMemberStatusString() const {
							return get("memberStatusString");
						}

						void setName(const std::string& value){
							get("name") = value;
						}

						void setTag(const std::string& value){
							get("tag") = value;
						}

						void setTeamId(TeamId* value){
							get("teamId") = value;
						}

						void setMemberStatusString(const std::string& value){
							get("memberStatusString") = value;
						}
					};
				};
			};
		};
	};
};
