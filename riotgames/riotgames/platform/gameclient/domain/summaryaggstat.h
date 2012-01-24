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

						set("statType", new amf::Null());
						set("value", new amf::Null());
					}

					std::string getStatType(){
						return get("statType")->toString();
					}

					double getValue(){
						return get("value")->toDouble();
					}

					void setStatType(const std::string& value){
						set("statType", amf::object_creator_t(value).mValue);
					}

					void setValue(double value){
						set("value", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
