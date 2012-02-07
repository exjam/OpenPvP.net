#include "variant.h"
#include "amf.h"

namespace amf {
	void Object::defineObject(){
		Encoder::defineObject(this);
	}

	var_t var(const std::string& name, const Variant& value){
		return var_t(name, value);
	}

	Variant& operator<<(Variant& lhs, const var_t& var){
		if(lhs.type() == Array::Type)
			*lhs.toArray() << var;
		else if(lhs.type() == Object::Type)
			*lhs.toObject() << var;

		return lhs;
	}
	
	Variant::Variant(){
	}

	Variant::Variant(BaseAmf* obj)
		: Reference(obj)
	{
	}

	Variant::Variant(const Variant& other)
		: Reference(other.mObject)
	{
	}

	Variant::Variant(const char* value){
		fromString(value);
	}

	Variant::Variant(const bool& value){
		fromBool(value);
	}

	Variant::Variant(const int32& value){
		fromInt(value);
	}

	Variant::Variant(const uint32& value){
		fromUInt(value);
	}

	Variant::Variant(const double& value){
		fromDouble(value);
	}

	Variant::Variant(const std::string& value){
		fromString(value);
	}

	Variant::~Variant(){
	}

	int Variant::type() const {
		if(!mObject)
			return AMF_UNKNOWN_TYPE;

		return mObject->type();
	}

	bool Variant::operator !() const {
		return mObject == 0;
	}

	Variant::operator Null*() const {
		if(!mObject)
			return nullptr;
		else if(mObject->type() != AMF_NULL)
			throw std::bad_cast();

		return (Null*)mObject;
	}

	Variant::operator Date*() const {
		return toDate();
	}

	Variant::operator Array*() const {
		return toArray();
	}

	Variant::operator Object*() const {
		return toObject();
	}

	Variant::operator ByteArray*() const {
		return toByteArray();
	}

	Variant::operator Number*() const {
		if(!mObject || mObject->type() == AMF_NULL)
			return nullptr;
		else if(mObject->type() != AMF_NUMBER)
			throw std::bad_cast();

		return (Number*)mObject;
	}

	Variant::operator String*() const {
		if(!mObject || mObject->type() == AMF_NULL)
			return nullptr;
		else if(mObject->type() != AMF_STRING)
			throw std::bad_cast();

		return (String*)mObject;
	}

	Variant::operator Integer*() const {
		if(!mObject || mObject->type() == AMF_NULL)
			return nullptr;
		else if(mObject->type() != AMF_INTEGER)
			throw std::bad_cast();

		return (Integer*)mObject;
	}

	Variant::operator Boolean*() const {
		if(!mObject || mObject->type() == AMF_NULL)
			return nullptr;
		else if(mObject->type() != AMF_BOOLEAN)
			throw std::bad_cast();

		return (Boolean*)mObject;
	}


	Variant::operator bool() const {
		return toBool();
	}

	Variant::operator int32() const {
		return toInt();
	}

	Variant::operator uint32() const {
		return toUInt();
	}

	Variant::operator double() const {
		return toDouble();
	}

	Variant::operator std::string() const {
		return toString();
	}

	int32 Variant::toInt() const {
		if(!mObject)
			return 0;

		switch(mObject->type()){
			case AMF_NULL:
				return false;
			case AMF_NUMBER:
				return (int32)((Number*)mObject)->value();
			case AMF_INTEGER:
				return ((Integer*)mObject)->value();
			case AMF_BOOLEAN:
				return ((Boolean*)mObject)->value() ? 1 : 0;
			case AMF_STRING:
				return atoi(((String*)mObject)->value().c_str());
			case AMF_DATE:
				return (int32)((Date*)mObject)->value();
			default:
				throw std::bad_cast();
		};
	}

	bool Variant::toBool() const {
		if(!mObject)
			return false;

		switch(mObject->type()){
			case AMF_NULL:
				return false;
			case AMF_NUMBER:
				return ((Number*)mObject)->value() > 0.0;
			case AMF_INTEGER:
				return ((Integer*)mObject)->value() > 0;
			case AMF_BOOLEAN:
				return ((Boolean*)mObject)->value();
			case AMF_STRING:
				return ((String*)mObject)->value().compare("true") == 0;
			default:
				throw std::bad_cast();
		};
	}

	uint32 Variant::toUInt() const {
		return toInt();
	}

