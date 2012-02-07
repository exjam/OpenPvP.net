#pragma once

#include "amf/variant.h"
#include "talentrow.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class TalentGroup : public amf::Object {
				public:
					TalentGroup(){
						setName("com.riotgames.platform.summoner.TalentGroup");

						set("talentRows", new amf::Array());
						set("tltGroupId", (amf::Null*)nullptr);
						set("name", (amf::Null*)nullptr);
						set("index", (amf::Null*)nullptr);
					}

					amf::TypedArray<TalentRow*>* getTalentRows() const {
						return (amf::TypedArray<TalentRow*>*)(amf::Array*)get("talentRows");
					}

					int getTltGroupId() const {
						return get("tltGroupId");
					}

					std::string getName() const {
						return get("name");
					}

					int getIndex() const {
						return get("index");
					}

					void setTalentRows(amf::Array* value){
						get("talentRows") = value;
					}

					void setTltGroupId(int value){
						get("tltGroupId") = value;
					}

					void setName(const std::string& value){
						get("name") = value;
					}

					void setIndex(int value){
						get("index") = value;
					}
				};
			};
		};
	};
};
