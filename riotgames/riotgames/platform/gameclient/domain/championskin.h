#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class ChampionSkin : public amf::Object {
				public:
					ChampionSkin(){
						setName("com.riotgames.platform.catalog.champion.ChampionSkinDTO");

						set("championId", new amf::Null());
						set("lastSelected", new amf::Null());
						set("freeToPlayReward", new amf::Null());
						set("owned", new amf::Null());
						set("skinId", new amf::Null());
						set("stillObtainable", amf::object_creator_t(true).mValue);
						set("isDefault", new amf::Null());
					}

					double getChampionId(){
						return get("championId")->toDouble();
					}

					bool getLastSelected(){
						return get("lastSelected")->toBool();
					}

					bool getFreeToPlayReward(){
						return get("freeToPlayReward")->toBool();
					}

					bool getOwned(){
						return get("owned")->toBool();
					}

					double getSkinId(){
						return get("skinId")->toDouble();
					}

					bool getStillObtainable(){
						return get("stillObtainable")->toBool();
					}

					bool getIsDefault(){
						return get("isDefault")->toBool();
					}

					void setChampionId(double value){
						set("championId", amf::object_creator_t(value).mValue);
					}

					void setLastSelected(bool value){
						set("lastSelected", amf::object_creator_t(value).mValue);
					}

					void setFreeToPlayReward(bool value){
						set("freeToPlayReward", amf::object_creator_t(value).mValue);
					}

					void setOwned(bool value){
						set("owned", amf::object_creator_t(value).mValue);
					}

					void setSkinId(double value){
						set("skinId", amf::object_creator_t(value).mValue);
					}

					void setStillObtainable(bool value){
						set("stillObtainable", amf::object_creator_t(value).mValue);
					}

					void setIsDefault(bool value){
						set("isDefault", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
