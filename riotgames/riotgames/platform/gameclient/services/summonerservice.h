#pragma once

#include "flex/services.h"
#include "../domain/summoner.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			using namespace domain;

			namespace services {
				class SummonerService : private flex::messaging::services::Service {
				public:
					SummonerService()
						: flex::messaging::services::Service("summonerService")
					{
					}

					void changeTalentRankings(double param1, amf::Object* param2, const rtmp::CommandCallback& callback){
						invoke("changeTalentRankings", callback, param1, param2);
					}

					void checkSummonerName(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("checkSummonerName", callback, param1);
					}

					void getSocialNetworkFriends(const rtmp::CommandCallback& callback){
						invoke("getSocialNetworkFriends", callback);
					}

					void getAllSummonerData(double param1, const rtmp::CommandCallback& callback){
						invoke("getAllSummonerData", callback, param1);
					}

					void getSummoner(double param1, const rtmp::CommandCallback& callback){
						invoke("getSummoner", callback, param1);
					}

					void getSummonerByName(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("getSummonerByName", callback, param1);
					}

					void saveSocialNetworkFriendList(amf::Array* param1, amf::Array* param2, const std::string& param3, const rtmp::CommandCallback& callback){
						invoke("saveSocialNetworkFriendList", callback, param1, param2, param3);
					}

					void getPublicSummonersByAccountIds(amf::Array* param1, const rtmp::CommandCallback& callback){
						invoke("getPublicSummonersByAccountIds", callback, param1);
					}

					void getAllPublicSummonerDataByAccount(double param1, const rtmp::CommandCallback& callback){
						invoke("getAllPublicSummonerDataByAccount", callback, param1);
					}

					void saveSummoner(Summoner* param1, const rtmp::CommandCallback& callback){
						invoke("saveSummoner", callback, param1);
					}

					void getSummonerByAccountId(double param1, const rtmp::CommandCallback& callback){
						invoke("getSummonerByAccountId", callback, param1);
					}

					void getSummonerInternalNameByName(const std::string& param1, amf::Object* param5, const rtmp::CommandCallback& callback){
						invoke("getSummonerInternalNameByName", callback, param1, param5);
					}

					void createSummoner(Summoner* param1, const rtmp::CommandCallback& callback){
						invoke("createSummoner", callback, param1);
					}

					void getAllSummonerDataByAccount(double param1, const rtmp::CommandCallback& callback){
						invoke("getAllSummonerDataByAccount", callback, param1);
					}

					void updateProfileIconId(int param1, const rtmp::CommandCallback& callback){
						invoke("updateProfileIconId", callback, param1);
					}

					void getSummonerCatalog(const rtmp::CommandCallback& callback){
						invoke("getSummonerCatalog", callback);
					}

					void updateSummonerSocialNetworkUser(const std::string& param1, const std::string& param2, const std::string& param3, const rtmp::CommandCallback& callback){
						invoke("updateSummonerSocialNetworkUser", callback, param1, param2, param3);
					}

					void createStubSummoner(const rtmp::CommandCallback& callback){
						invoke("createStubSummoner", callback);
					}

					void playerChangeSummonerName(double param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("playerChangeSummonerName", callback, param1, param2);
					}

					void createDefaultSummoner(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("createDefaultSummoner", callback, param1);
					}

					void getSummonerNames(amf::Array* param1, const rtmp::CommandCallback& callback){
						invoke("getSummonerNames", callback, param1);
					}

					void getSocialNetworkUsers(amf::Array* param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("getSocialNetworkUsers", callback, param1, param2);
					}

					void resetTalents(double param1, const rtmp::CommandCallback& callback){
						invoke("resetTalents", callback, param1);
					}
				};

				extern SummonerService summonerService;
			};
		};
	};
};
