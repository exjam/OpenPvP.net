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

					amf::Array_t<TalentGroup*>* getTalentTree(){
						return (amf::Array_t<TalentGroup*>*)get("talentTree")->toArray();
					}

					amf::Array_t<RuneSlot*>* getSpellBookConfig(){
						return (amf::Array_t<RuneSlot*>*)get("spellBookConfig")->toArray();
					}

					void setTalentTree(amf::Array* value){
						set("talentTree", (Variant*)value);
					}

					void setSpellBookConfig(amf::Array* value){
						set("spellBookConfig", (Variant*)value);
					}
				};
			};
		};
	};
};
