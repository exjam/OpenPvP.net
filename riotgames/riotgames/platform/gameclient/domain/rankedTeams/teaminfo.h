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

							set("name", new amf::Null());
							set("tag", new amf::Null());
							set("teamId", new amf::Null());
							set("memberStatusString", new amf::Null());
						}

						std::string getName(){
							return get("name")->toString();
						}

						std::string getTag(){
							return get("tag")->toString();
						}

						TeamId* getTeamId(){
							return (TeamId*)get("teamId")->toObject();
						}

						std::string getMemberStatusString(){
							return get("memberStatusString")->toString();
						}

						void setName(const std::string& value){
							set("name", amf::object_creator_t(value).mValue);
						}

						void setTag(const std::string& value){
							set("tag", amf::object_creator_t(value).mValue);
						}

						void setTeamId(TeamId* value){
							set("teamId", (Variant*)value);
						}

						void setMemberStatusString(const std::string& value){
							set("memberStatusString", amf::object_creator_t(value).mValue);
						}
					};
				};
			};
		};
	};
};
