#include "amf.h"
#include "amf0.h"
#include "amf3.h"
#include "rtmp/packet.h"

namespace amf {
	namespace log {
		int obj::mIndent = 0;
		bool obj::mLineStart = true;
		obj::indent_t indent(1);
		obj::indent_t outdent(-1);
	};

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

	void Entity::serialize(Packet* pak) const {
		pak->add<uint8>(mType);
	}

	void Entity::deserialize(Packet* pak){
		pak->read<uint8>(mType);
	}

	std::string Entity::toString() const {
		return std::string();
	}
	
	Entity* Entity::create(Entity* value){
		return value;
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

	Entity* Entity::readAMF0(Packet* pak){
		using namespace amf0;

		Entity* result = NULL;
		uint8 type = pak->peek<uint8>();

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
				result = new Object();
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
				pak->skip(1);
				return Entity::read(AMF3, pak);
			default:
				throw new DecodeException("Unsupported AMF0 marker %d\n", type);
		}

		if(result)
			result->deserialize(pak);

		return result;
	}

	Entity* Entity::readAMF3(Packet* pak){
		using namespace amf3;

		Entity* result = NULL;
		uint8 type = pak->peek<uint8>();

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
				result = new Object();
				break;
			case AMF3_XML:
				result = new Xml();
				break;
			case AMF3_BYTE_ARRAY:
				result = new ByteArray();
				break;
			case AMF3_AVMPLUS:
				pak->skip(1);
				break;
			default:
				throw new DecodeException("Unsupported AMF3 marker %d\n", type);
		}

		if(result)
			result->deserialize(pak);

		return result;
	}

	Entity* Entity::read(Packet* pak){
		return (mActiveVersion == AMF0) ? readAMF0(pak) : readAMF3(pak);
	}

	Entity* Entity::read(uint32 version, Packet* pak){
		mActiveVersion = version;
		return read(pak);
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
	
	void Container::serialize(Packet* pak) const {
		for(auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
			(*itr)->serialize(pak);
	}

	void Container::deserialize(Packet* pak){
		while(pak->position() < pak->size())
			add(Entity::read(pak));
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
