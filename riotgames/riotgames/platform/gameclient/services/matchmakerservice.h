#pragma once

#include "flex/services.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace services {
				typedef amf::Object MatchMakerParams;

				class MatchMakerService : private flex::messaging::services::Service {
				public:
					MatchMakerService()
						: flex::messaging::services::Service("matchmakerService")
					{
					}

					void attachToQueue(MatchMakerParams* param1, const rtmp::CommandCallback& callback){
						invoke("attachToQueue", callback, param1);
					}

					void attachToQueues(MatchMakerParams* param1, const rtmp::CommandCallback& callback){
						invoke("attachToQueues", callback, param1);
					}

					void attachTeamToQueue(MatchMakerParams* param1, const rtmp::CommandCallback& callback){
						invoke("attachTeamToQueue", callback, param1);
					}

					void getAvailableQueues(const rtmp::CommandCallback& callback){
						invoke("getAvailableQueues", callback);
					}

					void purgeFromQueues(const rtmp::CommandCallback& callback){
						invoke("purgeFromQueues", callback);
					}

					void getQueueInfo(double param1, const rtmp::CommandCallback& callback){
						invoke("getQueueInfo", callback, param1);
					}

					void isMatchmakingEnabled(const rtmp::CommandCallback& callback){
						invoke("isMatchmakingEnabled", callback);
					}

					void cancelFromQueueIfPossible(double param1, const rtmp::CommandCallback& callback){
						invoke("cancelFromQueueIfPossible", callback, param1);
					}

					void acceptInviteForMatchmakingGame(const std::string& param1, amf::Object* param5, const rtmp::CommandCallback& callback){
						invoke("acceptInviteForMatchmakingGame", callback, param1, param5);
					}

					void attachTeamToQueues(MatchMakerParams* param1, const rtmp::CommandCallback& callback){
						invoke("attachTeamToQueues", callback, param1);
					}
				};

				extern MatchMakerService matchmakerService;
			};
		};
	};
};
