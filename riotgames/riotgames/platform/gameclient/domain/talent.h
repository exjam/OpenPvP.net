#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class Talent : public amf::Object {
				public:
					Talent(){
						setName("com.riotgames.platform.summoner.Talent");

						set("gameCode", (amf::Null*)nullptr);
						set("prereqTalentGameCode", (amf::Null*)nullptr);
						set("talentGroupId", (amf::Null*)nullptr);
						set("name", (amf::Null*)nullptr);
						set("level4Desc", (amf::Null*)nullptr);
						set("minLevel", (amf::Null*)nullptr);
						set("maxRank", (amf::Null*)nullptr);
						set("tltId", (amf::Null*)nullptr);
						set("index", (amf::Null*)nullptr);
						set("talentRowId", (amf::Null*)nullptr);
						set("level2Desc", (amf::Null*)nullptr);
						set("minTier", (amf::Null*)nullptr);
						set("level3Desc", (amf::Null*)nullptr);
						set("level5Desc", (amf::Null*)nullptr);
						set("level1Desc", (amf::Null*)nullptr);
					}

					int getGameCode() const {
						return get("gameCode");
					}

					int getPrereqTalentGameCode() const {
						return get("prereqTalentGameCode");
					}

					int getTalentGroupId() const {
						return get("talentGroupId");
					}

					std::string getName() const {
						return get("name");
					}

					int getLevel4Desc() const {
						return get("level4Desc");
					}

					int getMinLevel() const {
						return get("minLevel");
					}

					int getMaxRank() const {
						return get("maxRank");
					}

					int getTltId() const {
						return get("tltId");
					}

					int getIndex() const {
						return get("index");
					}

					int getTalentRowId() const {
						return get("talentRowId");
					}

					int getLevel2Desc() const {
						return get("level2Desc");
					}

					int getMinTier() const {
						return get("minTier");
					}

					int getLevel3Desc() const {
						return get("level3Desc");
					}

					int getLevel5Desc() const {
						return get("level5Desc");
					}

					int getLevel1Desc() const {
						return get("level1Desc");
					}

					void setGameCode(int value){
						get("gameCode") = value;
					}

					void setPrereqTalentGameCode(int value){
						get("prereqTalentGameCode") = value;
					}

					void setTalentGroupId(int value){
						get("talentGroupId") = value;
					}

					void setName(const std::string& value){
						get("name") = value;
					}

					void setLevel4Desc(int value){
						get("level4Desc") = value;
					}

					void setMinLevel(int value){
						get("minLevel") = value;
					}

					void setMaxRank(int value){
						get("maxRank") = value;
					}

					void setTltId(int value){
						get("tltId") = value;
					}

					void setIndex(int value){
						get("index") = value;
					}

					void setTalentRowId(int value){
						get("talentRowId") = value;
					}

					void setLevel2Desc(int value){
						get("level2Desc") = value;
					}

					void setMinTier(int value){
						get("minTier") = value;
					}

					void setLevel3Desc(int value){
						get("level3Desc") = value;
					}

					void setLevel5Desc(int value){
						get("level5Desc") = value;
					}

					void setLevel1Desc(int value){
						get("level1Desc") = value;
					}
				};
			};
		};
	};
};
