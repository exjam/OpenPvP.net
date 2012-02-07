#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {

				class SummonerLevelAndPoints : public amf::Object {
				public:
					SummonerLevelAndPoints(){
						setName("com.riotgames.platform.summoner.SummonerLevelAndPoints");

						set("expPoints", (amf::Null*)nullptr);
						set("summonerLevel", (amf::Null*)nullptr);
						set("infPoints", (amf::Null*)nullptr);
						set("sumId", (amf::Null*)nullptr);
					}

					double getExpPoints() const {
						return get("expPoints");
					}

					double getSummonerLevel() const {
						return get("summonerLevel");
					}

					double getInfPoints() const {
						return get("infPoints");
					}

					double getSumId() const {
						return get("sumId");
					}

					void setExpPoints(double value){
						get("expPoints") = value;
					}

					void setSummonerLevel(double value){
						get("summonerLevel") = value;
					}

					void setInfPoints(double value){
						get("infPoints") = value;
					}

					void setSumId(double value){
						get("sumId") = value;
					}
				};
			};
		};
	};
};
