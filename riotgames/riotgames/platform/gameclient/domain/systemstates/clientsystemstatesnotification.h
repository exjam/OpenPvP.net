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
							amf::Encoder::addExternalizable(this);
						}

						std::string name() const {
							return "com.riotgames.platform.systemstate.ClientSystemStatesNotification";
						}

						void readExternal(amf::Encoder* encoder, amf::Object* object, ByteStream& stream){
							uint16 length;
							stream >> length;

							char* json = new char[length + 1];
							stream.read(json, length);
							json[length] = 0;
							object->set("json", json);
							delete [] json;
						}

						void writeExternal(amf::Encoder* encoder, amf::Object* object, ByteStream& stream){
						}
					};
				};
			};
		};
	};
};
