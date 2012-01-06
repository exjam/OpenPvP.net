#include "amf.h"
#include "amf0.h"
#include "amf3.h"

namespace amf {
	namespace log {
		int obj::mIndent = 0;
		bool obj::mLineStart = true;
		obj::indent_t indent(1);
		obj::indent_t outdent(-1);
	};

	null_t null;
	undefined_t undefined;

	void object_begin(Container* c){
		(*c) << object_begin_t();
	}

	void object_end(Container* c){
		(*c) << object_end_t();
	}

	object_begin_t object_begin(const std::string& name){
		return object_begin_t(name);
	}

	/*
	Base AMFx Entity
	*/
	Entity::Entity(uint32 type, uint32 version)
		: mType(type), mVersion(version)
	{
	}

	uint32 Entity::mActiveVersion = AMF0;
		
	uint32 Entity::type() const {
		return mType;
	}

	void Entity::serialize(ByteStream& stream) const {
		stream << mType;
	}

	void Entity::deserialize(ByteStream& stream){
		stream >> mType;
	}

	std::string Entity::toString() const {
		return std::string();
	}
	
	Entity* Entity::create(Entity* value){
		if(!value){
			if(mActiveVersion == AMF0)
				return new amf0::Null();
			else if(mActiveVersion == AMF3)
				return new amf3::Null();
		}

		return value;
	}

	Entity* Entity::createObject(const std::string& name){
		if(mActiveVersion == AMF0){
			if(name.length())
				return new amf0::TypedObject(name);
			else
				return new amf0::Object();
		}else
			return new amf3::Object(name);
	}

	Entity* Entity::create(const undefined_t&){
		if(mActiveVersion == AMF0)
			return new amf0::Undefined();
		else
			return new amf3::Undefined();
	}

	Entity* Entity::create(const bool& value){
		if(mActiveVersion == AMF0)
			return new amf0::Boolean(value);
		else
			return new amf3::Boolean(value);
	}
	
	Entity* Entity::create(const uint8& value){
		return create((uint32)value);
	}

	Entity* Entity::create(const uint16& value){
		return create((uint32)value);
	}

	Entity* Entity::create(const uint32& value){
		if(mActiveVersion == AMF0)
			return new amf0::Number((double)value);
		else
			return new amf3::Integer(value);
	}

	Entity* Entity::create(const int8& value){
		return create((int32)value);
	}

	Entity* Entity::create(const int16& value){
		return create((int32)value);
	}

	Entity* Entity::create(const int32& value){
		if(mActiveVersion == AMF0)
			return new amf0::Number((double)value);
		else
			return new amf3::Integer(value);
	}

	Entity* Entity::create(const float& value){
		return create((double)value);
	}

	Entity* Entity::create(const double& value){
		if(mActiveVersion == AMF0)
			return new amf0::Number(value);
		else
			return new amf3::Double(value);
	}

	Entity* Entity::create(const char* value){
		return create(std::string(value));
	}

	Entity* Entity::create(const std::string& value){
		if(mActiveVersion == AMF0)
			return new amf0::String(value);
		else
			return new amf3::String(value);
	}
		
	int32 Entity::asInt() const {
		if(mVersion == AMF0){
			if(mType == amf0::AMF0_NUMBER)
				return (int32)((amf0::Number*)this)->value();
			else if(mType == amf0::AMF0_NULL)
				return 0;
		}else if(mVersion == AMF3){
			if(mType == amf3::AMF3_INTEGER)
				return ((amf3::Integer*)this)->value();
			else if(mType == amf3::AMF3_NULL)
				return 0;
		}
		
		throw new DecodeException("Invalid cast to uint32");
	}
	
	double Entity::asDouble() const {
		if(mVersion == AMF0){
			if(mType == amf0::AMF0_NUMBER)
				return ((amf0::Number*)this)->value();
			else if(mType == amf0::AMF0_NULL)
				return 0;
		}else if(mVersion == AMF3){
			if(mType == amf3::AMF3_DOUBLE)
				return ((amf3::Double*)this)->value();
			else if(mType == amf3::AMF3_NULL)
				return 0;
		}

		throw new DecodeException("Invalid cast to double");
	}
	
	bool Entity::asBool() const {
		if(mVersion == AMF0){
			if(mType == amf0::AMF0_BOOLEAN)
				return ((amf0::Boolean*)this)->value();
			else if(mType == amf0::AMF0_NULL)
				return false;
		}else if(mVersion == AMF3){
			if(mType == amf3::AMF3_BOOLEAN)
				return ((amf3::Boolean*)this)->value();
			else if(mType == amf3::AMF3_NULL)
				return false;
		}

		throw new DecodeException("Invalid cast to boolean");
	}
	
	Object* Entity::asObject() const {
		if(mVersion == AMF0){
			if(mType == amf0::AMF0_OBJECT)
				return (Object*)this;
			else if(mType == amf0::AMF0_TYPED_OBJECT)
				return (Object*)this;
			else if(mType == amf0::AMF0_ECMA_ARRAY)
				return (Object*)this;
			else if(mType == amf0::AMF0_STRICT_ARRAY)
				return (Object*)this;
			else if(mType == amf3::AMF3_NULL)
				return nullptr;
		}else if(mVersion == AMF3){
			if(mType == amf3::AMF3_OBJECT)
				return (Object*)this;
			else if(mType == amf3::AMF3_ARRAY)
				return (Object*)this;
			else if(mType == amf3::AMF3_NULL)
				return nullptr;
		}
		
		throw new DecodeException("Invalid cast to object");
	}
	
