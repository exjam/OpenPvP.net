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

						set("minLevel", new amf::Null());
						set("id", new amf::Null());
						set("runeType", new amf::Null());
					}

					int getMinLevel(){
						return get("minLevel")->toInt();
					}

					int getId(){
						return get("id")->toInt();
					}

					RuneType* getRuneType(){
						return (RuneType*)get("runeType")->toObject();
					}

					void setMinLevel(int value){
						set("minLevel", amf::object_creator_t(value).mValue);
					}

					void setId(int value){
						set("id", amf::object_creator_t(value).mValue);
					}

					void setRuneType(RuneType* value){
						set("runeType", (Variant*)value);
					}
				};
			};
		};
	};
};
