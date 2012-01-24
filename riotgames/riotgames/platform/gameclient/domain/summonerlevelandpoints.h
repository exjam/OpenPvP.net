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

						set("expPoints", new amf::Null());
						set("summonerLevel", new amf::Null());
						set("infPoints", new amf::Null());
						set("sumId", new amf::Null());
					}

					double getExpPoints(){
						return get("expPoints")->toDouble();
					}

					double getSummonerLevel(){
						return get("summonerLevel")->toDouble();
					}

					double getInfPoints(){
						return get("infPoints")->toDouble();
					}

					double getSumId(){
						return get("sumId")->toDouble();
					}

					void setExpPoints(double value){
						set("expPoints", amf::object_creator_t(value).mValue);
					}

					void setSummonerLevel(double value){
						set("summonerLevel", amf::object_creator_t(value).mValue);
					}

					void setInfPoints(double value){
						set("infPoints", amf::object_creator_t(value).mValue);
					}

					void setSumId(double value){
						set("sumId", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
