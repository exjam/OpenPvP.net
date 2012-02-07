#pragma once

#include "amf/variant.h"
#include "flex/iexternalizable.h"
#include <iostream>

/*
object com.riotgames.platform.broadcast.BroadcastNotification
json = "{"broadcastMessages":[{"id":0,"active":true,"content":"Leona has been re-enabled. If you are unable to select her please re-log.","messageKey":"generic","severity":"info"}]}"
}
*/

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace broadcast {
					class BroadcastNotification : public amf::Object {
					public:
					};

					class BroadcastNotificationExt : public flex::utils::IExternalizable {
					public:
						BroadcastNotificationExt(){
							amf::Encoder::addExternalizable(this);
						}

						std::string name() const {
							return "com.riotgames.platform.broadcast.BroadcastNotification";
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
