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

						set("infTierMod", (amf::Null*)nullptr);
						set("expToNextLevel", (amf::Null*)nullptr);
						set("expTierMod", (amf::Null*)nullptr);
						set("summonerLevel", (amf::Null*)nullptr);
						set("summonerTier", (amf::Null*)nullptr);
					}

					double getInfTierMod() const {
						return get("infTierMod");
					}

					double getExpToNextLevel() const {
						return get("expToNextLevel");
					}

					double getExpTierMod() const {
						return get("expTierMod");
					}

					double getSummonerLevel() const {
						return get("summonerLevel");
					}

					double getSummonerTier() const {
						return get("summonerTier");
					}

					void setInfTierMod(double value){
						get("infTierMod") = value;
					}

					void setExpToNextLevel(double value){
						get("expToNextLevel") = value;
					}

					void setExpTierMod(double value){
						get("expTierMod") = value;
					}

					void setSummonerLevel(double value){
						get("summonerLevel") = value;
					}

					void setSummonerTier(double value){
						get("summonerTier") = value;
					}
				};
			};
		};
	};
};
