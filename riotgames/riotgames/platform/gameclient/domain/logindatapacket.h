#pragma once

#include "amf/variant.h"

#include "summonercatalog.h"
#include "allsummonerdata.h"
#include "playerstatsummaries.h"

#include "game/gamereconnectioninfo.h"
#include "gameconfig/gametypeconfig.h"
#include "broadcast/broadcastnotification.h"
#include "systemstates/clientsystemstatesnotification.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				using namespace game;
				using namespace broadcast;
				using namespace gameconfig;
				using namespace systemstates;

				class LoginDataPacket : public amf::Object {
				public:
					LoginDataPacket(){
						setName("com.riotgames.platform.clientfacade.domain.LoginDataPacket");

						set("rpBalance", new amf::Null());
						set("minutesUntilMidnight", new amf::Null());
						set("leaverBusterPenaltyTime", new amf::Null());
						set("minorShutdownEnforced", new amf::Null());
						set("clientHeartBeatEnabled", new amf::Null());
						set("playerStatSummaries", new amf::Null());
						set("maxPracticeGameSize", new amf::Null());
						set("reconnectInfo", new amf::Null());
						set("minor", new amf::Null());
						set("platformId", new amf::Null());
						set("gameTypeConfigs", new amf::Array());
						set("ipBalance", new amf::Null());
						set("clientSystemStates", new amf::Null());
						set("summonerCatalog", new amf::Null());
						set("languages", new amf::Array());
						set("allSummonerData", new amf::Null());
						set("leaverPenaltyLevel", new amf::Null());
						set("broadcastNotification", new amf::Null());
						set("matchMakingEnabled", new amf::Null());
						set("inGhostGame", new amf::Null());
					}

					double getRpBalance(){
						return get("rpBalance")->toDouble();
					}

					double getMinutesUntilMidnight(){
						return get("minutesUntilMidnight")->toDouble();
					}

					int getLeaverBusterPenaltyTime(){
						return get("leaverBusterPenaltyTime")->toInt();
					}

					bool getMinorShutdownEnforced(){
						return get("minorShutdownEnforced")->toBool();
					}

					bool getClientHeartBeatEnabled(){
						return get("clientHeartBeatEnabled")->toBool();
					}

					PlayerStatSummaries* getPlayerStatSummaries(){
						return (PlayerStatSummaries*)get("playerStatSummaries")->toObject();
					}

					int getMaxPracticeGameSize(){
						return get("maxPracticeGameSize")->toInt();
					}

					GameReconnectionInfo* getReconnectInfo(){
						return (GameReconnectionInfo*)get("reconnectInfo")->toObject();
					}

					bool getMinor(){
						return get("minor")->toBool();
					}

					std::string getPlatformId(){
						return get("platformId")->toString();
					}

					amf::Array_t<GameTypeConfig*>* getGameTypeConfigs(){
						return (amf::Array_t<GameTypeConfig*>*)get("gameTypeConfigs")->toArray();
					}

					double getIpBalance(){
						return get("ipBalance")->toDouble();
					}

					ClientSystemStatesNotification* getClientSystemStates(){
						return (ClientSystemStatesNotification*)get("clientSystemStates")->toObject();
					}

					SummonerCatalog* getSummonerCatalog(){
						return (SummonerCatalog*)get("summonerCatalog")->toObject();
					}

					amf::Array* getLanguages(){
						return get("languages")->toArray();
					}

					AllSummonerData* getAllSummonerData(){
						return (AllSummonerData*)get("allSummonerData")->toObject();
					}

					int getLeaverPenaltyLevel(){
						return get("leaverPenaltyLevel")->toInt();
					}

					BroadcastNotification* getBroadcastNotification(){
						return (BroadcastNotification*)get("broadcastNotification")->toObject();
					}

					bool getMatchMakingEnabled(){
						return get("matchMakingEnabled")->toBool();
					}

					bool getInGhostGame(){
						return get("inGhostGame")->toBool();
					}

					void setRpBalance(double value){
						set("rpBalance", amf::object_creator_t(value).mValue);
					}

					void setMinutesUntilMidnight(double value){
						set("minutesUntilMidnight", amf::object_creator_t(value).mValue);
					}

					void setLeaverBusterPenaltyTime(int value){
						set("leaverBusterPenaltyTime", amf::object_creator_t(value).mValue);
					}

					void setMinorShutdownEnforced(bool value){
						set("minorShutdownEnforced", amf::object_creator_t(value).mValue);
					}

					void setClientHeartBeatEnabled(bool value){
						set("clientHeartBeatEnabled", amf::object_creator_t(value).mValue);
					}

					void setPlayerStatSummaries(PlayerStatSummaries* value){
						set("playerStatSummaries", (Variant*)value);
					}

					void setMaxPracticeGameSize(int value){
						set("maxPracticeGameSize", amf::object_creator_t(value).mValue);
					}

					void setReconnectInfo(GameReconnectionInfo* value){
						set("reconnectInfo", (Variant*)value);
					}

					void setMinor(bool value){
						set("minor", amf::object_creator_t(value).mValue);
					}

					void setPlatformId(const std::string& value){
						set("platformId", amf::object_creator_t(value).mValue);
					}

					void setGameTypeConfigs(amf::Array* value){
						set("gameTypeConfigs", (Variant*)value);
					}

					void setIpBalance(double value){
						set("ipBalance", amf::object_creator_t(value).mValue);
					}

					void setClientSystemStates(ClientSystemStatesNotification* value){
						set("clientSystemStates", (Variant*)value);
					}

					void setSummonerCatalog(SummonerCatalog* value){
						set("summonerCatalog", (Variant*)value);
					}

					void setLanguages(amf::Array* value){
						set("languages", (Variant*)value);
					}

					void setAllSummonerData(AllSummonerData* value){
						set("allSummonerData", (Variant*)value);
					}

					void setLeaverPenaltyLevel(int value){
						set("leaverPenaltyLevel", amf::object_creator_t(value).mValue);
					}

					void setBroadcastNotification(BroadcastNotification* value){
						set("broadcastNotification", (Variant*)value);
					}

					void setMatchMakingEnabled(bool value){
						set("matchMakingEnabled", amf::object_creator_t(value).mValue);
					}

					void setInGhostGame(bool value){
						set("inGhostGame", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
