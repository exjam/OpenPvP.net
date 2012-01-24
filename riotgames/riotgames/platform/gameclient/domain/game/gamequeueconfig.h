#pragma once

#include "amf/variant.h"
#include "../abstractdomainobject.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace game {
					class GameQueueConfig : public AbstractDomainObject {
					public:
						GameQueueConfig(){
							setName("com.riotgames.platform.matchmaking.GameQueueConfig");

							set("gameMode", new amf::Null());
							set("supportedMapIds", new amf::Array());
							set("maximumParticipantListSize", new amf::Null());
							set("type", new amf::Null());
							set("minimumParticipantListSize", new amf::Null());
							set("gameTypeConfigId", new amf::Null());
							set("numPlayersPerTeam", new amf::Null());
							set("id", new amf::Null());
							set("maxLevel", new amf::Null());
							set("minLevel", new amf::Null());
							set("teamOnly", new amf::Null());
							set("ranked", new amf::Null());
						}

						std::string getGameMode(){
							return get("gameMode")->toString();
						}

						amf::Array* getSupportedMapIds(){
							return get("supportedMapIds")->toArray();
						}

						int getMaximumParticipantListSize(){
							return get("maximumParticipantListSize")->toInt();
						}

						std::string getType(){
							return get("type")->toString();
						}

						int getMinimumParticipantListSize(){
							return get("minimumParticipantListSize")->toInt();
						}

						int getGameTypeConfigId(){
							return get("gameTypeConfigId")->toInt();
						}

						double getNumPlayersPerTeam(){
							return get("numPlayersPerTeam")->toDouble();
						}

						double getId(){
							return get("id")->toDouble();
						}

						int getMaxLevel(){
							return get("maxLevel")->toInt();
						}

						int getMinLevel(){
							return get("minLevel")->toInt();
						}

						bool getTeamOnly(){
							return get("teamOnly")->toBool();
						}

						bool getRanked(){
							return get("ranked")->toBool();
						}

						void setGameMode(const std::string& value){
							set("gameMode", amf::object_creator_t(value).mValue);
						}

						void setSupportedMapIds(amf::Array* value){
							set("supportedMapIds", (Variant*)value);
						}

						void setMaximumParticipantListSize(int value){
							set("maximumParticipantListSize", amf::object_creator_t(value).mValue);
						}

						void setType(const std::string& value){
							set("type", amf::object_creator_t(value).mValue);
						}

						void setMinimumParticipantListSize(int value){
							set("minimumParticipantListSize", amf::object_creator_t(value).mValue);
						}

						void setGameTypeConfigId(int value){
							set("gameTypeConfigId", amf::object_creator_t(value).mValue);
						}

						void setNumPlayersPerTeam(double value){
							set("numPlayersPerTeam", amf::object_creator_t(value).mValue);
						}

						void setId(double value){
							set("id", amf::object_creator_t(value).mValue);
						}

						void setMaxLevel(int value){
							set("maxLevel", amf::object_creator_t(value).mValue);
						}

						void setMinLevel(int value){
							set("minLevel", amf::object_creator_t(value).mValue);
						}

						void setTeamOnly(bool value){
							set("teamOnly", amf::object_creator_t(value).mValue);
						}

						void setRanked(bool value){
							set("ranked", amf::object_creator_t(value).mValue);
						}
					};
				};
			};
		};
	};
};
