#pragma once

#include "amf/variant.h"
#include "spell.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SummonerDefaultSpells : public amf::Object {
				public:
					SummonerDefaultSpells(){
						setName("com.riotgames.platform.summoner.SummonerDefaultSpells");

						set("bindingEventDispatcher", (amf::Null*)nullptr);
						set("spellDefault1", (amf::Null*)nullptr);
						set("summonerId", (amf::Null*)nullptr);
						set("spellDefault2", (amf::Null*)nullptr);
					}

					const amf::Reference<Spell> getSpellDefault1() const {
						return get("spellDefault1").toObject();
					}

					double getSummonerId() const {
						return get("summonerId");
					}

					const amf::Reference<Spell> getSpellDefault2() const {
						return get("spellDefault2").toObject();
					}

					void setSpellDefault1(Spell* value){
						get("spellDefault1") = value;
					}

					void setSummonerId(double value){
						get("summonerId") = value;
					}

					void setSpellDefault2(Spell* value){
						get("spellDefault2") = value;
					}
				};
			};
		};
	};
};
