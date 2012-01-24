#pragma once

#include "amf/variant.h"
#include "summaryaggstats.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class PlayerStatSummary : public amf::Object {
				public:
					PlayerStatSummary(){
						setName("com.riotgames.platform.statistics.PlayerStatSummary");

						set("userId", new amf::Null());
						set("maxRating", amf::object_creator_t(0).mValue);
						set("leaves", amf::object_creator_t(0).mValue);
						set("modifyDate", new amf::Null());
						set("losses", amf::object_creator_t(0).mValue);
						set("rating", amf::object_creator_t(0).mValue);
						set("wins", amf::object_creator_t(0).mValue);
						set("playerStatSummaryType", new amf::Null());
						set("aggregatedStats", new amf::Null());
					}

					double getUserId(){
						return get("userId")->toDouble();
					}

					int getMaxRating(){
						return get("maxRating")->toInt();
					}

					int getLeaves(){
						return get("leaves")->toInt();
					}

					amf::Date* getModifyDate(){
						return get("modifyDate")->toDate();
					}

					int getLosses(){
						return get("losses")->toInt();
					}

					int getRating(){
						return get("rating")->toInt();
					}

					int getWins(){
						return get("wins")->toInt();
					}

					std::string getPlayerStatSummaryType(){
						return get("playerStatSummaryType")->toString();
					}

					SummaryAggStats* getAggregatedStats(){
						return (SummaryAggStats*)get("aggregatedStats")->toObject();
					}

					void setUserId(double value){
						set("userId", amf::object_creator_t(value).mValue);
					}

					void setMaxRating(int value){
						set("maxRating", amf::object_creator_t(value).mValue);
					}

					void setLeaves(int value){
						set("leaves", amf::object_creator_t(value).mValue);
					}

					void setModifyDate(amf::Date* value){
						set("modifyDate", (Variant*)value);
					}

					void setLosses(int value){
						set("losses", amf::object_creator_t(value).mValue);
					}

					void setRating(int value){
						set("rating", amf::object_creator_t(value).mValue);
					}

					void setWins(int value){
						set("wins", amf::object_creator_t(value).mValue);
					}

					void setPlayerStatSummaryType(const std::string& value){
						set("playerStatSummaryType", amf::object_creator_t(value).mValue);
					}

					void setAggregatedStats(SummaryAggStats* value){
						set("aggregatedStats", (Variant*)value);
					}
				};
			};
		};
	};
};
