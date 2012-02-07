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

						set("userId", (amf::Null*)nullptr);
						set("maxRating", 0);
						set("leaves", 0);
						set("modifyDate", (amf::Null*)nullptr);
						set("losses", 0);
						set("rating", 0);
						set("wins", 0);
						set("playerStatSummaryType", (amf::Null*)nullptr);
						set("aggregatedStats", (amf::Null*)nullptr);
					}

					double getUserId() const {
						return get("userId");
					}

					int getMaxRating() const {
						return get("maxRating");
					}

					int getLeaves() const {
						return get("leaves");
					}

					amf::Date* getModifyDate() const {
						return get("modifyDate").toDate();
					}

					int getLosses() const {
						return get("losses");
					}

					int getRating() const {
						return get("rating");
					}

					int getWins() const {
						return get("wins");
					}

					std::string getPlayerStatSummaryType() const {
						return get("playerStatSummaryType");
					}

					const amf::Reference<SummaryAggStats> getAggregatedStats() const {
						return get("aggregatedStats").toObject();
					}

					void setUserId(double value){
						get("userId") = value;
					}

					void setMaxRating(int value){
						get("maxRating") = value;
					}

					void setLeaves(int value){
						get("leaves") = value;
					}

					void setModifyDate(amf::Date* value){
						get("modifyDate") = value;
					}

					void setLosses(int value){
						get("losses") = value;
					}

					void setRating(int value){
						get("rating") = value;
					}

					void setWins(int value){
						get("wins") = value;
					}

					void setPlayerStatSummaryType(const std::string& value){
						get("playerStatSummaryType") = value;
					}

					void setAggregatedStats(SummaryAggStats* value){
						get("aggregatedStats") = value;
					}
				};
			};
		};
	};
};
