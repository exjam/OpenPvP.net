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

						set("imagePath", (amf::Null*)nullptr);
						set("runeType", (amf::Null*)nullptr);
					}

					std::string getImagePath() const {
						return get("imagePath");
					}

					const amf::Reference<RuneType> getRuneType() const {
						return get("runeType").toObject();
					}

					void setImagePath(const std::string& value){
						get("imagePath") = value;
					}

					void setRuneType(RuneType* value){
						get("runeType") = value;
					}
				};
			};
		};
	};
};
