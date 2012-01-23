#include "variant.h"
#include "amf.h"

namespace amf {
	var_t var(const std::string& name, object_creator_t value){
		return var_t(name, value.mValue);
	}
	
	Variant* Variant::fromValue(const std::string& value){
		return new amf::String(value);
	}

	Variant* Variant::fromValue(const char* value){
		return new amf::String(value);
	}

	Variant* Variant::fromValue(const uint32& value){
		return new amf::Integer(value);
	}

	Variant* Variant::fromValue(const int32& value){
		return new amf::Integer(value);
	}

	Variant* Variant::fromValue(const bool& value){
		return new amf::Boolean(value);
	}

	Variant* Variant::fromValue(const double& value){
		return new amf::Number(value);
	}

	int32 Variant::toInt() const {
		switch(mType){
			case AMF_NULL:
				return false;
			case AMF_NUMBER:
				return (int32)((Number*)this)->value();
			case AMF_INTEGER:
				return ((Integer*)this)->value();
			case AMF_BOOLEAN:
				return ((Boolean*)this)->value() ? 1 : 0;
			case AMF_STRING:
				return atoi(((String*)this)->value().c_str());
			case AMF_DATE:
				return (int32)((Date*)this)->value();
			default:
				return 0;
		};
	}

	bool Variant::toBool() const {
		switch(mType){
			case AMF_NULL:
				return false;
			case AMF_NUMBER:
				return ((Number*)this)->value() > 0.0;
			case AMF_INTEGER:
				return ((Integer*)this)->value() > 0;
			case AMF_BOOLEAN:
				return ((Boolean*)this)->value();
			case AMF_STRING:
				return ((String*)this)->value().compare("true") == 0;
			default:
				throw std::bad_cast();
		};
	}

	uint32 Variant::toUInt() const {
		return toInt();
	}

	Date* Variant::toDate() const {
		if(mType == AMF_NULL)
			return nullptr;
		else if(mType != AMF_DATE)
			throw std::bad_cast();

		return (Date*)this;
	}

	double Variant::toDouble() const {
		switch(mType){
			case AMF_NULL:
				return 0.0;
			case AMF_NUMBER:
				return ((Number*)this)->value();
			case AMF_INTEGER:
				return ((Integer*)this)->value();
			case AMF_STRING:
				return atof(((String*)this)->value().c_str());
			case AMF_DATE:
				return ((Date*)this)->value();
			default:
				throw std::bad_cast();
		};
	}

	Array* Variant::toArray() const {
		if(mType == AMF_NULL)
			return nullptr;
		else if(mType != AMF_ARRAY)
			throw std::bad_cast();

		return (Array*)this;
	}

	ByteArray* Variant::toByteArray() const {
		if(mType == AMF_NULL)
			return nullptr;
		else if(mType != AMF_BYTE_ARRAY)
			throw std::bad_cast();

		return (ByteArray*)this;
	}

	Object* Variant::toObject() const {
		if(mType == AMF_NULL)
			return nullptr;
		else if(mType != AMF_OBJECT)
			throw std::bad_cast();

		return (Object*)this;
	}

	std::string Variant::toString() const {
		char buffer[32];
		switch(mType){
			case AMF_NULL:
				return "";
			case AMF_NUMBER:
				sprintf_s(buffer, 32, "%Lf", ((Number*)this)->value());
				return buffer;
			case AMF_INTEGER:
				sprintf_s(buffer, 32, "%d", ((Integer*)this)->value());
				return buffer;
			case AMF_BOOLEAN:
				return ((Boolean*)this)->value() ? "true" : "false";
			case AMF_STRING:
				return ((String*)this)->value();
			case AMF_DATE:
				sprintf_s(buffer, 32, "%Lf", ((Date*)this)->value());
				return buffer;
			default:
				throw std::bad_cast();
		};
	}
		
	void Object::defineObject(){
		Encoder.defineObject(this);
	}
};
