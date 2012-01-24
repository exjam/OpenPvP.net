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

							set("name", new amf::Null());
							set("mainPickTimerDuration", new amf::Null());
							set("maxAllowableBans", new amf::Null());
							set("pickMode", amf::object_creator_t("DraftModeSinglePickStrategy").mValue);
							set("exclusivePick", new amf::Null());
							set("postPickTimerDuration", new amf::Null());
							set("allowTrades", new amf::Null());
							set("id", new amf::Null());
							set("banTimerDuration", new amf::Null());
						}

						std::string getName(){
							return get("name")->toString();
						}

						double getMainPickTimerDuration(){
							return get("mainPickTimerDuration")->toDouble();
						}

						int getMaxAllowableBans(){
							return get("maxAllowableBans")->toInt();
						}

						std::string getPickMode(){
							return get("pickMode")->toString();
						}

						bool getExclusivePick(){
							return get("exclusivePick")->toBool();
						}

						double getPostPickTimerDuration(){
							return get("postPickTimerDuration")->toDouble();
						}

						bool getAllowTrades(){
							return get("allowTrades")->toBool();
						}

						double getId(){
							return get("id")->toDouble();
						}

						double getBanTimerDuration(){
							return get("banTimerDuration")->toDouble();
						}

						void setName(const std::string& value){
							set("name", amf::object_creator_t(value).mValue);
						}

						void setMainPickTimerDuration(double value){
							set("mainPickTimerDuration", amf::object_creator_t(value).mValue);
						}

						void setMaxAllowableBans(int value){
							set("maxAllowableBans", amf::object_creator_t(value).mValue);
						}

						void setPickMode(const std::string& value){
							set("pickMode", amf::object_creator_t(value).mValue);
						}

						void setExclusivePick(bool value){
							set("exclusivePick", amf::object_creator_t(value).mValue);
						}

						void setPostPickTimerDuration(double value){
							set("postPickTimerDuration", amf::object_creator_t(value).mValue);
						}

						void setAllowTrades(bool value){
							set("allowTrades", amf::object_creator_t(value).mValue);
						}

						void setId(double value){
							set("id", amf::object_creator_t(value).mValue);
						}

						void setBanTimerDuration(double value){
							set("banTimerDuration", amf::object_creator_t(value).mValue);
						}
					};
				};
			};
		};
	};
};
