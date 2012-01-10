#pragma once

#include "amf/amf.h"
#include <string>
#include <functional>

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace services {
				class Service {
				public:
					void invoke(const std::string& service, const std::string& function, amf::Object* arguments, std::function<void(amf::Container*)>& onSuccess){
					}

				private:
				};
			};
		};
	};
};