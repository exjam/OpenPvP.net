#pragma once

#include "types.h"
#include "variant.h"
#include "bytestream.h"

#include <vector>

namespace flex {
	namespace utils {
		class IExternalizable;
	};
};

namespace amf {	
	class amf0;
	class amf3;
	
	class Encoder {
		static const int mMaxVersion = 3;

	public:
		Encoder(uint8 version);
		~Encoder();

		void setVersion(uint8 version);
		Variant deserialise(ByteStream& stream, bool cache = true);
		void serialise(const Variant& value, ByteStream& stream);

		static void defineObject(Object* object);
		static void addExternalizable(flex::utils::IExternalizable* externalizable);

	private:
		uint8 mVersion;
		amf0* mAmf0;
		amf3* mAmf3;
	};

	class DecodeException : public std::exception {
	public:
		DecodeException(char* format, ...);
		DecodeException(const std::string& what);

		virtual const char* what() const throw();

	private:
		std::string mWhat;
	};

	class EncodeException : public std::exception {
	public:
		EncodeException(char* format, ...);
		EncodeException(const std::string& what);

		virtual const char* what() const throw();
		
	private:
		std::string mWhat;
	};
};
