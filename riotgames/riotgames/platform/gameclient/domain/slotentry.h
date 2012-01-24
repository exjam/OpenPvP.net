#pragma once

#include "amf/variant.h"
#include "rune.h"
#include "runeslot.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SlotEntry : public amf::Object {
				public:
					SlotEntry(){
						setName("com.riotgames.platform.summoner.spellbook.SlotEntry");

						set("rune", new amf::Null());
						set("runeSlot", new amf::Null());
					}

					Rune* getRune(){
						return (Rune*)get("rune")->toObject();
					}

					RuneSlot* getRuneSlot(){
						return (RuneSlot*)get("runeSlot")->toObject();
					}

					void setRune(Rune* value){
						set("rune", (Variant*)value);
					}

					void setRuneSlot(RuneSlot* value){
						set("runeSlot", (Variant*)value);
					}
				};
			};
		};
	};
};
