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

						set("gameCode", new amf::Null());
						set("prereqTalentGameCode", new amf::Null());
						set("talentGroupId", new amf::Null());
						set("name", new amf::Null());
						set("level4Desc", new amf::Null());
						set("minLevel", new amf::Null());
						set("maxRank", new amf::Null());
						set("tltId", new amf::Null());
						set("index", new amf::Null());
						set("talentRowId", new amf::Null());
						set("level2Desc", new amf::Null());
						set("minTier", new amf::Null());
						set("level3Desc", new amf::Null());
						set("level5Desc", new amf::Null());
						set("level1Desc", new amf::Null());
					}

					int getGameCode(){
						return get("gameCode")->toInt();
					}

					int getPrereqTalentGameCode(){
						return get("prereqTalentGameCode")->toInt();
					}

					int getTalentGroupId(){
						return get("talentGroupId")->toInt();
					}

					std::string getName(){
						return get("name")->toString();
					}

					int getLevel4Desc(){
						return get("level4Desc")->toInt();
					}

					int getMinLevel(){
						return get("minLevel")->toInt();
					}

					int getMaxRank(){
						return get("maxRank")->toInt();
					}

					int getTltId(){
						return get("tltId")->toInt();
					}

					int getIndex(){
						return get("index")->toInt();
					}

					int getTalentRowId(){
						return get("talentRowId")->toInt();
					}

					int getLevel2Desc(){
						return get("level2Desc")->toInt();
					}

					int getMinTier(){
						return get("minTier")->toInt();
					}

					int getLevel3Desc(){
						return get("level3Desc")->toInt();
					}

					int getLevel5Desc(){
						return get("level5Desc")->toInt();
					}

					int getLevel1Desc(){
						return get("level1Desc")->toInt();
					}

					void setGameCode(int value){
						set("gameCode", amf::object_creator_t(value).mValue);
					}

					void setPrereqTalentGameCode(int value){
						set("prereqTalentGameCode", amf::object_creator_t(value).mValue);
					}

					void setTalentGroupId(int value){
						set("talentGroupId", amf::object_creator_t(value).mValue);
					}

					void setName(const std::string& value){
						set("name", amf::object_creator_t(value).mValue);
					}

					void setLevel4Desc(int value){
						set("level4Desc", amf::object_creator_t(value).mValue);
					}

					void setMinLevel(int value){
						set("minLevel", amf::object_creator_t(value).mValue);
					}

					void setMaxRank(int value){
						set("maxRank", amf::object_creator_t(value).mValue);
					}

					void setTltId(int value){
						set("tltId", amf::object_creator_t(value).mValue);
					}

					void setIndex(int value){
						set("index", amf::object_creator_t(value).mValue);
					}

					void setTalentRowId(int value){
						set("talentRowId", amf::object_creator_t(value).mValue);
					}

					void setLevel2Desc(int value){
						set("level2Desc", amf::object_creator_t(value).mValue);
					}

					void setMinTier(int value){
						set("minTier", amf::object_creator_t(value).mValue);
					}

					void setLevel3Desc(int value){
						set("level3Desc", amf::object_creator_t(value).mValue);
					}

					void setLevel5Desc(int value){
						set("level5Desc", amf::object_creator_t(value).mValue);
					}

					void setLevel1Desc(int value){
						set("level1Desc", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
