#include "amf0.h"

namespace amf0 {
	/*
	AMF0_NUMBER;
	*/
	Number::Number(double value)
		: Entity(Type, AMF0), mValue(value)
	{
	}
	
	void Number::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		serialize(mValue, stream);
	}

	void Number::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		deserialize(mValue, stream);
	}
		
	std::string Number::toString() const {
		log::obj obj;
		obj << mValue;
		return obj;
	}

	void Number::serialize(double value, ByteStream& stream){
		stream << value;
	}

	void Number::deserialize(double& value, ByteStream& stream){
		stream >> value;
	}

	/*
	AMF0_BOOLEAN;
	*/
	Boolean::Boolean(bool value)
		: Entity(Type, AMF0), mValue(value)
	{
	}
		
	std::string Boolean::toString() const {
		log::obj obj;
		obj << (mValue ? "true" : "false");
		return obj;
	}
	
	void Boolean::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		serialize(mValue, stream);
	}

	void Boolean::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		deserialize(mValue, stream);
	}

	void Boolean::serialize(bool value, ByteStream& stream){
		stream << uint8(value ? 1 : 0);
	}

	void Boolean::deserialize(bool& value, ByteStream& stream){
		uint8 tmp;
		stream >> tmp;
		value = tmp != 0;
	}

	/*
	AMF0_OBJECT;
	*/
	Object::Object()
		: amf::Object(Type, AMF0)
	{
	}

	Object::~Object(){
		for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr)
			delete itr->second;
	}

	std::string Object::toString() const {
		log::obj obj;

		obj << "{ object" << std::endl;
		obj << log::indent;
			
		for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr){
			obj << "'" << itr->first << "' => ";
			obj << itr->second->toString() << std::endl;
		}
			
		obj << log::outdent;
		obj << "}";

		return obj;
	}

	void Object::serialize(ByteStream& stream) const {
		Entity::serialize(stream);

		for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr){
			String::serialize(itr->first, stream);
			itr->second->serialize(stream);
		}

		stream << uint16(0);//empty string
		stream << uint8(AMF0_OBJECT_END);//end of object
	}

	void Object::deserialize(ByteStream& stream){
		Entity::deserialize(stream);

		while(true){
			std::string key;
			String::deserialize(key, stream);

			Entity* value = Entity::read(stream);
			if(value->type() == AMF0_OBJECT_END){
				delete value;
				break;
			}
			
			mProperties[key] = value;
		}
	}

	/*
	AMF0_MOVIECLIP;
	*/
	MovieClip::MovieClip()
		: Entity(Type, AMF0)
	{
	}

	std::string MovieClip::toString() const {
		log::obj obj;
		obj << "movieclip";
		return obj;
	}

	/*
	AMF0_NULL
	*/
	Null::Null()
		: Entity(Type, AMF0)
	{
	}

	std::string Null::toString() const {
		log::obj obj;
		obj << "null";
		return obj;
	}

	/*
	AMF0_UNDEFINED;
	*/
	Undefined::Undefined()
		: Entity(Type, AMF0)
	{
	}

	std::string Undefined::toString() const {
		log::obj obj;
		obj << "undefined";
		return obj;
	}

	/*
	AMF0_REFERENCE
	*/
	Reference::Reference(uint16 value)
		: Entity(Type, AMF0), mValue(value)
	{
	}

	std::string Reference::toString() const {
		log::obj obj;
		obj << "reference[" << mValue << "]";
		return obj;
	}
	
	void Reference::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		stream << mValue;
	}

	void Reference::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		stream >> mValue;
	}

	/*
	AMF0_ECMA_ARRAY;
	*/
	AssociativeArray::AssociativeArray()
		: amf::Object(Type, AMF0)
	{
	}

	AssociativeArray::~AssociativeArray(){
		for(auto itr = mEntries.begin(); itr != mEntries.end(); ++itr)
			delete itr->second;
	}

	std::string AssociativeArray::toString() const {
		log::obj obj;

		obj << "{ array " << std::endl;
		obj << log::indent;

		for(auto itr = mEntries.begin(); itr != mEntries.end(); ++itr){
			obj << "'" << itr->first << "' => ";
			obj << itr->second->toString() << std::endl;
		}
			
		obj << log::outdent;
		obj << "}";

		return obj;
	}
	
	void AssociativeArray::serialize(ByteStream& stream) const {
		Entity::serialize(stream);

		stream << uint32(mEntries.size());

		for(auto itr = mEntries.begin(); itr != mEntries.end(); ++itr){
			String::serialize(itr->first, stream);
			itr->second->serialize(stream);
		}
	}

	void AssociativeArray::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		
		uint32 size;
		stream >> size;
		for(uint32 i = 0; i < size; ++i){
			std::string key;
			String::deserialize(key, stream);
			mEntries[key] = Entity::read(stream);
		}
	}

	/*
	AMF0_OBJECT_END
	*/
	ObjectEnd::ObjectEnd()
		: Entity(Type, AMF0)
	{
	}

	/*
	AMF0_STRICT_ARRAY;
	*/
	StrictArray::StrictArray()
		: amf::Object(Type, AMF0)
	{
	}

	StrictArray::~StrictArray(){
		for(auto itr = mEntries.begin(); itr != mEntries.end(); ++itr)
			delete *itr;
	}

	std::string StrictArray::toString() const {
		log::obj obj;

		obj << "{ array " << std::endl;
		obj << log::indent;

		uint32 i = 0;
		for(auto itr = mEntries.begin(); itr != mEntries.end(); ++itr, ++i){
			obj << "[" << i << "] => ";
			obj << (*itr)->toString() << std::endl;
		}
			
		obj << log::outdent;
		obj << "}";

		return obj;
	}
	
	void StrictArray::serialize(ByteStream& stream) const {
		Entity::serialize(stream);

		stream << uint32(mEntries.size());
		for(auto itr = mEntries.begin(); itr != mEntries.end(); ++itr)
			(*itr)->serialize(stream);
	}

	void StrictArray::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		
		uint32 size;
		stream >> size;
		for(uint32 i = 0; i < size; ++i)
			mEntries.push_back(Entity::read(stream));
	}

	/*
	AMF0_DATE
	*/
	Date::Date(double value, uint16 timezone)
		: Entity(Type, AMF0), mValue(value), mTimeZone(timezone)
	{
	}

	std::string Date::toString() const {
		log::obj obj;

		obj << "{ date " << std::endl;
		obj << log::indent;

		obj << "value => " << mValue << std::endl;
		obj << "timezone => " << mTimeZone << std::endl;

		obj << log::outdent;
		obj << "}";

		return obj;
	}
	
	void Date::serialize(ByteStream& stream) const {
		Entity::serialize(stream);

		stream << mValue;
		stream << mTimeZone;
	}

	void Date::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		
		stream >> mValue;
		stream >> mTimeZone;
	}

	/*
	AMF0_UNSUPPORTED
	*/
	Unsupported::Unsupported()
		: Entity(Type, AMF0)
	{
	}

	std::string Unsupported::toString() const {
		log::obj obj;
		obj << "unsupported";
		return obj;
	}

	/*
	AMF0_RECORDSET
	*/
	RecordSet::RecordSet()
		: Entity(Type, AMF0)
	{
	}

	std::string RecordSet::toString() const {
		log::obj obj;
		obj << "recordset";
		return obj;
	}

	/*
	AMF0_XML_DOC;
	*/
	XmlDocument::XmlDocument()
		: Entity(Type, AMF0)
	{
	}

	XmlDocument::XmlDocument(const std::string& value)
		: Entity(Type, AMF0), mValue(value)
	{
	}

	std::string XmlDocument::toString() const {
		log::obj obj;
		obj << "{ xml " << std::endl;
		obj << mValue << std::endl;
		obj << "}";
		return obj;
	}
	
	void XmlDocument::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		LongString::serialize(mValue, stream);
	}

	void XmlDocument::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		LongString::deserialize(mValue, stream);
	}

	/*
	AMF0_TYPED_OBJECT
	*/
	TypedObject::TypedObject()
		: amf::Object(Type, AMF0)
	{
	}

	TypedObject::TypedObject(const std::string& name)
		: amf::Object(Type, AMF0), mTypename(name)
	{
	}

	TypedObject::~TypedObject(){
		for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr)
			delete itr->second;
	}

	std::string TypedObject::toString() const {
		log::obj obj;

		obj << "{ object " << mTypename << std::endl;
		obj << log::indent;

		for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr){
			obj << "'" << itr->first << "' => ";
			obj << itr->second->toString() << std::endl;
		}

		obj << log::outdent;
		obj << "}";

		return obj;
	}

	void TypedObject::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		String::serialize(mTypename, stream);

		for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr){
			String::serialize(itr->first, stream);
			itr->second->serialize(stream);
		}

		stream << uint16(0);
		stream << uint8(AMF0_OBJECT_END);
	}

	void TypedObject::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		String::deserialize(mTypename, stream);

		while(true){
			std::string key;
			String::deserialize(key, stream);

			Entity* value = Entity::read(stream);
			if(value->type() == AMF0_OBJECT_END){
				delete value;
				break;
			}
			
			mProperties[key] = value;
		}
	}
};
