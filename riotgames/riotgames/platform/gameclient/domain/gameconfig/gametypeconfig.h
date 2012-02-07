#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace gameconfig {
					class GameTypeConfig : public amf::Object {
					public:
						GameTypeConfig(){
							setName("com.riotgames.platform.game.GameTypeConfigDTO");

							set("name", (amf::Null*)nullptr);
							set("mainPickTimerDuration", (amf::Null*)nullptr);
							set("maxAllowableBans", (amf::Null*)nullptr);
							set("pickMode", "DraftModeSinglePickStrategy");
							set("exclusivePick", (amf::Null*)nullptr);
							set("postPickTimerDuration", (amf::Null*)nullptr);
							set("allowTrades", (amf::Null*)nullptr);
							set("id", (amf::Null*)nullptr);
							set("banTimerDuration", (amf::Null*)nullptr);
						}

						std::string getName() const {
							return get("name");
						}

						double getMainPickTimerDuration() const {
							return get("mainPickTimerDuration");
						}

						int getMaxAllowableBans() const {
							return get("maxAllowableBans");
						}

						std::string getPickMode() const {
							return get("pickMode");
						}

						bool getExclusivePick() const {
							return get("exclusivePick");
						}

						double getPostPickTimerDuration() const {
							return get("postPickTimerDuration");
						}

						bool getAllowTrades() const {
							return get("allowTrades");
						}

						double getId() const {
							return get("id");
						}

						double getBanTimerDuration() const {
							return get("banTimerDuration");
						}

						void setName(const std::string& value){
							get("name") = value;
						}

						void setMainPickTimerDuration(double value){
							get("mainPickTimerDuration") = value;
						}

						void setMaxAllowableBans(int value){
							get("maxAllowableBans") = value;
						}

						void setPickMode(const std::string& value){
							get("pickMode") = value;
						}

						void setExclusivePick(bool value){
							get("exclusivePick") = value;
						}

						void setPostPickTimerDuration(double value){
							get("postPickTimerDuration") = value;
						}

						void setAllowTrades(bool value){
							get("allowTrades") = value;
						}

						void setId(double value){
							get("id") = value;
						}

						void setBanTimerDuration(double value){
							get("banTimerDuration") = value;
						}
					};
				};
			};
		};
	};
};
