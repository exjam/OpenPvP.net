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

					amf::Array_t<SummaryAggStat*>* getStats(){
						return (amf::Array_t<SummaryAggStat*>*)get("stats")->toArray();
					}

					void setStats(amf::Array* value){
						set("stats", (Variant*)value);
					}
				};
			};
		};
	};
};
