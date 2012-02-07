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

						set("rpBalance", (amf::Null*)nullptr);
						set("minutesUntilMidnight", (amf::Null*)nullptr);
						set("leaverBusterPenaltyTime", (amf::Null*)nullptr);
						set("minorShutdownEnforced", (amf::Null*)nullptr);
						set("clientHeartBeatEnabled", (amf::Null*)nullptr);
						set("playerStatSummaries", (amf::Null*)nullptr);
						set("maxPracticeGameSize", (amf::Null*)nullptr);
						set("reconnectInfo", (amf::Null*)nullptr);
						set("minor", (amf::Null*)nullptr);
						set("platformId", (amf::Null*)nullptr);
						set("gameTypeConfigs", new amf::Array());
						set("ipBalance", (amf::Null*)nullptr);
						set("clientSystemStates", (amf::Null*)nullptr);
						set("summonerCatalog", (amf::Null*)nullptr);
						set("languages", new amf::Array());
						set("allSummonerData", (amf::Null*)nullptr);
						set("leaverPenaltyLevel", (amf::Null*)nullptr);
						set("broadcastNotification", (amf::Null*)nullptr);
						set("matchMakingEnabled", (amf::Null*)nullptr);
						set("inGhostGame", (amf::Null*)nullptr);
					}

					double getRpBalance() const {
						return get("rpBalance");
					}

					double getMinutesUntilMidnight() const {
						return get("minutesUntilMidnight");
					}

					int getLeaverBusterPenaltyTime() const {
						return get("leaverBusterPenaltyTime");
					}

					bool getMinorShutdownEnforced() const {
						return get("minorShutdownEnforced");
					}

					bool getClientHeartBeatEnabled() const {
						return get("clientHeartBeatEnabled");
					}

					const amf::Reference<PlayerStatSummaries> getPlayerStatSummaries() const {
						return get("playerStatSummaries").toObject();
					}

					int getMaxPracticeGameSize() const {
						return get("maxPracticeGameSize");
					}

					const amf::Reference<GameReconnectionInfo> getReconnectInfo() const {
						return get("reconnectInfo").toObject();
					}

					bool getMinor() const {
						return get("minor");
					}

					std::string getPlatformId() const {
						return get("platformId");
					}

					amf::TypedArray<GameTypeConfig*>* getGameTypeConfigs() const {
						return (amf::TypedArray<GameTypeConfig*>*)(amf::Array*)get("gameTypeConfigs");
					}

					double getIpBalance() const {
						return get("ipBalance");
					}

					const amf::Reference<ClientSystemStatesNotification> getClientSystemStates() const {
						return get("clientSystemStates").toObject();
					}

					const amf::Reference<SummonerCatalog> getSummonerCatalog() const {
						return get("summonerCatalog").toObject();
					}

					const amf::Reference<amf::Array> getLanguages() const {
						return get("languages");
					}

					const amf::Reference<AllSummonerData> getAllSummonerData() const {
						return get("allSummonerData").toObject();
					}

					int getLeaverPenaltyLevel() const {
						return get("leaverPenaltyLevel");
					}

					const amf::Reference<BroadcastNotification> getBroadcastNotification() const {
						return get("broadcastNotification").toObject();
					}

					bool getMatchMakingEnabled() const {
						return get("matchMakingEnabled");
					}

					bool getInGhostGame() const {
						return get("inGhostGame");
					}

					void setRpBalance(double value){
						get("rpBalance") = value;
					}

					void setMinutesUntilMidnight(double value){
						get("minutesUntilMidnight") = value;
					}

					void setLeaverBusterPenaltyTime(int value){
						get("leaverBusterPenaltyTime") = value;
					}

					void setMinorShutdownEnforced(bool value){
						get("minorShutdownEnforced") = value;
					}

					void setClientHeartBeatEnabled(bool value){
						get("clientHeartBeatEnabled") = value;
					}

					void setPlayerStatSummaries(PlayerStatSummaries* value){
						get("playerStatSummaries") = value;
					}

					void setMaxPracticeGameSize(int value){
						get("maxPracticeGameSize") = value;
					}

					void setReconnectInfo(GameReconnectionInfo* value){
						get("reconnectInfo") = value;
					}

					void setMinor(bool value){
						get("minor") = value;
					}

					void setPlatformId(const std::string& value){
						get("platformId") = value;
					}

					void setGameTypeConfigs(amf::Array* value){
						get("gameTypeConfigs") = value;
					}

					void setIpBalance(double value){
						get("ipBalance") = value;
					}

					void setClientSystemStates(ClientSystemStatesNotification* value){
						get("clientSystemStates") = value;
					}

					void setSummonerCatalog(SummonerCatalog* value){
						get("summonerCatalog") = value;
					}

					void setLanguages(amf::Array* value){
						get("languages") = value;
					}

					void setAllSummonerData(AllSummonerData* value){
						get("allSummonerData") = value;
					}

					void setLeaverPenaltyLevel(int value){
						get("leaverPenaltyLevel") = value;
					}

					void setBroadcastNotification(BroadcastNotification* value){
						get("broadcastNotification") = value;
					}

					void setMatchMakingEnabled(bool value){
						get("matchMakingEnabled") = value;
					}

					void setInGhostGame(bool value){
						get("inGhostGame") = value;
					}
				};
			};
		};
	};
};
