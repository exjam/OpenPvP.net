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

						set("runeTypeId", new amf::Null());
					}

					int getRuneTypeId(){
						return get("runeTypeId")->toInt();
					}

					void setRuneTypeId(int value){
						set("runeTypeId", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
