#pragma once

#include "amf/variant.h"
#include "summonerassociatedtalent.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {

				class SummonerTalentsAndPoints : public amf::Object {
				public:
					SummonerTalentsAndPoints(){
						setName("com.riotgames.platform.summoner.SummonerTalentsAndPoints");

						set("talentPoints", (amf::Null*)nullptr);
						set("unusedTalentPoints", (amf::Null*)nullptr);
						set("summonerAssociatedTalents", new amf::Array());
						set("summonerId", (amf::Null*)nullptr);
					}

					double getTalentPoints() const {
						return get("talentPoints");
					}

					double getUnusedTalentPoints() const {
						return get("unusedTalentPoints");
					}

					amf::TypedArray<SummonerAssociatedTalent*>* getSummonerAssociatedTalents() const {
						return (amf::TypedArray<SummonerAssociatedTalent*>*)(amf::Array*)get("summonerAssociatedTalents");
					}

					double getSummonerId() const {
						return get("summonerId");
					}

					void setTalentPoints(double value){
						get("talentPoints") = value;
					}

					void setUnusedTalentPoints(double value){
						get("unusedTalentPoints") = value;
					}

					void setSummonerAssociatedTalents(amf::Array* value){
						get("summonerAssociatedTalents") = value;
					}

					void setSummonerId(double value){
						get("summonerId") = value;
					}
				};
			};
		};
	};
};
