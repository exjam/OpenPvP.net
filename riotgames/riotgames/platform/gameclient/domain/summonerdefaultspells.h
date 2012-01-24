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

						set("bindingEventDispatcher", new amf::Null());
						set("spellDefault1", new amf::Null());
						set("summonerId", new amf::Null());
						set("spellDefault2", new amf::Null());
					}

					Spell* getSpellDefault1(){
						return (Spell*)get("spellDefault1")->toObject();
					}

					double getSummonerId(){
						return get("summonerId")->toDouble();
					}

					Spell* getSpellDefault2(){
						return (Spell*)get("spellDefault2")->toObject();
					}

					void setSpellDefault1(Spell* value){
						set("spellDefault1", (Variant*)value);
					}

					void setSummonerId(double value){
						set("summonerId", amf::object_creator_t(value).mValue);
					}

					void setSpellDefault2(Spell* value){
						set("spellDefault2", (Variant*)value);
					}
				};
			};
		};
	};
};
