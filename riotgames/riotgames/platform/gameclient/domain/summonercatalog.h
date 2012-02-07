#pragma once

#include "amf/variant.h"
#include "runeslot.h"
#include "talentgroup.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SummonerCatalog : public amf::Object {
				public:
					SummonerCatalog(){
						setName("com.riotgames.platform.summoner.SummonerCatalog");

						set("talentTree", new amf::Array());
						set("spellBookConfig", new amf::Array());
					}

					amf::TypedArray<TalentGroup*>* getTalentTree() const {
						return (amf::TypedArray<TalentGroup*>*)(amf::Array*)get("talentTree");
					}

					amf::TypedArray<RuneSlot*>* getSpellBookConfig() const {
						return (amf::TypedArray<RuneSlot*>*)(amf::Array*)get("spellBookConfig");
					}

					void setTalentTree(amf::Array* value){
						get("talentTree") = value;
					}

					void setSpellBookConfig(amf::Array* value){
						get("spellBookConfig") = value;
					}
				};
			};
		};
	};
};
