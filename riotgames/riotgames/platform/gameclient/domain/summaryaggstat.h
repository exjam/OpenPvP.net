#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class SummaryAggStat : public amf::Object {
				public:
					SummaryAggStat(){
						setName("com.riotgames.platform.statistics.SummaryAggStat");

						set("statType", (amf::Null*)nullptr);
						set("value", (amf::Null*)nullptr);
					}

					std::string getStatType() const {
						return get("statType");
					}

					double getValue() const {
						return get("value");
					}

					void setStatType(const std::string& value){
						get("statType") = value;
					}

					void setValue(double value){
						get("value") = value;
					}
				};
			};
		};
	};
};
