#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class AbstractDomainObject : public amf::Object {
				public:
					AbstractDomainObject(){
						setName("com.riotgames.platform.gameclient.domain.AbstractDomainObject");
						
						set("futureData", (amf::Null*)nullptr);
						set("dataVersion", new amf::Integer(0));
					}

					amf::Variant& futureData(){
						return get("futureData");
					}

					int32 dataVersion(){
						return get("dataVersion");
					}

					void setFutureData(amf::Variant& value){
						get("futureData") = value;
					}

					void setDataVersion(int value){
						get("dataVersion") = value;
					}
				};
			};
		};
	};
};
