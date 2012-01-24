#pragma once

#include "amf/variant.h"
#include "runetype.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class Rune : public amf::Object {
				public:
					Rune(){
						setName("com.riotgames.platform.summoner.Rune");

						set("imagePath", new amf::Null());
						set("runeType", new amf::Null());
					}

					std::string getImagePath(){
						return get("imagePath")->toString();
					}

					RuneType* getRuneType(){
						return (RuneType*)get("runeType")->toObject();
					}

					void setImagePath(const std::string& value){
						set("imagePath", amf::object_creator_t(value).mValue);
					}

					void setRuneType(RuneType* value){
						set("runeType", (Variant*)value);
					}
				};
			};
		};
	};
};
