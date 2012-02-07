#pragma once

#include "amf/variant.h"
#include "basesummoner.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class Summoner : public BaseSummoner {
				public:
					Summoner(){
						setName("com.riotgames.platform.summoner.Summoner");
						
						set("name", (amf::Null*)nullptr);
						set("seasonOneTier", (amf::Null*)nullptr);
						set("nameChangeFlag", (amf::Null*)nullptr);
						set("sumId", (amf::Null*)nullptr);
						set("advancedTutorialFlag", (amf::Null*)nullptr);
						set("revisionId", (amf::Null*)nullptr);
						set("revisionDate", (amf::Null*)nullptr);
						set("helpFlag", (amf::Null*)nullptr);
						set("isMe", (amf::Null*)nullptr);
						set("socialNetworkUserIds", new amf::Array());
						set("tutorialFlag", (amf::Null*)nullptr);
						set("lastGameDate", (amf::Null*)nullptr);
						set("displayEloQuestionaire", (amf::Null*)nullptr);
					}

					std::string getSeasonOneTier() const {
						return get("seasonOneTier");
					}

					bool getNameChangeFlag() const {
						return get("nameChangeFlag");
					}

					double getSumId() const {
						return get("sumId");
					}

					bool getAdvancedTutorialFlag() const {
						return get("advancedTutorialFlag");
					}

					double getRevisionId() const {
						return get("revisionId");
					}

					amf::Date* getRevisionDate() const {
						return get("revisionDate").toDate();
					}

					bool getHelpFlag() const {
						return get("helpFlag");
					}

					bool getIsMe() const {
						return get("isMe");
					}

					const amf::Reference<amf::Array> getSocialNetworkUserIds() const {
						return get("socialNetworkUserIds");
					}

					bool getTutorialFlag() const {
						return get("tutorialFlag");
					}

					amf::Date* getLastGameDate() const {
						return get("lastGameDate").toDate();
					}

					bool getDisplayEloQuestionaire() const {
						return get("displayEloQuestionaire");
					}

					void setSeasonOneTier(const std::string& value){
						get("seasonOneTier") = value;
					}

					void setNameChangeFlag(bool value){
						get("nameChangeFlag") = value;
					}

					void setSumId(double value){
						get("sumId") = value;
					}

					void setAdvancedTutorialFlag(bool value){
						get("advancedTutorialFlag") = value;
					}

					void setRevisionId(double value){
						get("revisionId") = value;
					}

					void setRevisionDate(amf::Date* value){
						get("revisionDate") = value;
					}

					void setHelpFlag(bool value){
						get("helpFlag") = value;
					}

					void setIsMe(bool value){
						get("isMe") = value;
					}

					void setSocialNetworkUserIds(amf::Array* value){
						get("socialNetworkUserIds") = value;
					}

					void setTutorialFlag(bool value){
						get("tutorialFlag") = value;
					}

					void setLastGameDate(amf::Date* value){
						get("lastGameDate") = value;
					}

					void setDisplayEloQuestionaire(bool value){
						get("displayEloQuestionaire") = value;
					}
				};
			};
		};
	};
};
