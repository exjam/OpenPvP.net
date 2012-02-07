#pragma once

#include "amf/variant.h"
#include "playerparticipant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class GameDTO : public amf::Object {
				public:
					GameDTO(){
						setName("com.riotgames.platform.game.GameDTO");

						set("gameMode", (amf::Null*)nullptr);
						set("bannedChampions", new amf::Array());
						set("spectatorsAllowed", (amf::Null*)nullptr);
						set("ownerSummary", (amf::Null*)nullptr);
						set("queueTypeName", (amf::Null*)nullptr);
						set("optimisticLock", (amf::Null*)nullptr);
						set("id", (amf::Null*)nullptr);
						set("teamTwo", new amf::Array());
						set("gameType", (amf::Null*)nullptr);
						set("banOrder", new amf::Array());
						set("expiryTime", (amf::Null*)nullptr);
						set("teamOne", new amf::Array());
						set("gameZonePort", (amf::Null*)nullptr);
						set("gameZoneHost", (amf::Null*)nullptr);
						set("gameStateString", (amf::Null*)nullptr);
						set("name", (amf::Null*)nullptr);
						set("terminatedCondition", (amf::Null*)nullptr);
						set("gameTypeConfigId", (amf::Null*)nullptr);
						set("creationTime", (amf::Null*)nullptr);
						set("playerChampionSelections", new amf::Array());
						set("mapId", (amf::Null*)nullptr);
						set("gameState", (amf::Null*)nullptr);
						set("pickTurn", (amf::Null*)nullptr);
						set("queuePosition", (amf::Null*)nullptr);
						set("observers", new amf::Array());
						set("accountSpellsMap", new amf::Array());
						set("spectatorDelay", (amf::Null*)nullptr);
						set("maxNumPlayers", (amf::Null*)nullptr);
						set("passwordSet", (amf::Null*)nullptr);
					}

					std::string getGameMode() const {
						return get("gameMode");
					}

					const amf::Reference<amf::Array> getBannedChampions() const {
						return get("bannedChampions");
					}

					bool getSpectatorsAllowed() const {
						return get("spectatorsAllowed");
					}

					const amf::Reference<PlayerParticipant> getOwnerSummary() const {
						return get("ownerSummary").toObject();
					}

					std::string getQueueTypeName() const {
						return get("queueTypeName");
					}

					double getOptimisticLock() const {
						return get("optimisticLock");
					}

					double getId() const {
						return get("id");
					}

					const amf::Reference<amf::Array> getTeamTwo() const {
						return get("teamTwo");
					}

					std::string getGameType() const {
						return get("gameType");
					}

					const amf::Reference<amf::Array> getBanOrder() const {
						return get("banOrder");
					}

					double getExpiryTime() const {
						return get("expiryTime");
					}

					const amf::Reference<amf::Array> getTeamOne() const {
						return get("teamOne");
					}

					std::string getGameZonePort() const {
						return get("gameZonePort");
					}

					std::string getGameZoneHost() const {
						return get("gameZoneHost");
					}

					std::string getGameStateString() const {
						return get("gameStateString");
					}

					std::string getName() const {
						return get("name");
					}

					std::string getTerminatedCondition() const {
						return get("terminatedCondition");
					}

					int getGameTypeConfigId() const {
						return get("gameTypeConfigId");
					}

					amf::Date* getCreationTime() const {
						return get("creationTime").toDate();
					}

					const amf::Reference<amf::Array> getPlayerChampionSelections() const {
						return get("playerChampionSelections");
					}

					int getMapId() const {
						return get("mapId");
					}

					std::string getGameState() const {
						return get("gameState");
					}

					int getPickTurn() const {
						return get("pickTurn");
					}

					int getQueuePosition() const {
						return get("queuePosition");
					}

					const amf::Reference<amf::Array> getObservers() const {
						return get("observers");
					}

					const amf::Reference<amf::Array> getAccountSpellsMap() const {
						return get("accountSpellsMap");
					}

					int getSpectatorDelay() const {
						return get("spectatorDelay");
					}

					int getMaxNumPlayers() const {
						return get("maxNumPlayers");
					}

					bool getPasswordSet() const {
						return get("passwordSet");
					}

					void setGameMode(const std::string& value){
						get("gameMode") = value;
					}

					void setBannedChampions(amf::Array* value){
						get("bannedChampions") = value;
					}

					void setSpectatorsAllowed(bool value){
						get("spectatorsAllowed") = value;
					}

					void setOwnerSummary(PlayerParticipant* value){
						get("ownerSummary") = value;
					}

					void setQueueTypeName(const std::string& value){
						get("queueTypeName") = value;
					}

					void setOptimisticLock(double value){
						get("optimisticLock") = value;
					}

					void setId(double value){
						get("id") = value;
					}

					void setTeamTwo(amf::Array* value){
						get("teamTwo") = value;
					}

					void setGameType(const std::string& value){
						get("gameType") = value;
					}

					void setBanOrder(amf::Array* value){
						get("banOrder") = value;
					}

					void setExpiryTime(double value){
						get("expiryTime") = value;
					}

					void setTeamOne(amf::Array* value){
						get("teamOne") = value;
					}

					void setGameZonePort(const std::string& value){
						get("gameZonePort") = value;
					}

					void setGameZoneHost(const std::string& value){
						get("gameZoneHost") = value;
					}

					void setGameStateString(const std::string& value){
						get("gameStateString") = value;
					}

					void setName(const std::string& value){
						get("name") = value;
					}

					void setTerminatedCondition(const std::string& value){
						get("terminatedCondition") = value;
					}

					void setGameTypeConfigId(int value){
						get("gameTypeConfigId") = value;
					}

					void setCreationTime(amf::Date* value){
						get("creationTime") = value;
					}

					void setPlayerChampionSelections(amf::Array* value){
						get("playerChampionSelections") = value;
					}

					void setMapId(int value){
						get("mapId") = value;
					}

					void setGameState(const std::string& value){
						get("gameState") = value;
					}

					void setPickTurn(int value){
						get("pickTurn") = value;
					}

					void setQueuePosition(int value){
						get("queuePosition") = value;
					}

					void setObservers(amf::Array* value){
						get("observers") = value;
					}

					void setAccountSpellsMap(amf::Array* value){
						get("accountSpellsMap") = value;
					}

					void setSpectatorDelay(int value){
						get("spectatorDelay") = value;
					}

					void setMaxNumPlayers(int value){
						get("maxNumPlayers") = value;
					}

					void setPasswordSet(bool value){
						get("passwordSet") = value;
					}
				};
			};
		};
	};
};
