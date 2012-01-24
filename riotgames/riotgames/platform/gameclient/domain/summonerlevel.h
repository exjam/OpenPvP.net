#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SummonerLevel : public amf::Object {
				public:
					SummonerLevel(){
						setName("com.riotgames.platform.summoner.SummonerLevel");

						set("infTierMod", new amf::Null());
						set("expToNextLevel", new amf::Null());
						set("expTierMod", new amf::Null());
						set("summonerLevel", new amf::Null());
						set("summonerTier", new amf::Null());
					}

					double getInfTierMod(){
						return get("infTierMod")->toDouble();
					}

					double getExpToNextLevel(){
						return get("expToNextLevel")->toDouble();
					}

					double getExpTierMod(){
						return get("expTierMod")->toDouble();
					}

					double getSummonerLevel(){
						return get("summonerLevel")->toDouble();
					}

					double getSummonerTier(){
						return get("summonerTier")->toDouble();
					}

					void setInfTierMod(double value){
						set("infTierMod", amf::object_creator_t(value).mValue);
					}

					void setExpToNextLevel(double value){
						set("expToNextLevel", amf::object_creator_t(value).mValue);
					}

					void setExpTierMod(double value){
						set("expTierMod", amf::object_creator_t(value).mValue);
					}

					void setSummonerLevel(double value){
						set("summonerLevel", amf::object_creator_t(value).mValue);
					}

					void setSummonerTier(double value){
						set("summonerTier", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
