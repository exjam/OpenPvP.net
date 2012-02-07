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

						set("displayName", (amf::Null*)nullptr);
						set("active", (amf::Null*)nullptr);
						set("name", (amf::Null*)nullptr);
						set("gameModes", new amf::Array());
						set("description", (amf::Null*)nullptr);
						set("spellId", (amf::Null*)nullptr);
						set("minLevel", (amf::Null*)nullptr);
					}

					std::string getDisplayName() const {
						return get("displayName");
					}

					bool getActive() const {
						return get("active");
					}

					std::string getName() const {
						return get("name");
					}

					const amf::Reference<amf::Array> getGameModes() const {
						return get("gameModes");
					}

					std::string getDescription() const {
						return get("description");
					}

					int getSpellId() const {
						return get("spellId");
					}

					int getMinLevel() const {
						return get("minLevel");
					}

					void setDisplayName(const std::string& value){
						get("displayName") = value;
					}

					void setActive(bool value){
						get("active") = value;
					}

					void setName(const std::string& value){
						get("name") = value;
					}

					void setGameModes(amf::Array* value){
						get("gameModes") = value;
					}

					void setDescription(const std::string& value){
						get("description") = value;
					}

					void setSpellId(int value){
						get("spellId") = value;
					}

					void setMinLevel(int value){
						get("minLevel") = value;
					}
				};
			};
		};
	};
};
