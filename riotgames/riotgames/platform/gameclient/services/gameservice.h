#pragma once

#include "flex/services.h"
#include "../domain/gamedto.h"
#include "../domain/champion.h"
#include "../domain/newgamesummary.h"
#include "../domain/botparticipant.h"
#include "../domain/game/gamemap.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			using namespace domain;
			using namespace domain::game;

			namespace services {
				class GameService : private flex::messaging::services::Service {
				public:
					GameService()
						: flex::messaging::services::Service("gameService")
					{
					}

					void selectChampion(int32 championId, const rtmp::CommandCallback& callback){
						invoke("selectChampion", callback, championId);
					}

					void setClientReceivedMaestroMessage(double param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("setClientReceivedMaestroMessage", callback, param1, param2);
					}

					void setClientReceivedGameMessage(double param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("setClientReceivedGameMessage", callback, param1, param2);
					}

					void getLatestGameTimerState(GameDTO* param1, const rtmp::CommandCallback& callback){
						invoke("getLatestGameTimerState", callback, &amf::Number(param1->getId()), &amf::String(param1->getGameStateString()), &amf::Integer(param1->getPickTurn()));
					}

					void declineObserverReconnect(const rtmp::CommandCallback& callback){
						invoke("declineObserverReconnect", callback);
					}

					void createTutorialGame(uint32 param1, const rtmp::CommandCallback& callback){
						invoke("createTutorialGame", callback, param1);
					}

					void championSelectCompleted(const rtmp::CommandCallback& callback){
						invoke("championSelectCompleted", callback);
					}

					void createGame(const std::string& param1, const std::string& param2, GameMap* param3, int param4, const std::string& param5, int param6, const std::string& param7, const rtmp::CommandCallback& callback){
						invoke("createPracticeGame", callback, param1, param2, param3, param4, param5, param6, param7);
					}

					void banChampionCompleted(const rtmp::CommandCallback& callback){
						invoke("banChampionCompleted", callback);
					}

					void switchPlayerToObserver(double param1, const rtmp::CommandCallback& callback){
						invoke("switchPlayerToObserver", callback, param1);
					}

					void banUserFromGame(double param1, double param2, const rtmp::CommandCallback& callback){
						invoke("banUserFromGame", callback, param1, param2);
					}

					void banChampion(int param1, const rtmp::CommandCallback& callback){
						invoke("banChampion", callback, param1);
					}

					void getChampionsForBan(const rtmp::CommandCallback& callback){
						invoke("getChampionsForBan", callback);
					}

					void claimGame(NewGameSummary* param1, const rtmp::CommandCallback& callback){
						invoke("claimGame", callback, param1);
					}

					void switchObserverToPlayer(double param1, double param2, const rtmp::CommandCallback& callback){
						invoke("switchObserverToPlayer", callback, param1, param2);
					}

					void cancelSelectChampion(const rtmp::CommandCallback& callback){
						invoke("cancelSelectChampion", callback);
					}

					void startChampionSelection(double param1, double param2, const rtmp::CommandCallback& callback){
						invoke("startChampionSelection", callback, param1, param2);
					}

					void switchTeams(double param1, const rtmp::CommandCallback& callback){
						invoke("switchTeams", callback, param1);
					}

					void tradeChampions(double param1, const rtmp::CommandCallback& callback){
						invoke("tradeChampion", callback, param1);
					}

					void selectSpells(amf::Array* param1, const rtmp::CommandCallback& callback){
						invoke("selectSpells", callback, param1->at(0), param1->at(1));
					}

					void quitGame(const rtmp::CommandCallback& callback){
						invoke("quitGame", callback);
					}

					void selectChampionSkin(ChampionSkin* param1, const rtmp::CommandCallback& callback){
						invoke("selectChampionSkin", callback, param1->getChampionId(), param1->getSkinId());
					}

					void removeBotChampion(Champion* param1, BotParticipant* param2, const rtmp::CommandCallback& callback){
						invoke("removeBotChampion", callback, param1->getChampionId(), param2);
					}

					void getGameReconnectionInfo(const rtmp::CommandCallback& callback){
						invoke("retrieveInProgressGameInfo", callback);
					}

					void getGame(double param1, const rtmp::CommandCallback& callback){
						invoke("getGame", callback, param1);
					}

					void banObserverFromGame(double param1, double param2, const rtmp::CommandCallback& callback){
						invoke("banObserverFromGame", callback, param1, param2);
					}

					void getPracticeGameForUser(const rtmp::CommandCallback& callback){
						invoke("getGameForUser", callback);
					}

					void getAuditInfo(amf::Array* param3, const rtmp::CommandCallback& callback){
						invoke("listAuditInfo", callback, param3);
					}

					void selectBotChampion(Champion* param1, BotParticipant* param2, const rtmp::CommandCallback& callback){
						invoke("selectBotChampion", callback, &amf::Number(param1->getChampionId()), param2);
					}

					void observeGame(double param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("observeGame", callback, param1, param2);
					}

					void getAvailablePracticeGames(const rtmp::CommandCallback& callback){
						invoke("listAllPracticeGames", callback);
					}

					void joinGame(double param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("joinGame", callback, param1, param2);
					}

					void spectateGameInProgress(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("retrieveInProgressSpectatorGameInfo", callback, param1);
					}
				};

				extern GameService gameService;
			};
		};
	};
};
