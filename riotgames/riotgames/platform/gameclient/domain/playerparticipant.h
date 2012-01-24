#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {

				class PlayerParticipant : public amf::Object {
				public:
					PlayerParticipant(){
						setName("com.riotgames.platform.game.PlayerParticipant");

						set("profileIconId", amf::object_creator_t(-1).mValue);
						set("summonerLevel", new amf::Null());
						set("accountId", new amf::Null());
						set("clientInSynch", new amf::Null());
						set("summonerId", new amf::Null());
						set("lifetimeStatistics", new amf::Array());
					}

					int getProfileIconId(){
						return get("profileIconId")->toInt();
					}

					double getSummonerLevel(){
						return get("summonerLevel")->toDouble();
					}

					double getAccountId(){
						return get("accountId")->toDouble();
					}

					bool getClientInSynch(){
						return get("clientInSynch")->toBool();
					}

					double getSummonerId(){
						return get("summonerId")->toDouble();
					}

					amf::Array* getLifetimeStatistics(){
						return get("lifetimeStatistics")->toArray();
					}

					void setProfileIconId(int value){
						set("profileIconId", amf::object_creator_t(value).mValue);
					}

					void setSummonerLevel(double value){
						set("summonerLevel", amf::object_creator_t(value).mValue);
					}

					void setAccountId(double value){
						set("accountId", amf::object_creator_t(value).mValue);
					}

					void setClientInSynch(bool value){
						set("clientInSynch", amf::object_creator_t(value).mValue);
					}

					void setSummonerId(double value){
						set("summonerId", amf::object_creator_t(value).mValue);
					}

					void setLifetimeStatistics(amf::Array* value){
						set("lifetimeStatistics", (Variant*)value);
					}
				};
			};
		};
	};
};
