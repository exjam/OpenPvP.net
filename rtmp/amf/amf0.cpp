#include "amf.h"
#include "amf0.h"
#include "variant.h"

#include <assert.h>

namespace amf {
	amf0::amf0(){
	}

	void amf0::start(){
	}

	void amf0::end(){
	}

	void amf0::defineObject(Object* object){
	}

	void amf0::addExternalizable(flex::utils::IExternalizable* externalizable){
	}
	
	void amf0::serialise(uint8 type, ByteArray* value, ByteStream& stream){
	}
	
	void amf0::deserialise(uint8 type, ByteArray* value, ByteStream& stream){
	}

	void amf0::serialise(uint8 version, Variant* value, ByteStream& stream){
		assert(version == 0);
			
		uint8 type = value ? value->type() : AMF_NULL;
		switch(type){
			case AMF_NULL:
				serialise(AMF0_INVALID, (Null*)value, stream);
				break;
			case AMF_NUMBER:
				serialise(AMF0_INVALID, (Number*)value, stream);
				break;
			case AMF_INTEGER:
				serialise(AMF0_INVALID, (Integer*)value, stream);
				break;
			case AMF_BOOLEAN:
				serialise(AMF0_INVALID, (Boolean*)value, stream);
				break;
			case AMF_STRING:
				serialise(AMF0_INVALID, (String*)value, stream);
				break;
			case AMF_DATE:
				serialise(AMF0_INVALID, (Date*)value, stream);
				break;
			case AMF_ARRAY:
				serialise(AMF0_INVALID, (Array*)value, stream);
				break;
			case AMF_OBJECT:
				serialise(AMF0_INVALID, (Object*)value, stream);
				break;
			default:
				throw new EncodeException("Invalid AMF0 data type %u", type);
				break;
		}
	}
		
	void amf0::serialise(uint8 type, Null* value, ByteStream& stream){
		assert(type == AMF0_INVALID);

		stream << uint8(AMF0_NULL);
	}

	void amf0::serialise(uint8 type, Number* value, ByteStream& stream){
		assert(type == AMF0_INVALID || type == AMF0_NUMBER);

		if(type == AMF0_INVALID)
			stream << uint8(AMF0_NUMBER);

		stream << double(value->value());
	}

	void amf0::serialise(uint8 type, Integer* value, ByteStream& stream){
		assert(type == AMF0_INVALID || type == AMF0_NUMBER);
			
		if(type == AMF0_INVALID)
			stream << uint8(AMF0_NUMBER);

		stream << double(value->value());
	}

	void amf0::serialise(uint8 type, Boolean* value, ByteStream& stream){
		assert(type == AMF0_INVALID || type == AMF0_BOOLEAN);
			
		if(type == AMF0_INVALID)
			stream << uint8(AMF0_BOOLEAN);

		stream << uint8(value->value() ? 1 : 0);
	}

	void amf0::serialise(uint8 type, String* value, ByteStream& stream){
		assert(type == AMF0_INVALID || type == AMF0_STRING);
			
		if(type == AMF0_INVALID)
			stream << uint8(AMF0_STRING);

		const std::string& str = value->value();
		stream << uint16(str.length());
		stream.write(str.c_str(), str.length());
	}

	void amf0::serialise(uint8 type, Date* value, ByteStream& stream){
		assert(type == AMF0_INVALID || type == AMF0_DATE);
			
		if(type == AMF0_DATE)
			stream << uint8(AMF0_DATE);

		stream << double(value->value());
		stream << uint16(0);
	}

	void amf0::serialise(uint8 type, Array* value, ByteStream& stream){
		assert(type == AMF0_INVALID || type == AMF0_ECMA_ARRAY || type == AMF0_STRICT_ARRAY);

		if(value->hasAssociative() && value->hasDense())
			throw new EncodeException("AMF0 arrays cannot have both associative and dense values");

		if(value->hasAssociative()){
			assert(type == AMF0_INVALID || type == AMF0_ECMA_ARRAY);

			if(type == AMF0_INVALID)
				stream << uint8(AMF0_ECMA_ARRAY);

			stream << uint32(value->keys());

			for(auto itr = value->begin(); itr != value->end(); ++itr){
				serialise(AMF0_STRING, &String(itr->first), stream);
				Encoder.serialise(itr->second, stream);
			}
		}else if(value->hasDense()){
			assert(type == AMF0_INVALID || type == AMF0_STRICT_ARRAY);
				
			if(type == AMF0_INVALID)
				stream << uint8(AMF0_STRICT_ARRAY);

			stream << uint32(value->size());

			for(size_t i = 0; i < value->size(); ++i)
				Encoder.serialise(value->at(i), stream);
		}
	}

