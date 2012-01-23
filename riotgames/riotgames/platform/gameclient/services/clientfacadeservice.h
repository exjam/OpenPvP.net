#pragma once

#include "flex/services.h"
#include "../domain/playercomplaint.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace services {
				using namespace riotgames::platform::gameclient::domain;

				class ClientFacadeService : private flex::messaging::services::Service {
				public:
					ClientFacadeService()
						: flex::messaging::services::Service("clientFacadeService")
					{
					}

					void reportPlayer(PlayerComplaint* param1, const rtmp::CommandCallback& callback){
						invoke("reportPlayer", callback, param1);
					}

					void getLoginDataPacketForUser(const rtmp::CommandCallback& callback){
						invoke("getLoginDataPacketForUser", callback);
					}
				};

				extern ClientFacadeService clientFacadeService;
			};
		};
	};
};
