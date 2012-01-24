#pragma once

#include "amf/variant.h"
#include "summonerassociatedtalentpk.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {

				class SummonerAssociatedTalent : public amf::Object {
				public:
					SummonerAssociatedTalent(){
						setName("com.riotgames.platform.summoner.SummonerAssociatedTalent");

						set("talent", new amf::Null());
						set("comp_id", new amf::Null());
						set("rank", new amf::Null());
					}

					Talent* getTalent(){
						return (Talent*)get("talent")->toObject();
					}

					SummonerAssociatedTalentPK* getComp_id(){
						return (SummonerAssociatedTalentPK*)get("comp_id")->toObject();
					}

					int getRank(){
						return get("rank")->toInt();
					}

					void setTalent(Talent* value){
						set("talent", (Variant*)value);
					}

					void setComp_id(SummonerAssociatedTalentPK* value){
						set("comp_id", (Variant*)value);
					}

					void setRank(int value){
						set("rank", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
