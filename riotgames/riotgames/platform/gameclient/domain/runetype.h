#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class RuneType : public amf::Object {
				public:
					RuneType(){
						setName("com.riotgames.platform.catalog.runes.RuneType");

						set("runeTypeId", (amf::Null*)nullptr);
					}

					int getRuneTypeId() const {
						return get("runeTypeId");
					}

					void setRuneTypeId(int value){
						get("runeTypeId") = value;
					}
				};
			};
		};
	};
};
