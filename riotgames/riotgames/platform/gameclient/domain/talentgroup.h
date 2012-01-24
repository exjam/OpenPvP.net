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
						set("tltGroupId", new amf::Null());
						set("name", new amf::Null());
						set("index", new amf::Null());
					}

					amf::Array_t<TalentRow*>* getTalentRows(){
						return (amf::Array_t<TalentRow*>*)get("talentRows")->toArray();
					}

					int getTltGroupId(){
						return get("tltGroupId")->toInt();
					}

					std::string getName(){
						return get("name")->toString();
					}

					int getIndex(){
						return get("index")->toInt();
					}

					void setTalentRows(amf::Array* value){
						set("talentRows", (Variant*)value);
					}

					void setTltGroupId(int value){
						set("tltGroupId", amf::object_creator_t(value).mValue);
					}

					void setName(const std::string& value){
						set("name", amf::object_creator_t(value).mValue);
					}

					void setIndex(int value){
						set("index", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
