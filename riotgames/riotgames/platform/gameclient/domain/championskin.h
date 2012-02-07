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

						set("championId", (amf::Null*)nullptr);
						set("lastSelected", (amf::Null*)nullptr);
						set("freeToPlayReward", (amf::Null*)nullptr);
						set("owned", (amf::Null*)nullptr);
						set("skinId", (amf::Null*)nullptr);
						set("stillObtainable", true);
						set("isDefault", (amf::Null*)nullptr);
					}

					double getChampionId() const {
						return get("championId");
					}

					bool getLastSelected() const {
						return get("lastSelected");
					}

					bool getFreeToPlayReward() const {
						return get("freeToPlayReward");
					}

					bool getOwned() const {
						return get("owned");
					}

					double getSkinId() const {
						return get("skinId");
					}

					bool getStillObtainable() const {
						return get("stillObtainable");
					}

					bool getIsDefault() const {
						return get("isDefault");
					}

					void setChampionId(double value){
						get("championId") = value;
					}

					void setLastSelected(bool value){
						get("lastSelected") = value;
					}

					void setFreeToPlayReward(bool value){
						get("freeToPlayReward") = value;
					}

					void setOwned(bool value){
						get("owned") = value;
					}

					void setSkinId(double value){
						get("skinId") = value;
					}

					void setStillObtainable(bool value){
						get("stillObtainable") = value;
					}

					void setIsDefault(bool value){
						get("isDefault") = value;
					}
				};
			};
		};
	};
};
