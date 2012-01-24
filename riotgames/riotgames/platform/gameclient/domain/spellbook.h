#pragma once

#include "amf/variant.h"
#include "spellbookpage.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SpellBook : public amf::Object {
				public:
					SpellBook(){
						setName("com.riotgames.platform.summoner.spellbook.SpellBook");

						set("spellBookPages", new amf::Array());
						set("dateString", new amf::Null());
						set("summonerId", new amf::Null());
						set("bindingEventDispatcher", new amf::Null());
					}

					amf::Array_t<SpellBookPage*>* getSpellBookPages(){
						return (amf::Array_t<SpellBookPage*>*)get("spellBookPages")->toArray();
					}

					std::string getDateString(){
						return get("dateString")->toString();
					}

					double getSummonerId(){
						return get("summonerId")->toDouble();
					}

					void setSpellBookPages(amf::Array* value){
						set("spellBookPages", (Variant*)value);
					}

					void setDateString(const std::string& value){
						set("dateString", amf::object_creator_t(value).mValue);
					}

					void setSummonerId(double value){
						set("summonerId", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
