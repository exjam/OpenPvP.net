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
						set("dateString", (amf::Null*)nullptr);
						set("summonerId", (amf::Null*)nullptr);
						set("bindingEventDispatcher", (amf::Null*)nullptr);
					}

					amf::TypedArray<SpellBookPage*>* getSpellBookPages() const {
						return (amf::TypedArray<SpellBookPage*>*)(amf::Array*)get("spellBookPages");
					}

					std::string getDateString() const {
						return get("dateString");
					}

					double getSummonerId() const {
						return get("summonerId");
					}

					void setSpellBookPages(amf::Array* value){
						get("spellBookPages") = value;
					}

					void setDateString(const std::string& value){
						get("dateString") = value;
					}

					void setSummonerId(double value){
						get("summonerId") = value;
					}
				};
			};
		};
	};
};
