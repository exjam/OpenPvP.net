#pragma once

#include "flex/services.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace services {
				class SummonerRuneService : private flex::messaging::services::Service {
				public:
					SummonerRuneService()
						: flex::messaging::services::Service("summonerRuneService")
					{
					}

					void getSummonerRunes(double param1, const rtmp::CommandCallback& callback){
						invoke("getSummonerRunes", callback, &amf::Number(param1));
					}

					void getSummonerRuneInventory(double param1, const rtmp::CommandCallback& callback){
						invoke("getSummonerRuneInventory", callback, &amf::Number(param1));
					}
				};

				extern SummonerRuneService summonerRuneService;
			};
		};
	};
};
