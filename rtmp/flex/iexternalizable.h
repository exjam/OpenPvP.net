#pragma once

#include "amf/amf.h"
#include "amf/variant.h"
#include "bytestream.h"

namespace flex {
	namespace utils {
		class IExternalizable {
		public:
			IExternalizable(){}
			virtual ~IExternalizable(){}

			virtual std::string name() const = 0;
			virtual void readExternal(amf::Object* object, ByteStream& stream) = 0;
			virtual void writeExternal(amf::Object* object, ByteStream& stream) = 0;
		};
	};
};