	Reference<Date> Variant::toDate() const {
		if(!mObject || mObject->type() == AMF_NULL)
			return nullptr;
		else if(mObject->type() != AMF_DATE)
			throw std::bad_cast();

		return (Date*)mObject;
	}

	double Variant::toDouble() const {
		if(!mObject)
			return 0.0;

		switch(mObject->type()){
			case AMF_NULL:
				return 0.0;
			case AMF_NUMBER:
				return ((Number*)mObject)->value();
			case AMF_INTEGER:
				return ((Integer*)mObject)->value();
			case AMF_STRING:
				return atof(((String*)mObject)->value().c_str());
			case AMF_DATE:
				return ((Date*)mObject)->value();
			default:
				throw std::bad_cast();
		};
	}

	Reference<Array> Variant::toArray() const {
		if(!mObject || mObject->type() == AMF_NULL){
			return nullptr;
		}else if(mObject->type() == AMF_OBJECT){
			Object* obj = (Object*)mObject;
			if(obj->name().compare("flex.messaging.io.ArrayCollection") == 0)
				return obj->get("source").toArray();
		}
		
		if(mObject->type() != AMF_ARRAY)
			throw std::bad_cast();

		return (Array*)mObject;
	}

	Reference<ByteArray> Variant::toByteArray() const {
		if(!mObject || mObject->type() == AMF_NULL)
			return nullptr;
		else if(mObject->type() != AMF_BYTE_ARRAY)
			throw std::bad_cast();

		return (ByteArray*)mObject;
	}

	Reference<Object> Variant::toObject() const {
		if(!mObject || mObject->type() == AMF_NULL)
			return nullptr;
		else if(mObject->type() != AMF_OBJECT)
			throw std::bad_cast();

		return (Object*)mObject;
	}

	std::string Variant::toString() const {
		if(!mObject)
			return "";
		
		char buffer[32];
		switch(mObject->type()){
			case AMF_NULL:
				return "";
			case AMF_NUMBER:
				sprintf_s(buffer, 32, "%Lf", ((Number*)mObject)->value());
				return buffer;
			case AMF_INTEGER:
				sprintf_s(buffer, 32, "%d", ((Integer*)mObject)->value());
				return buffer;
			case AMF_BOOLEAN:
				return ((Boolean*)mObject)->value() ? "true" : "false";
			case AMF_STRING:
				return ((String*)mObject)->value();
			case AMF_DATE:
				sprintf_s(buffer, 32, "%Lf", ((Date*)mObject)->value());
				return buffer;
			default:
				throw std::bad_cast();
		};
	}

	Variant& Variant::operator =(BaseAmf* v){
		Reference<BaseAmf>::operator=(v);
		return *this;
	}

	Variant& Variant::operator =(const Variant& v){
		Reference<BaseAmf>::operator=((const Reference<BaseAmf>&)v);
		return *this;
	}
	
	Variant& Variant::operator =(const bool& v){
		if(!mObject || mObject->type() != Boolean::Type)
			(*this) = new Boolean(v);
		else
			((Boolean*)mObject)->setValue(v);

		return *this;
	}

	Variant& Variant::operator =(const int32& v){
		if(!mObject || mObject->type() != Integer::Type)
			(*this) = new Integer(v);

		((Integer*)mObject)->setValue(v);
		return *this;
	}

	Variant& Variant::operator =(const uint32& v){
		if(!mObject || mObject->type() != Integer::Type)
			(*this) = new Integer(v);
		else
			((Integer*)mObject)->setValue(v);

		return *this;
	}

	Variant& Variant::operator =(const double& v){
		if(!mObject || mObject->type() != Number::Type)
			(*this) = new Number(v);
		else
			((Number*)mObject)->setValue(v);

		return *this;
	}

	Variant& Variant::operator =(const std::string& v){
		if(!mObject || mObject->type() != String::Type)
			(*this) = new String(v);
		else
			((String*)mObject)->setValue(v);

		return *this;
	}
	void Variant::fromBool(const bool& value){
		(*this) = value;
	}

	void Variant::fromInt(const int32& value){
		(*this) = value;
	}

	void Variant::fromUInt(const uint32& value){
		(*this) = value;
	}

	void Variant::fromDouble(const double& value){
		(*this) = value;
	}

	void Variant::fromString(const std::string& value){
		(*this) = value;
	}
};
