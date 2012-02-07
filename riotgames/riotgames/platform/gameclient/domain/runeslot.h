#pragma once

#include "amf/variant.h"
#include "runetype.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class RuneSlot : public amf::Object {
				public:
					RuneSlot(){
						setName("com.riotgames.platform.summoner.RuneSlot");

						set("minLevel", (amf::Null*)nullptr);
						set("id", (amf::Null*)nullptr);
						set("runeType", (amf::Null*)nullptr);
					}

					int getMinLevel() const {
						return get("minLevel");
					}

					int getId() const {
						return get("id");
					}

					const amf::Reference<RuneType> getRuneType() const {
						return get("runeType").toObject();
					}

					void setMinLevel(int value){
						get("minLevel") = value;
					}

					void setId(int value){
						get("id") = value;
					}

					void setRuneType(RuneType* value){
						get("runeType") = value;
					}
				};
			};
		};
	};
};
