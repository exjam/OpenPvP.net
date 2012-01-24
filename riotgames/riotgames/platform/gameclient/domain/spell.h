#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class Spell : public amf::Object {
				public:
					Spell(){
						setName("com.riotgames.platform.summoner.Spell");

						set("displayName", new amf::Null());
						set("active", new amf::Null());
						set("name", new amf::Null());
						set("gameModes", new amf::Array());
						set("description", new amf::Null());
						set("spellId", new amf::Null());
						set("minLevel", new amf::Null());
					}

					std::string getDisplayName(){
						return get("displayName")->toString();
					}

					bool getActive(){
						return get("active")->toBool();
					}

					std::string getName(){
						return get("name")->toString();
					}

					amf::Array* getGameModes(){
						return get("gameModes")->toArray();
					}

					std::string getDescription(){
						return get("description")->toString();
					}

					int getSpellId(){
						return get("spellId")->toInt();
					}

					int getMinLevel(){
						return get("minLevel")->toInt();
					}

					void setDisplayName(const std::string& value){
						set("displayName", amf::object_creator_t(value).mValue);
					}

					void setActive(bool value){
						set("active", amf::object_creator_t(value).mValue);
					}

					void setName(const std::string& value){
						set("name", amf::object_creator_t(value).mValue);
					}

					void setGameModes(amf::Array* value){
						set("gameModes", (Variant*)value);
					}

					void setDescription(const std::string& value){
						set("description", amf::object_creator_t(value).mValue);
					}

					void setSpellId(int value){
						set("spellId", amf::object_creator_t(value).mValue);
					}

					void setMinLevel(int value){
						set("minLevel", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
