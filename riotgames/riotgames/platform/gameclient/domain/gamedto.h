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

						set("gameMode", new amf::Null());
						set("bannedChampions", new amf::Array());
						set("spectatorsAllowed", new amf::Null());
						set("ownerSummary", new amf::Null());
						set("queueTypeName", new amf::Null());
						set("optimisticLock", new amf::Null());
						set("id", new amf::Null());
						set("teamTwo", new amf::Array());
						set("gameType", new amf::Null());
						set("banOrder", new amf::Array());
						set("expiryTime", new amf::Null());
						set("teamOne", new amf::Array());
						set("gameZonePort", new amf::Null());
						set("gameZoneHost", new amf::Null());
						set("gameStateString", new amf::Null());
						set("name", new amf::Null());
						set("terminatedCondition", new amf::Null());
						set("gameTypeConfigId", new amf::Null());
						set("creationTime", new amf::Null());
						set("playerChampionSelections", new amf::Array());
						set("mapId", new amf::Null());
						set("gameState", new amf::Null());
						set("pickTurn", new amf::Null());
						set("queuePosition", new amf::Null());
						set("observers", new amf::Array());
						set("accountSpellsMap", new amf::Array());
						set("spectatorDelay", new amf::Null());
						set("maxNumPlayers", new amf::Null());
						set("passwordSet", new amf::Null());
					}

					std::string getGameMode(){
						return get("gameMode")->toString();
					}

					amf::Array* getBannedChampions(){
						return get("bannedChampions")->toArray();
					}

					bool getSpectatorsAllowed(){
						return get("spectatorsAllowed")->toBool();
					}

					PlayerParticipant* getOwnerSummary(){
						return (PlayerParticipant*)get("ownerSummary")->toObject();
					}

					std::string getQueueTypeName(){
						return get("queueTypeName")->toString();
					}

					double getOptimisticLock(){
						return get("optimisticLock")->toDouble();
					}

					double getId(){
						return get("id")->toDouble();
					}

					amf::Array* getTeamTwo(){
						return get("teamTwo")->toArray();
					}

					std::string getGameType(){
						return get("gameType")->toString();
					}

					amf::Array* getBanOrder(){
						return get("banOrder")->toArray();
					}

					double getExpiryTime(){
						return get("expiryTime")->toDouble();
					}

					amf::Array* getTeamOne(){
						return get("teamOne")->toArray();
					}

					std::string getGameZonePort(){
						return get("gameZonePort")->toString();
					}

					std::string getGameZoneHost(){
						return get("gameZoneHost")->toString();
					}

					std::string getGameStateString(){
						return get("gameStateString")->toString();
					}

					std::string getName(){
						return get("name")->toString();
					}

					std::string getTerminatedCondition(){
						return get("terminatedCondition")->toString();
					}

					int getGameTypeConfigId(){
						return get("gameTypeConfigId")->toInt();
					}

					amf::Date* getCreationTime(){
						return get("creationTime")->toDate();
					}

					amf::Array* getPlayerChampionSelections(){
						return get("playerChampionSelections")->toArray();
					}

					int getMapId(){
						return get("mapId")->toInt();
					}

					std::string getGameState(){
						return get("gameState")->toString();
					}

					int getPickTurn(){
						return get("pickTurn")->toInt();
					}

					int getQueuePosition(){
						return get("queuePosition")->toInt();
					}

					amf::Array* getObservers(){
						return get("observers")->toArray();
					}

					amf::Array* getAccountSpellsMap(){
						return get("accountSpellsMap")->toArray();
					}

					int getSpectatorDelay(){
						return get("spectatorDelay")->toInt();
					}

					int getMaxNumPlayers(){
						return get("maxNumPlayers")->toInt();
					}

					bool getPasswordSet(){
						return get("passwordSet")->toBool();
					}

					void setGameMode(const std::string& value){
						set("gameMode", amf::object_creator_t(value).mValue);
					}

					void setBannedChampions(amf::Array* value){
						set("bannedChampions", (Variant*)value);
					}

					void setSpectatorsAllowed(bool value){
						set("spectatorsAllowed", amf::object_creator_t(value).mValue);
					}

					void setOwnerSummary(PlayerParticipant* value){
						set("ownerSummary", (Variant*)value);
					}

					void setQueueTypeName(const std::string& value){
						set("queueTypeName", amf::object_creator_t(value).mValue);
					}

					void setOptimisticLock(double value){
						set("optimisticLock", amf::object_creator_t(value).mValue);
					}

					void setId(double value){
						set("id", amf::object_creator_t(value).mValue);
					}

					void setTeamTwo(amf::Array* value){
						set("teamTwo", (Variant*)value);
					}

					void setGameType(const std::string& value){
						set("gameType", amf::object_creator_t(value).mValue);
					}

					void setBanOrder(amf::Array* value){
						set("banOrder", (Variant*)value);
					}

					void setExpiryTime(double value){
						set("expiryTime", amf::object_creator_t(value).mValue);
					}

					void setTeamOne(amf::Array* value){
						set("teamOne", (Variant*)value);
					}

					void setGameZonePort(const std::string& value){
						set("gameZonePort", amf::object_creator_t(value).mValue);
					}

					void setGameZoneHost(const std::string& value){
						set("gameZoneHost", amf::object_creator_t(value).mValue);
					}

					void setGameStateString(const std::string& value){
						set("gameStateString", amf::object_creator_t(value).mValue);
					}

					void setName(const std::string& value){
						set("name", amf::object_creator_t(value).mValue);
					}

					void setTerminatedCondition(const std::string& value){
						set("terminatedCondition", amf::object_creator_t(value).mValue);
					}

					void setGameTypeConfigId(int value){
						set("gameTypeConfigId", amf::object_creator_t(value).mValue);
					}

					void setCreationTime(amf::Date* value){
						set("creationTime", (Variant*)value);
					}

					void setPlayerChampionSelections(amf::Array* value){
						set("playerChampionSelections", (Variant*)value);
					}

					void setMapId(int value){
						set("mapId", amf::object_creator_t(value).mValue);
					}

					void setGameState(const std::string& value){
						set("gameState", amf::object_creator_t(value).mValue);
					}

					void setPickTurn(int value){
						set("pickTurn", amf::object_creator_t(value).mValue);
					}

					void setQueuePosition(int value){
						set("queuePosition", amf::object_creator_t(value).mValue);
					}

					void setObservers(amf::Array* value){
						set("observers", (Variant*)value);
					}

					void setAccountSpellsMap(amf::Array* value){
						set("accountSpellsMap", (Variant*)value);
					}

					void setSpectatorDelay(int value){
						set("spectatorDelay", amf::object_creator_t(value).mValue);
					}

					void setMaxNumPlayers(int value){
						set("maxNumPlayers", amf::object_creator_t(value).mValue);
					}

					void setPasswordSet(bool value){
						set("passwordSet", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
