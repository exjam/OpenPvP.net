#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SummonerAssociatedTalentPK : public amf::Object {
				public:
					SummonerAssociatedTalentPK(){
						setName("com.riotgames.platform.summoner.SummonerAssociatedTalentPK");

						set("tltId", new amf::Null());
						set("sumId", new amf::Null());
					}

					int getTltId(){
						return get("tltId")->toInt();
					}

					double getSumId(){
						return get("sumId")->toDouble();
					}

					void setTltId(int value){
						set("tltId", amf::object_creator_t(value).mValue);
					}

					void setSumId(double value){
						set("sumId", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
