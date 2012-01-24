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

						set("isCurrent", new amf::Null());
						set("name", new amf::Null());
						set("createDate", new amf::Null());
						set("pageId", new amf::Null());
						set("summonerId", new amf::Null());
						set("slotEntries", new amf::Array());
					}

					bool getIsCurrent(){
						return get("isCurrent")->toBool();
					}

					std::string getName(){
						return get("name")->toString();
					}

					amf::Date* getCreateDate(){
						return get("createDate")->toDate();
					}

					double getPageId(){
						return get("pageId")->toDouble();
					}

					double getSummonerId(){
						return get("summonerId")->toDouble();
					}

					amf::Array_t<SlotEntry*>* getSlotEntries(){
						return (amf::Array_t<SlotEntry*>*)get("slotEntries")->toArray();
					}

					void setIsCurrent(bool value){
						set("isCurrent", amf::object_creator_t(value).mValue);
					}

					void setName(const std::string& value){
						set("name", amf::object_creator_t(value).mValue);
					}

					void setCreateDate(amf::Date* value){
						set("createDate", (Variant*)value);
					}

					void setPageId(double value){
						set("pageId", amf::object_creator_t(value).mValue);
					}

					void setSummonerId(double value){
						set("summonerId", amf::object_creator_t(value).mValue);
					}

					void setSlotEntries(amf::Array* value){
						set("slotEntries", (Variant*)value);
					}
				};
			};
		};
	};
};
