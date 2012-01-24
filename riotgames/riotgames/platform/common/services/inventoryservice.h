#pragma once

#include "flex/services.h"

namespace riotgames {
	namespace platform {
		namespace common {
			namespace services {
				class InventoryService : private flex::messaging::services::Service {
				public:
					InventoryService()
						: flex::messaging::services::Service("inventoryService")
					{
					}

					void useRuneCombiner(double param1, amf::Array* param2, const rtmp::CommandCallback& callback){
						invoke("useRuneCombiner", callback, &amf::Number(param1), param2);
					}

					void useGrabBag(double param1, const rtmp::CommandCallback& callback){
						invoke("useGrabBag", callback, &amf::Number(param1));
					}

					void getAvailableChampions(const rtmp::CommandCallback& callback){
						invoke("getAvailableChampions", callback);
					}

					void retrieveInventoryTypes(const rtmp::CommandCallback& callback){
						invoke("retrieveInventoryTypes", callback);
					}

					void isStoreEnabled(const rtmp::CommandCallback& callback){
						invoke("isStoreEnabled", callback);
					}

					void getAllRuneCombiners(const rtmp::CommandCallback& callback){
						invoke("getAllRuneCombiners", callback);
					}

					void giftFacebookFan(const rtmp::CommandCallback& callback){
						invoke("giftFacebookFan", callback);
					}

					void getSumonerActiveBoosts(const rtmp::CommandCallback& callback){
						invoke("getSumonerActiveBoosts", callback);
					}
				};

				extern InventoryService inventoryService;
			};
		};
	};
};
