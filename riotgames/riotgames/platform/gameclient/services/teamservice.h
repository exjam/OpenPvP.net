#pragma once

#include "flex/services.h"
#include "../domain/rankedTeams/teamid.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace services {
				using namespace riotgames::platform::gameclient::domain::rankedTeams;

				class TeamService : private flex::messaging::services::Service {
				public:
					TeamService()
						: flex::messaging::services::Service("summonerTeamService")
					{
					}

					void disbandTeam(TeamId* param1, const rtmp::CommandCallback& callback){
						invoke("disbandTeam", callback, param1);
					}

					void ownerLeaveTeam(double param1, TeamId* param2, const rtmp::CommandCallback& callback){
						invoke("leaveTeam", callback, &amf::Number(param1), param2);
					}

					void changeOwner(double param1, TeamId* param2, const rtmp::CommandCallback& callback){
						invoke("changeOwner", callback, &amf::Number(param1), param2);
					}

					void joinTeam(TeamId* param1, const rtmp::CommandCallback& callback){
						invoke("joinTeam", callback, param1);
					}

					void findTeamById(TeamId* param1, const rtmp::CommandCallback& callback){
						invoke("findTeamById", callback, param1);
					}

					void invitePlayer(double param1, TeamId* param2, const rtmp::CommandCallback& callback){
						invoke("invitePlayer", callback, &amf::Number(param1), param2);
					}

					void findTeamByTag(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("findTeamByTag", callback, &amf::String(param1));
					}

					void kickPlayer(double param1, TeamId* param2, const rtmp::CommandCallback& callback){
						invoke("kickPlayer", callback, &amf::Number(param1), param2);
					}

					void doesNameExist(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("doesNameExist", callback, &amf::String(param1));
					}

					void findOrCreateLocalPlayer(const rtmp::CommandCallback& callback){
						invoke("createPlayer", callback);
					}

					void doesTagExist(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("doesTagExist", callback, &amf::String(param1));
					}

					void findTeamByName(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("findTeamByName", callback, &amf::String(param1));
					}

					void createTeam(const std::string& param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("createTeam", callback, &amf::String(param1), &amf::String(param2));
					}

					void findPlayer(double param1, const rtmp::CommandCallback& callback){
						invoke("findPlayer", callback, &amf::Number(param1));
					}

					void leaveTeam(TeamId* param1, const rtmp::CommandCallback& callback){
						invoke("leaveTeam", callback, param1);
					}

					void declineInvite(TeamId* param1, const rtmp::CommandCallback& callback){
						invoke("declineInvite", callback, param1);
					}
				};

				extern TeamService summonerTeamService;
			};
		};
	};
};
