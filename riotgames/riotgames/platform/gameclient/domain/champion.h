#pragma once

#include "amf/variant.h"
#include "rentableinventoryitem.h"
#include "championskin.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class Champion : public RentableInventoryItem {
				public:
					Champion(){
						setName("com.riotgames.platform.catalog.champion.ChampionDTO");

						set("ownedByYourTeam", true);
						set("active", (amf::Null*)nullptr);
						set("freeToPlayReward", (amf::Null*)nullptr);
						set("displayName", (amf::Null*)nullptr);
						set("championData", (amf::Null*)nullptr);
						set("botEnabled", (amf::Null*)nullptr);
						set("freeToPlay", (amf::Null*)nullptr);
						set("banned", false);
						set("defaultSkin", (amf::Null*)nullptr);
						set("championSkins", new amf::Array());
						set("championId", (amf::Null*)nullptr);
						set("ownedByEnemyTeam", true);
						set("description", (amf::Null*)nullptr);
						set("owned", (amf::Null*)nullptr);
					}

					bool getOwnedByYourTeam() const {
						return get("ownedByYourTeam");
					}

					bool getActive() const {
						return get("active");
					}

					bool getFreeToPlayReward() const {
						return get("freeToPlayReward");
					}

					std::string getDisplayName() const {
						return get("displayName");
					}

					const amf::Reference<Object> getChampionData() const {
						return get("championData").toObject();
					}

					bool getBotEnabled() const {
						return get("botEnabled");
					}

					bool getFreeToPlay() const {
						return get("freeToPlay");
					}

					bool getBanned() const {
						return get("banned");
					}

					const amf::Reference<ChampionSkin> getDefaultSkin() const {
						return get("defaultSkin").toObject();
					}

					amf::TypedArray<ChampionSkin*>* getChampionSkins() const {
						return (amf::TypedArray<ChampionSkin*>*)(amf::Array*)get("championSkins");
					}

					int getChampionId() const {
						return get("championId");
					}

					bool getOwnedByEnemyTeam() const {
						return get("ownedByEnemyTeam");
					}

					std::string getDescription() const {
						return get("description");
					}

					bool getOwned() const {
						return get("owned");
					}

					void setOwnedByYourTeam(bool value){
						get("ownedByYourTeam") = value;
					}

					void setActive(bool value){
						get("active") = value;
					}

					void setFreeToPlayReward(bool value){
						get("freeToPlayReward") = value;
					}

					void setDisplayName(const std::string& value){
						get("displayName") = value;
					}

					void setChampionData(Object* value){
						get("championData") = value;
					}

					void setBotEnabled(bool value){
						get("botEnabled") = value;
					}

					void setFreeToPlay(bool value){
						get("freeToPlay") = value;
					}

					void setBanned(bool value){
						get("banned") = value;
					}

					void setDefaultSkin(ChampionSkin* value){
						get("defaultSkin") = value;
					}

					void setChampionSkins(amf::Array* value){
						get("championSkins") = value;
					}

					void setChampionId(int value){
						get("championId") = value;
					}

					void setOwnedByEnemyTeam(bool value){
						get("ownedByEnemyTeam") = value;
					}

					void setDescription(const std::string& value){
						get("description") = value;
					}

					void setOwned(bool value){
						get("owned") = value;
					}
				};
			};
		};
	};
};
