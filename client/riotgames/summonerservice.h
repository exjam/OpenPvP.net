#pragma once

#include "flex/services.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace services {
				class SummonerService : private flex::messaging::services::Service {
				public:
					SummonerService()
						: flex::messaging::services::Service("summonerService")
					{
					}

					void changeTalentRankings(double param1, amf::Object* param2, const rtmp::CommandCallback& callback){
						invoke("changeTalentRankings", callback, &amf::Number(param1), param2);
					}

					void checkSummonerName(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("checkSummonerName", callback, &amf::String(param1));
					}

					void getSocialNetworkFriends(const rtmp::CommandCallback& callback){
						invoke("getSocialNetworkFriends", callback);
					}

					void getAllSummonerData(double param1, const rtmp::CommandCallback& callback){
						invoke("getAllSummonerData", callback, &amf::Number(param1));
					}

					void getSummoner(double param1, const rtmp::CommandCallback& callback){
						invoke("getSummoner", callback, &amf::Number(param1));
					}

					void getSummonerByName(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("getSummonerByName", callback, &amf::String(param1));
					}

					void saveSocialNetworkFriendList(amf::Array* param1, amf::Array* param2, const std::string& param3, const rtmp::CommandCallback& callback){
						invoke("saveSocialNetworkFriendList", callback, param1, param2, &amf::String(param3));
					}

					void getPublicSummonersByAccountIds(amf::Array* param1, const rtmp::CommandCallback& callback){
						invoke("getPublicSummonersByAccountIds", callback, param1);
					}

					void getAllPublicSummonerDataByAccount(double param1, const rtmp::CommandCallback& callback){
						invoke("getAllPublicSummonerDataByAccount", callback, &amf::Number(param1));
					}

					/*void saveSummoner(Summoner* param1, const rtmp::CommandCallback& callback){
						invoke("saveSummoner", callback, param1);
					}*/

					void getSummonerByAccountId(double param1, const rtmp::CommandCallback& callback){
						invoke("getSummonerByAccountId", callback, &amf::Number(param1));
					}

					void getSummonerInternalNameByName(const std::string& param1, amf::Object* param5, const rtmp::CommandCallback& callback){
						invoke("getSummonerInternalNameByName", callback, &amf::String(param1), param5);
					}

					/*void createSummoner(Summoner* param1, const rtmp::CommandCallback& callback){
						invoke("createSummoner", callback, param1);
					}*/

					void getAllSummonerDataByAccount(double param1, const rtmp::CommandCallback& callback){
						invoke("getAllSummonerDataByAccount", callback, &amf::Number(param1));
					}

					void updateProfileIconId(int param1, const rtmp::CommandCallback& callback){
						invoke("updateProfileIconId", callback, &amf::Integer(param1));
					}

					void getSummonerCatalog(const rtmp::CommandCallback& callback){
						invoke("getSummonerCatalog", callback);
					}

					void updateSummonerSocialNetworkUser(const std::string& param1, const std::string& param2, const std::string& param3, const rtmp::CommandCallback& callback){
						invoke("updateSummonerSocialNetworkUser", callback, &amf::String(param1), &amf::String(param2), &amf::String(param3));
					}

					void createStubSummoner(const rtmp::CommandCallback& callback){
						invoke("createStubSummoner", callback);
					}

					void playerChangeSummonerName(double param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("playerChangeSummonerName", callback, &amf::Number(param1), &amf::String(param2));
					}

					void createDefaultSummoner(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("createDefaultSummoner", callback, &amf::String(param1));
					}

					void getSummonerNames(amf::Array* param1, const rtmp::CommandCallback& callback){
						invoke("getSummonerNames", callback, param1);
					}

					void getSocialNetworkUsers(amf::Array* param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("getSocialNetworkUsers", callback, param1, &amf::String(param2));
					}

					void resetTalents(double param1, const rtmp::CommandCallback& callback){
						invoke("resetTalents", callback, &amf::Number(param1));
					}
				};
			};
		};
	};
};