	std::string Entity::asString() const {
		if(mVersion == AMF0){
			if(mType == amf0::AMF0_STRING)
				return ((amf0::String*)this)->value();
			else if(mType == amf0::AMF0_LONG_STRING)
				return ((amf0::LongString*)this)->value();
			else if(mType == amf0::AMF0_XML_DOC)
				return ((amf0::XmlDocument*)this)->value();
			else if(mType == amf0::AMF0_NULL)
				return std::string();
		}else if(mVersion == AMF3){
			if(mType == amf3::AMF3_STRING)
				return ((amf3::String*)this)->value();
			else if(mType == amf3::AMF3_XML)
				return ((amf3::Xml*)this)->value();
			else if(mType == amf3::AMF3_XML_DOC)
				return ((amf3::XmlDocument*)this)->value();
			else if(mType == amf3::AMF3_NULL)
				return std::string();
		}
		
		throw new DecodeException("Invalid cast to string");
	}

	Entity* Entity::readAMF0(ByteStream& stream){
		using namespace amf0;

		Entity* result = NULL;
		uint8 type = stream.peek();

		switch(type){
			case AMF0_NUMBER:
				result = new Number();
				break;
			case AMF0_BOOLEAN:
				result = new Boolean();
				break;
			case AMF0_STRING:
				result = new String();
				break;
			case AMF0_OBJECT:
				result = new amf0::Object();
				break;
			case AMF0_MOVIECLIP:
				result = new MovieClip();
				break;
			case AMF0_NULL:
				result = new Null();
				break;
			case AMF0_UNDEFINED:
				result = new Undefined();
				break;
			case AMF0_REFERENCE:
				result = new Reference();
				break;
			case AMF0_ECMA_ARRAY:
				result = new AssociativeArray();
				break;
			case AMF0_OBJECT_END:
				result = new ObjectEnd();
				break;
			case AMF0_STRICT_ARRAY:
				result = new StrictArray();
				break;
			case AMF0_DATE:
				result = new Date();
				break;
			case AMF0_LONG_STRING:
				result = new LongString();
				break;
			case AMF0_UNSUPPORTED:
				result = new Unsupported();
				break;
			case AMF0_RECORDSET:
				result = new RecordSet();
				break;
			case AMF0_XML_DOC:
				result = new XmlDocument();
				break;
			case AMF0_TYPED_OBJECT:
				result = new TypedObject();
				break;
			case AMF0_AVMPLUS:
				stream.skip(1);
				return Entity::read(AMF3, stream);
			default:
				throw new DecodeException("Unsupported AMF0 marker %d\n", type);
		}

		if(result)
			result->deserialize(stream);

		return result;
	}

	Entity* Entity::readAMF3(ByteStream& stream){
		using namespace amf3;

		Entity* result = NULL;
		uint8 type = stream.peek();

		switch(type){
			case AMF3_UNDEFINED:
				result = new Undefined();
				break;
			case AMF3_NULL:
				result = new Null();
				break;
			case AMF3_FALSE:
				result = new Boolean();
				break;
			case AMF3_TRUE:
				result = new Boolean();
				break;
			case AMF3_INTEGER:
				result = new Integer();
				break;
			case AMF3_DOUBLE:
				result = new Double();
				break;
			case AMF3_STRING:
				result = new String();
				break;
			case AMF3_XML_DOC:
				result = new XmlDocument();
				break;
			case AMF3_DATE:
				result = new Date();
				break;
			case AMF3_ARRAY:
				result = new Array();
				break;
			case AMF3_OBJECT:
				result = new amf3::Object();
				break;
			case AMF3_XML:
				result = new Xml();
				break;
			case AMF3_BYTE_ARRAY:
				result = new ByteArray();
				break;
			case AMF3_AVMPLUS:
				stream.skip(1);
				break;
			default:
				throw new DecodeException("Unsupported AMF3 marker %d\n", type);
		}

		if(result)
			result->deserialize(stream);

		return result;
	}
	
	void Entity::setVersion(uint32 version){
		mActiveVersion = version;
	}

	Entity* Entity::read(ByteStream& stream){
		return (mActiveVersion == AMF0) ? readAMF0(stream) : readAMF3(stream);
	}

	Entity* Entity::read(uint32 version, ByteStream& stream){
		mActiveVersion = version;
		return read(stream);
	}

	/*
	AMFx Container
	*/
	Container::Container(){
	}

	Container::~Container(){
		for(auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
			delete *itr;
	}

	std::string Container::toString() const {
		log::obj obj;

		obj << "{" << std::endl;
		obj << log::indent;

		for(auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
			obj << (*itr)->toString() << std::endl;
			
		obj << log::outdent;
		obj << "}";

		return obj;
	}
	
	void Container::serialize(ByteStream& stream) const {
		for(auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
			(*itr)->serialize(stream);
	}

	void Container::deserialize(ByteStream& stream){
		while(!stream.eof())
			add(Entity::read(stream));
	}

	/*
	Decode Exception
	*/
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
	
	/*
	Encode Exception
	*/
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
