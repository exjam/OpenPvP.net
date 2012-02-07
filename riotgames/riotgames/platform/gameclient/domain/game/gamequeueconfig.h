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

							set("gameMode", (amf::Null*)nullptr);
							set("supportedMapIds", new amf::Array());
							set("maximumParticipantListSize", (amf::Null*)nullptr);
							set("type", (amf::Null*)nullptr);
							set("minimumParticipantListSize", (amf::Null*)nullptr);
							set("gameTypeConfigId", (amf::Null*)nullptr);
							set("numPlayersPerTeam", (amf::Null*)nullptr);
							set("id", (amf::Null*)nullptr);
							set("maxLevel", (amf::Null*)nullptr);
							set("minLevel", (amf::Null*)nullptr);
							set("teamOnly", (amf::Null*)nullptr);
							set("ranked", (amf::Null*)nullptr);
						}

						std::string getGameMode() const {
							return get("gameMode");
						}

						const amf::Reference<amf::Array> getSupportedMapIds() const {
							return get("supportedMapIds");
						}

						int getMaximumParticipantListSize() const {
							return get("maximumParticipantListSize");
						}

						std::string getType() const {
							return get("type");
						}

						int getMinimumParticipantListSize() const {
							return get("minimumParticipantListSize");
						}

						int getGameTypeConfigId() const {
							return get("gameTypeConfigId");
						}

						double getNumPlayersPerTeam() const {
							return get("numPlayersPerTeam");
						}

						double getId() const {
							return get("id");
						}

						int getMaxLevel() const {
							return get("maxLevel");
						}

						int getMinLevel() const {
							return get("minLevel");
						}

						bool getTeamOnly() const {
							return get("teamOnly");
						}

						bool getRanked() const {
							return get("ranked");
						}

						void setGameMode(const std::string& value){
							get("gameMode") = value;
						}

						void setSupportedMapIds(amf::Array* value){
							get("supportedMapIds") = value;
						}

						void setMaximumParticipantListSize(int value){
							get("maximumParticipantListSize") = value;
						}

						void setType(const std::string& value){
							get("type") = value;
						}

						void setMinimumParticipantListSize(int value){
							get("minimumParticipantListSize") = value;
						}

						void setGameTypeConfigId(int value){
							get("gameTypeConfigId") = value;
						}

						void setNumPlayersPerTeam(double value){
							get("numPlayersPerTeam") = value;
						}

						void setId(double value){
							get("id") = value;
						}

						void setMaxLevel(int value){
							get("maxLevel") = value;
						}

						void setMinLevel(int value){
							get("minLevel") = value;
						}

						void setTeamOnly(bool value){
							get("teamOnly") = value;
						}

						void setRanked(bool value){
							get("ranked") = value;
						}
					};
				};
			};
		};
	};
};
