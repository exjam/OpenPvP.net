#pragma once

#include "amf/variant.h"
#include "flex/iexternalizable.h"
#include <iostream>

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace systemstates {
					class ClientSystemStatesNotification : public amf::Object {
					public:
					};

					class ClientSystemStatesNotificationExt : public flex::utils::IExternalizable {
					public:
						ClientSystemStatesNotificationExt(){
							amf::Encoder.addExternalizable(this);
						}

						std::string name() const {
							return "com.riotgames.platform.systemstate.ClientSystemStatesNotification";
						}

						void readExternal(amf::Object* object, ByteStream& stream){
							uint16 length;
							stream >> length;

							char* json = new char[length];
							stream.read(json, length);
							std::cout << "ClientSystemStatesNotificationExt json:" << std::endl << json << std::endl;
							delete [] json;
						}

						void writeExternal(amf::Object* object, ByteStream& stream){
						}
					};
				};
			};
		};
	};
};
