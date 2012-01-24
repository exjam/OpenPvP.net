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

						set("talentPoints", new amf::Null());
						set("unusedTalentPoints", new amf::Null());
						set("summonerAssociatedTalents", new amf::Array());
						set("summonerId", new amf::Null());
					}

					double getTalentPoints(){
						return get("talentPoints")->toDouble();
					}

					double getUnusedTalentPoints(){
						return get("unusedTalentPoints")->toDouble();
					}

					amf::Array_t<SummonerAssociatedTalent*>* getSummonerAssociatedTalents(){
						return (amf::Array_t<SummonerAssociatedTalent*>*)get("summonerAssociatedTalents")->toArray();
					}

					double getSummonerId(){
						return get("summonerId")->toDouble();
					}

					void setTalentPoints(double value){
						set("talentPoints", amf::object_creator_t(value).mValue);
					}

					void setUnusedTalentPoints(double value){
						set("unusedTalentPoints", amf::object_creator_t(value).mValue);
					}

					void setSummonerAssociatedTalents(amf::Array* value){
						set("summonerAssociatedTalents", (Variant*)value);
					}

					void setSummonerId(double value){
						set("summonerId", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
