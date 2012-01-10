#include "amf.h"
#include "amf0.h"
#include "amf3.h"

#include <stdarg.h>
#include <assert.h>

namespace amf {
	log::indent_t amf::log::indent(1);
	log::indent_t amf::log::outdent(-1);
	int log::obj::mIndent = 0;
	bool log::obj::mLineStart = true;

	uint8 mCurrentVersion;

	void setVersion(uint8 version){
		mCurrentVersion = version;
	}

	Variant* deserialise(ByteStream& stream){
		assert(stream.tell() < stream.size());

		if(mCurrentVersion == 0)
			return amf0::deserialise(mCurrentVersion, stream);
		else if(mCurrentVersion == 3)
			return amf3::deserialise(mCurrentVersion, stream);

		throw new DecodeException("Invalid AMF version %d", mCurrentVersion);
	}

	void serialise(Variant* value, ByteStream& stream){
		if(mCurrentVersion == 0)
			return amf0::serialise(mCurrentVersion, value, stream);
		else if(mCurrentVersion == 3)
			return amf3::serialise(mCurrentVersion, value, stream);

		throw new DecodeException("Invalid AMF version %d", mCurrentVersion);
	}

	void deserialise(Container* container, ByteStream& stream){
		setVersion(0);
		amf3::ReferenceTable::startGroup();

		while(!stream.eof())
			container->push_back(amf::deserialise(stream));
	}

	void serialise(Container* container, ByteStream& stream){
		setVersion(0);

		for(size_t i = 0; i < container->size(); ++i)
			amf::serialise(container->at(i), stream);
	}

	int32 Variant::toInt() const {
		switch(mType){
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

	double Variant::toDate() const {
		return toDouble();
	}

	double Variant::toDouble() const {
		switch(mType){
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
		if(mType != AMF_ARRAY)
			throw std::bad_cast();

		return (Array*)this;
	}

	ByteArray* Variant::toByteArray() const {
		if(mType != AMF_BYTE_ARRAY)
			throw std::bad_cast();

		return (ByteArray*)this;
	}

	Object* Variant::toObject() const {
		if(mType != AMF_OBJECT)
			throw std::bad_cast();

		return (Object*)this;
	}

	std::string Variant::toString() const {
		char buffer[32];
		switch(mType){
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

	void object_begin(Container* c){
		(*c) << object_begin_t();
	}

	void object_end(Container* c){
		(*c) << object_end_t();
	}

	object_begin_t object_begin(const std::string& name){
		return object_begin_t(name);
	}
	
	object_creator_t::object_creator_t(bool value){
		mValue = new Boolean(value);
	}

	object_creator_t::object_creator_t(int32 value){
		mValue = new Integer(value);
	}

	object_creator_t::object_creator_t(uint32 value){
		mValue = new Integer(value);
	}

	object_creator_t::object_creator_t(double value){
		mValue = new Number(value);
	}

	object_creator_t::object_creator_t(const std::string& value){
		mValue = new String(value);
	}

	var_t var(const std::string& name, object_creator_t value){
		return var_t(name, value.mValue);
	}

	var_t var(const std::string& name, Variant* value){
		if(value == nullptr)
			return var_t(name, new Null());

		return var_t(name, value);
	}

	size_t Container::size() const {
		return mChildren.size();
	}

	Variant* Container::at(size_t index) const {
		return mChildren.at(index);
	}

	void Container::push_back(Variant* child){
		mChildren.push_back(child);
	}

	Container& Container::operator<<(object_creator_t obj){
		mChildren.push_back(obj.mValue);
		return *this;
	}

	Container& Container::operator<<(Variant* obj){
		mChildren.push_back(obj);
		return *this;
	}

	Container& Container::operator<<(const object_begin_t& obj){
		Object* object = new Object(obj.mName);
		mStreamObjects.push(object);
		mChildren.push_back(object);
		return *this;
	}

	Container& Container::operator<<(const var_t& var){
		if(mStreamObjects.size() > 0)
			mStreamObjects.top()->set(var.mName, var.mValue);

		return *this;
	}

	Container& Container::operator<<(const object_end_t& obj){
		mStreamObjects.pop();
		return *this;
	}

	Container& Container::operator<<(void (*pf)(Container*)){
		(*pf)(this);
		return *this;
	}

	DecodeException::DecodeException(const std::string& what)
		: mWhat(what)
	{
	}

	DecodeException::DecodeException(char* format, ...){
		char buffer[256];

		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, 256, format, args);
		va_end(args);

		mWhat = buffer;
	}

	const char* DecodeException::what() const throw() {
		return mWhat.c_str();
	}

	EncodeException::EncodeException(const std::string& what)
		: mWhat(what)
	{
	}

	EncodeException::EncodeException(char* format, ...){
		char buffer[256];

		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, format, args);
		va_end(args);

		mWhat = buffer;
	}

	const char* EncodeException::what() const throw() {
		return mWhat.c_str();
	}
};
