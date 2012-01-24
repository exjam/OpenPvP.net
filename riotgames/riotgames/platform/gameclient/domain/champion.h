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

						set("ownedByYourTeam", amf::object_creator_t(true).mValue);
						set("active", new amf::Null());
						set("freeToPlayReward", new amf::Null());
						set("displayName", new amf::Null());
						set("championData", new amf::Null());
						set("botEnabled", new amf::Null());
						set("freeToPlay", new amf::Null());
						set("banned", amf::object_creator_t(false).mValue);
						set("defaultSkin", new amf::Null());
						set("championSkins", new amf::Array());
						set("championId", new amf::Null());
						set("ownedByEnemyTeam", amf::object_creator_t(true).mValue);
						set("description", new amf::Null());
						set("owned", new amf::Null());
					}

					bool getOwnedByYourTeam(){
						return get("ownedByYourTeam")->toBool();
					}

					bool getActive(){
						return get("active")->toBool();
					}

					bool getFreeToPlayReward(){
						return get("freeToPlayReward")->toBool();
					}

					std::string getDisplayName(){
						return get("displayName")->toString();
					}

					Object* getChampionData(){
						return (Object*)get("championData")->toObject();
					}

					bool getBotEnabled(){
						return get("botEnabled")->toBool();
					}

					bool getFreeToPlay(){
						return get("freeToPlay")->toBool();
					}

					bool getBanned(){
						return get("banned")->toBool();
					}

					ChampionSkin* getDefaultSkin(){
						return (ChampionSkin*)get("defaultSkin")->toObject();
					}

					amf::Array_t<ChampionSkin*>* getChampionSkins(){
						return (amf::Array_t<ChampionSkin*>*)get("championSkins")->toArray();
					}

					int getChampionId(){
						return get("championId")->toInt();
					}

					bool getOwnedByEnemyTeam(){
						return get("ownedByEnemyTeam")->toBool();
					}

					std::string getDescription(){
						return get("description")->toString();
					}

					bool getOwned(){
						return get("owned")->toBool();
					}

					void setOwnedByYourTeam(bool value){
						set("ownedByYourTeam", amf::object_creator_t(value).mValue);
					}

					void setActive(bool value){
						set("active", amf::object_creator_t(value).mValue);
					}

					void setFreeToPlayReward(bool value){
						set("freeToPlayReward", amf::object_creator_t(value).mValue);
					}

					void setDisplayName(const std::string& value){
						set("displayName", amf::object_creator_t(value).mValue);
					}

					void setChampionData(Object* value){
						set("championData", (Variant*)value);
					}

					void setBotEnabled(bool value){
						set("botEnabled", amf::object_creator_t(value).mValue);
					}

					void setFreeToPlay(bool value){
						set("freeToPlay", amf::object_creator_t(value).mValue);
					}

					void setBanned(bool value){
						set("banned", amf::object_creator_t(value).mValue);
					}

					void setDefaultSkin(ChampionSkin* value){
						set("defaultSkin", (Variant*)value);
					}

					void setChampionSkins(amf::Array* value){
						set("championSkins", (Variant*)value);
					}

					void setChampionId(int value){
						set("championId", amf::object_creator_t(value).mValue);
					}

					void setOwnedByEnemyTeam(bool value){
						set("ownedByEnemyTeam", amf::object_creator_t(value).mValue);
					}

					void setDescription(const std::string& value){
						set("description", amf::object_creator_t(value).mValue);
					}

					void setOwned(bool value){
						set("owned", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