	void amf0::serialise(uint8 type, Object* value, ByteStream& stream){
		assert(type == AMF0_INVALID || type == AMF0_OBJECT || type == AMF0_TYPED_OBJECT);

		if(value->name().length()){
			assert(type == AMF0_INVALID || type == AMF0_TYPED_OBJECT);

			if(type == AMF0_INVALID)
				stream << uint8(AMF0_TYPED_OBJECT);

			serialise(AMF0_STRING, &String(value->name()), stream);
		}else{
			assert(type == AMF0_INVALID || type == AMF0_OBJECT);

			if(type == AMF0_INVALID)
				stream << uint8(AMF0_OBJECT);
		}

		for(auto itr = value->begin(); itr != value->end(); ++itr){
			serialise(AMF0_STRING, &String(itr->first), stream);
			Encoder.serialise(itr->second, stream);
		}

		stream << uint16(0);
		stream << uint8(AMF0_OBJECT_END);
	}

	Variant* amf0::deserialise(uint8 version, ByteStream& stream){
		assert(version == 0);

		uint8 type;
		stream >> type;

		Variant* value = nullptr;

		switch(type){
			case AMF0_NUMBER:
				value = new Number();
				deserialise(type, (Number*)value, stream);
				break;
			case AMF0_BOOLEAN:
				value = new Boolean();
				deserialise(type, (Boolean*)value, stream);
				break;
			case AMF0_DATE:
				value = new Date();
				deserialise(type, (Date*)value, stream);
				break;
			case AMF0_TYPED_OBJECT:
			case AMF0_OBJECT:
				value = new Object();
				deserialise(type, (Object*)value, stream);
				break;
			case AMF0_ECMA_ARRAY:
			case AMF0_STRICT_ARRAY:
				value = new Array();
				deserialise(type, (Array*)value, stream);
				break;
			case AMF0_STRING:
			case AMF0_LONG_STRING:
			case AMF0_XML_DOC:
				value = new String();
				deserialise(type, (String*)value, stream);
				break;
			case AMF0_OBJECT_END:
				break;
			case AMF0_NULL:
			case AMF0_UNDEFINED:
				value = new Null();
				deserialise(type, (Null*)value, stream);
				break;
			case AMF0_AVMPLUS:
				Encoder.setVersion(3);
				return Encoder.deserialise(stream);
			/*
			case AMF0_REFERENCE:
				break;
			*/
			case AMF0_RECORDSET:
				throw new DecodeException("AMF0_RECORDSET not supported");
				break;
			case AMF0_MOVIECLIP:
				throw new DecodeException("AMF0_MOVIECLIP not supported");
				break;
			default:
				throw new DecodeException("Unsupported AMF0 type %u", type);
				break;
		};

		return value;
	}

	void amf0::deserialise(uint8 type, Null* value, ByteStream& stream){
		assert(type == AMF0_NULL || type == AMF0_UNDEFINED);
	}

	void amf0::deserialise(uint8 type, Number* value, ByteStream& stream){			
		assert(type == AMF0_NUMBER);

		stream >> value->value();
	}

	void amf0::deserialise(uint8 type, Integer* number, ByteStream& stream){
		__debugbreak();
	}

	void amf0::deserialise(uint8 type, Boolean* value, ByteStream& stream){
		assert(type == AMF0_BOOLEAN);

		uint8 charValue;
		stream >> charValue;
		value->value() = charValue > 0;
	}

	void amf0::deserialise(uint8 type, String* value, ByteStream& stream){
		assert(type == AMF0_STRING || type == AMF0_LONG_STRING || type == AMF0_XML_DOC);

		uint32 size;
		if(type == AMF0_STRING){
			uint16 size16;
			stream >> size16;
			size = size16;
		}else if(type == AMF0_LONG_STRING || type == AMF0_XML_DOC){
			stream >> size;
		}

		value->value().assign((char*)stream.data() + stream.tell(), size);
		stream.skip(size);
	}

	void amf0::deserialise(uint8 type, Date* value, ByteStream& stream){
		assert(type == AMF0_DATE);

		stream >> value->value();
		stream >> value->timezone();
	}

	void amf0::deserialise(uint8 type, Array* value, ByteStream& stream){
		assert(type == AMF0_STRICT_ARRAY || type == AMF0_ECMA_ARRAY);

		uint32 size;
		stream >> size;

		if(type == AMF0_STRICT_ARRAY){
			for(uint32 i = 0; i < size; ++i)
				value->push_back(Encoder.deserialise(stream));
		}else if(type == AMF0_ECMA_ARRAY){
			for(uint32 i = 0; i < size; ++i){
				String key;
				deserialise(AMF0_STRING, &key, stream);
				value->insert(key, Encoder.deserialise(stream));
			}
		}
	}

	void amf0::deserialise(uint8 type, Object* value, ByteStream& stream){
		assert(type == AMF0_OBJECT || type == AMF0_TYPED_OBJECT);

		if(type == AMF0_TYPED_OBJECT){
			String name;
			deserialise(AMF0_STRING, &name, stream);
			value->setName(name);
		}

		while(true){
			String key;
			deserialise(AMF0_STRING, &key, stream);

			Variant* data = Encoder.deserialise(stream);
			if(!data)
				break;

			value->insert(key, data);
		}
	}
};