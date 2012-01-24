#pragma once

#include "types.h"
#include "bytestream.h"

#include <vector>

namespace flex {
	namespace utils {
		class IExternalizable;
	};
};

namespace amf {
	typedef enum {
		AMF_NULL,
		AMF_NUMBER,
		AMF_INTEGER,
		AMF_BOOLEAN,
		AMF_STRING,
		AMF_DATE,
		AMF_ARRAY,
		AMF_BYTE_ARRAY,
		AMF_OBJECT,
		AMF_UNKNOWN_TYPE,
	} AmfTypes;
	
	class Variant;
	class Null;
	class Date;
	class Array;
	class Object;
	class Number;
	class String;
	class Integer;
	class Boolean;
	class ByteArray;
	class EncoderImpl;
	
	class Encoder_ {
		static const int mMaxVersion = 3;

	public:
		Encoder_();

		void setVersion(uint8 version);
		
		Variant* deserialise(ByteStream& stream, bool cache = true);
		void serialise(Variant* value, ByteStream& stream);

		void start(uint8 version);
		void end();

		void defineObject(Object* object);
		void addExternalizable(flex::utils::IExternalizable* externalizable);

	private:
		uint8 mVersion;
		EncoderImpl* mVersions[mMaxVersion + 1];
		std::vector<amf::Variant*> mCache;
	};

	extern Encoder_ Encoder;

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

	class EncoderImpl {
	public:
		virtual void start() = 0;
		virtual void end() = 0;
		
		virtual void defineObject(Object* object) = 0;
		virtual void addExternalizable(flex::utils::IExternalizable* externalizable) = 0;

		virtual void serialise(uint8 version, Variant* value, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, Null* value, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, Number* value, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, Integer* number, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, Boolean* value, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, String* value, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, Date* value, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, Array* value, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, ByteArray* value, ByteStream& stream) = 0;
		virtual void serialise(uint8 type, Object* value, ByteStream& stream) = 0;
		
		virtual Variant* deserialise(uint8 version, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, Null* value, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, Number* value, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, Integer* number, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, Boolean* value, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, String* value, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, Date* value, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, Array* value, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, ByteArray* value, ByteStream& stream) = 0;
		virtual void deserialise(uint8 type, Object* value, ByteStream& stream) = 0;
	};
};
