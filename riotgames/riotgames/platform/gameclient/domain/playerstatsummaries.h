#pragma once

#include "amf/variant.h"
#include "playerstatsummary.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {

				class PlayerStatSummaries : public amf::Object {
				public:
					PlayerStatSummaries(){
						setName("com.riotgames.platform.statistics.PlayerStatSummaries");

						set("playerStatSummarySet", new amf::Array());
						set("userId", (amf::Null*)nullptr);
					}

					amf::TypedArray<PlayerStatSummary*>* getPlayerStatSummarySet() const {
						return (amf::TypedArray<PlayerStatSummary*>*)(amf::Array*)get("playerStatSummarySet");
					}

					double getUserId() const {
						return get("userId");
					}

					void setPlayerStatSummarySet(amf::Array* value){
						get("playerStatSummarySet") = value;
					}

					void setUserId(double value){
						get("userId") = value;
					}
				};
			};
		};
	};
};
