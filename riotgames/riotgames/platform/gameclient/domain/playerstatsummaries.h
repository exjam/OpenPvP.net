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
						set("userId", new amf::Null());
					}

					amf::Array_t<PlayerStatSummary*>* getPlayerStatSummarySet(){
						return (amf::Array_t<PlayerStatSummary*>*)get("playerStatSummarySet")->toArray();
					}

					double getUserId(){
						return get("userId")->toDouble();
					}

					void setPlayerStatSummarySet(amf::Array* value){
						set("playerStatSummarySet", (Variant*)value);
					}

					void setUserId(double value){
						set("userId", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
