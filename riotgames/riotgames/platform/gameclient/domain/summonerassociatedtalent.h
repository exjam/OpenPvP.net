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

						set("talent", (amf::Null*)nullptr);
						set("comp_id", (amf::Null*)nullptr);
						set("rank", (amf::Null*)nullptr);
					}

					const amf::Reference<Talent> getTalent() const {
						return get("talent").toObject();
					}

					const amf::Reference<SummonerAssociatedTalentPK> getComp_id(){
						return get("comp_id").toObject();
					}

					int getRank() const {
						return get("rank");
					}

					void setTalent(Talent* value){
						get("talent") = value;
					}

					void setComp_id(SummonerAssociatedTalentPK* value){
						set("comp_id", value);
					}

					void setRank(int value){
						get("rank") = value;
					}
				};
			};
		};
	};
};
