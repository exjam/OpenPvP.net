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

						set("rune", (amf::Null*)nullptr);
						set("runeSlot", (amf::Null*)nullptr);
					}

					const amf::Reference<Rune> getRune() const {
						return get("rune").toObject();
					}

					const amf::Reference<RuneSlot> getRuneSlot() const {
						return get("runeSlot").toObject();
					}

					void setRune(Rune* value){
						get("rune") = value;
					}

					void setRuneSlot(RuneSlot* value){
						get("runeSlot") = value;
					}
				};
			};
		};
	};
};
