#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class Summoner : public amf::Object {
				public:
					Summoner(){
						setName("com.riotgames.platform.gameclient.domain.Summoner");

						set("seasonOneTier", new amf::Null());
						set("nameChangeFlag", new amf::Null());
						set("sumId", new amf::Null());
						set("advancedTutorialFlag", new amf::Null());
						set("revisionId", new amf::Null());
						set("revisionDate", new amf::Null());
						set("helpFlag", new amf::Null());
						set("isMe", new amf::Null());
						set("socialNetworkUserIds", new amf::Array());
						set("tutorialFlag", new amf::Null());
						set("lastGameDate", new amf::Null());
						set("displayEloQuestionaire", new amf::Null());
					}

					std::string getSeasonOneTier(){
						return get("seasonOneTier")->toString();
					}

					bool getNameChangeFlag(){
						return get("nameChangeFlag")->toBool();
					}

					double getSumId(){
						return get("sumId")->toDouble();
					}

					bool getAdvancedTutorialFlag(){
						return get("advancedTutorialFlag")->toBool();
					}

					double getRevisionId(){
						return get("revisionId")->toDouble();
					}

					amf::Date* getRevisionDate(){
						return get("revisionDate")->toDate();
					}

					bool getHelpFlag(){
						return get("helpFlag")->toBool();
					}

					bool getIsMe(){
						return get("isMe")->toBool();
					}

					amf::Array* getSocialNetworkUserIds(){
						return get("socialNetworkUserIds")->toArray();
					}

					bool getTutorialFlag(){
						return get("tutorialFlag")->toBool();
					}

					amf::Date* getLastGameDate(){
						return get("lastGameDate")->toDate();
					}

					bool getDisplayEloQuestionaire(){
						return get("displayEloQuestionaire")->toBool();
					}

					void setSeasonOneTier(const std::string& value){
						set("seasonOneTier", amf::object_creator_t(value).mValue);
					}

					void setNameChangeFlag(bool value){
						set("nameChangeFlag", amf::object_creator_t(value).mValue);
					}

					void setSumId(double value){
						set("sumId", amf::object_creator_t(value).mValue);
					}

					void setAdvancedTutorialFlag(bool value){
						set("advancedTutorialFlag", amf::object_creator_t(value).mValue);
					}

					void setRevisionId(double value){
						set("revisionId", amf::object_creator_t(value).mValue);
					}

					void setRevisionDate(amf::Date* value){
						set("revisionDate", (Variant*)value);
					}

					void setHelpFlag(bool value){
						set("helpFlag", amf::object_creator_t(value).mValue);
					}

					void setIsMe(bool value){
						set("isMe", amf::object_creator_t(value).mValue);
					}

					void setSocialNetworkUserIds(amf::Array* value){
						set("socialNetworkUserIds", (Variant*)value);
					}

					void setTutorialFlag(bool value){
						set("tutorialFlag", amf::object_creator_t(value).mValue);
					}

					void setLastGameDate(amf::Date* value){
						set("lastGameDate", (Variant*)value);
					}

					void setDisplayEloQuestionaire(bool value){
						set("displayEloQuestionaire", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
