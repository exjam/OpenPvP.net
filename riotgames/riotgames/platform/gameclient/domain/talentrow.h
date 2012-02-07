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

						set("tltRowId", (amf::Null*)nullptr);
						set("talents", new amf::Array());
						set("tltGroupId", (amf::Null*)nullptr);
						set("pointsToActivate", (amf::Null*)nullptr);
						set("index", (amf::Null*)nullptr);
					}

					int getTltRowId() const {
						return get("tltRowId");
					}

					amf::TypedArray<Talent*>* getTalents() const {
						return (amf::TypedArray<Talent*>*)(amf::Array*)get("talents");
					}

					int getTltGroupId() const {
						return get("tltGroupId");
					}

					int getPointsToActivate() const {
						return get("pointsToActivate");
					}

					int getIndex() const {
						return get("index");
					}

					void setTltRowId(int value){
						get("tltRowId") = value;
					}

					void setTalents(amf::Array* value){
						get("talents") = value;
					}

					void setTltGroupId(int value){
						get("tltGroupId") = value;
					}

					void setPointsToActivate(int value){
						get("pointsToActivate") = value;
					}

					void setIndex(int value){
						get("index") = value;
					}
				};
			};
		};
	};
};
