#pragma once

#include "amf/variant.h"
#include "SummaryAggStat.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SummaryAggStats : public amf::Object {
				public:
					SummaryAggStats(){
						setName("com.riotgames.platform.statistics.SummaryAggStats");

						set("stats", new amf::Array());
					}

					amf::TypedArray<SummaryAggStat*>* getStats() const {
						return (amf::TypedArray<SummaryAggStat*>*)(amf::Array*)get("stats");
					}

					void setStats(amf::Array* value){
						get("stats") = value;
					}
				};
			};
		};
	};
};
