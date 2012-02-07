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

						set("tltId", (amf::Null*)nullptr);
						set("sumId", (amf::Null*)nullptr);
					}

					int getTltId() const {
						return get("tltId");
					}

					double getSumId() const {
						return get("sumId");
					}

					void setTltId(int value){
						get("tltId") = value;
					}

					void setSumId(double value){
						get("sumId") = value;
					}
				};
			};
		};
	};
};
