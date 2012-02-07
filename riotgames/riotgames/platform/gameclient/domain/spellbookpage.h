#pragma once

#include "amf/variant.h"
#include "slotentry.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SpellBookPage : public amf::Object {
				public:
					SpellBookPage(){
						setName("com.riotgames.platform.summoner.spellbook.SpellBookPage");

						set("isCurrent", (amf::Null*)nullptr);
						set("name", (amf::Null*)nullptr);
						set("createDate", (amf::Null*)nullptr);
						set("pageId", (amf::Null*)nullptr);
						set("summonerId", (amf::Null*)nullptr);
						set("slotEntries", new amf::Array());
					}

					bool getIsCurrent() const {
						return get("isCurrent");
					}

					std::string getName() const {
						return get("name");
					}

					amf::Date* getCreateDate() const {
						return get("createDate").toDate();
					}

					double getPageId() const {
						return get("pageId");
					}

					double getSummonerId() const {
						return get("summonerId");
					}

					amf::TypedArray<SlotEntry*>* getSlotEntries() const {
						return (amf::TypedArray<SlotEntry*>*)(amf::Array*)get("slotEntries");
					}

					void setIsCurrent(bool value){
						get("isCurrent") = value;
					}

					void setName(const std::string& value){
						get("name") = value;
					}

					void setCreateDate(amf::Date* value){
						get("createDate") = value;
					}

					void setPageId(double value){
						get("pageId") = value;
					}

					void setSummonerId(double value){
						get("summonerId") = value;
					}

					void setSlotEntries(amf::Array* value){
						get("slotEntries") = value;
					}
				};
			};
		};
	};
};
