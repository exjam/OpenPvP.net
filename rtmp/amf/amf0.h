#pragma once

#include "amf.h"

namespace amf0 {
	using namespace amf;

	typedef enum {
		AMF0_NUMBER = 0,
		AMF0_BOOLEAN,
		AMF0_STRING,
		AMF0_OBJECT,
		AMF0_MOVIECLIP,
		AMF0_NULL,
		AMF0_UNDEFINED,
		AMF0_REFERENCE,
		AMF0_ECMA_ARRAY,
		AMF0_OBJECT_END,
		AMF0_STRICT_ARRAY,
		AMF0_DATE,
		AMF0_LONG_STRING,
		AMF0_UNSUPPORTED,
		AMF0_RECORDSET,
		AMF0_XML_DOC,
		AMF0_TYPED_OBJECT,
		AMF0_AVMPLUS,
		AMF0_INVALID = 0xFF
	} DataTypes;
		
	void serialise(uint8 version, Variant* value, ByteStream& stream);
	void serialise(uint8 type, Null* value, ByteStream& stream);
	void serialise(uint8 type, Number* value, ByteStream& stream);
	void serialise(uint8 type, Integer* number, ByteStream& stream);
	void serialise(uint8 type, Boolean* value, ByteStream& stream);
	void serialise(uint8 type, String* value, ByteStream& stream);
	void serialise(uint8 type, Date* value, ByteStream& stream);
	void serialise(uint8 type, Array* value, ByteStream& stream);
	void serialise(uint8 type, ByteArray* value, ByteStream& stream);
	void serialise(uint8 type, Object* value, ByteStream& stream);
		
	Variant* deserialise(uint8 version, ByteStream& stream);
	void deserialise(uint8 type, Null* value, ByteStream& stream);
	void deserialise(uint8 type, Number* value, ByteStream& stream);
	void deserialise(uint8 type, Integer* number, ByteStream& stream);
	void deserialise(uint8 type, Boolean* value, ByteStream& stream);
	void deserialise(uint8 type, String* value, ByteStream& stream);
	void deserialise(uint8 type, Date* value, ByteStream& stream);
	void deserialise(uint8 type, Array* value, ByteStream& stream);
	void deserialise(uint8 type, ByteArray* value, ByteStream& stream);
	void deserialise(uint8 type, Object* value, ByteStream& stream);
};
