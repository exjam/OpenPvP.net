#pragma once

#include "amf/variant.h"
#include "talent.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class TalentRow : public amf::Object {
				public:
					TalentRow(){
						setName("com.riotgames.platform.summoner.TalentRow");

						set("tltRowId", new amf::Null());
						set("talents", new amf::Array());
						set("tltGroupId", new amf::Null());
						set("pointsToActivate", new amf::Null());
						set("index", new amf::Null());
					}

					int getTltRowId(){
						return get("tltRowId")->toInt();
					}

					amf::Array_t<Talent*>* getTalents(){
						return (amf::Array_t<Talent*>*)get("talents")->toArray();
					}

					int getTltGroupId(){
						return get("tltGroupId")->toInt();
					}

					int getPointsToActivate(){
						return get("pointsToActivate")->toInt();
					}

					int getIndex(){
						return get("index")->toInt();
					}

					void setTltRowId(int value){
						set("tltRowId", amf::object_creator_t(value).mValue);
					}

					void setTalents(amf::Array* value){
						set("talents", (Variant*)value);
					}

					void setTltGroupId(int value){
						set("tltGroupId", amf::object_creator_t(value).mValue);
					}

					void setPointsToActivate(int value){
						set("pointsToActivate", amf::object_creator_t(value).mValue);
					}

					void setIndex(int value){
						set("index", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
