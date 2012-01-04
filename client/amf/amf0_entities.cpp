#include "amf0.h"
#include "rtmp/packet.h"

namespace amf0 {
	/*
	AMF0_NUMBER;
	*/
	Number::Number(double value)
		: Entity(Type, AMF0), mValue(value)
	{
	}
	
	void Number::serialize(Packet* pak) const {
		Entity::serialize(pak);
		serialize(mValue, pak);
	}

	void Number::deserialize(Packet* pak){
		Entity::deserialize(pak);
		deserialize(mValue, pak);
	}
		
	std::string Number::toString() const {
		log::obj obj;
		obj << mValue;
		return obj;
	}

	void Number::serialize(double value, Packet* pak){
		pak->add<double>(value);
	}

	void Number::deserialize(double& value, Packet* pak){
		pak->read<double>(value);
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
	
	void Boolean::serialize(Packet* pak) const {
		Entity::serialize(pak);
		serialize(mValue, pak);
	}

	void Boolean::deserialize(Packet* pak){
		Entity::deserialize(pak);
		deserialize(mValue, pak);
	}

	void Boolean::serialize(bool value, Packet* pak){
		pak->add<uint8>(value ? 1 : 0);
	}

	void Boolean::deserialize(bool& value, Packet* pak){
		value = pak->read<uint8>() != 0;
	}

	/*
	AMF0_OBJECT;
	*/
	Object::Object()
		: Entity(Type, AMF0)
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

	void Object::serialize(Packet* pak) const {
		Entity::serialize(pak);

		for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr){
			String::serialize(itr->first, pak);
			itr->second->serialize(pak);
		}

		pak->add<uint16>(0);//empty string
		pak->add<uint8>(AMF0_OBJECT_END);//end of object
	}

	void Object::deserialize(Packet* pak){
		Entity::deserialize(pak);

		while(true){
			std::string key;
			String::deserialize(key, pak);

			Entity* value = Entity::read(pak);
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
	
	void Reference::serialize(Packet* pak) const {
		Entity::serialize(pak);
		pak->add<uint16>(mValue);
	}

	void Reference::deserialize(Packet* pak){
		Entity::deserialize(pak);
		pak->read<uint16>(mValue);
	}

	/*
	AMF0_ECMA_ARRAY;
	*/
	AssociativeArray::AssociativeArray()
		: Entity(Type, AMF0)
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
	
	void AssociativeArray::serialize(Packet* pak) const {
		Entity::serialize(pak);

		pak->add<uint32>(mEntries.size());

		for(auto itr = mEntries.begin(); itr != mEntries.end(); ++itr){
			String::serialize(itr->first, pak);
			itr->second->serialize(pak);
		}
	}

	void AssociativeArray::deserialize(Packet* pak){
		Entity::deserialize(pak);
		
		uint32 size = pak->read<uint32>();
		for(uint32 i = 0; i < size; ++i){
			std::string key;
			String::deserialize(key, pak);
			mEntries[key] = Entity::read(pak);
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
		: Entity(Type, AMF0)
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
	
	void StrictArray::serialize(Packet* pak) const {
		Entity::serialize(pak);

		pak->add<uint32>(mEntries.size());
		for(auto itr = mEntries.begin(); itr != mEntries.end(); ++itr)
			(*itr)->serialize(pak);
	}

	void StrictArray::deserialize(Packet* pak){
		Entity::deserialize(pak);
		
		uint32 size = pak->read<uint32>();
		for(uint32 i = 0; i < size; ++i)
			mEntries.push_back(Entity::read(pak));
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
	
	void Date::serialize(Packet* pak) const {
		Entity::serialize(pak);

		pak->add<double>(mValue);
		pak->add<uint16>(mTimeZone);
	}

	void Date::deserialize(Packet* pak){
		Entity::deserialize(pak);

		pak->read<double>(mValue);
		pak->read<uint16>(mTimeZone);
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
	
	void XmlDocument::serialize(Packet* pak) const {
		Entity::serialize(pak);
		LongString::serialize(mValue, pak);
	}

	void XmlDocument::deserialize(Packet* pak){
		Entity::deserialize(pak);
		LongString::deserialize(mValue, pak);
	}

	/*
	AMF0_TYPED_OBJECT
	*/
	TypedObject::TypedObject()
		: Entity(Type, AMF0)
	{
	}

	TypedObject::TypedObject(const std::string& name)
		: Entity(Type, AMF0), mTypename(name)
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

	void TypedObject::serialize(Packet* pak) const {
		Entity::serialize(pak);
		String::serialize(mTypename, pak);

		for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr){
			String::serialize(itr->first, pak);
			itr->second->serialize(pak);
		}

		pak->add<uint16>(0);
		pak->add<uint8>(AMF0_OBJECT_END);
	}

	void TypedObject::deserialize(Packet* pak){
		Entity::deserialize(pak);
		String::deserialize(mTypename, pak);

		while(true){
			std::string key;
			String::deserialize(key, pak);

			Entity* value = Entity::read(pak);
			if(value->type() == AMF0_OBJECT_END){
				delete value;
				break;
			}
			
			mProperties[key] = value;
		}
	}
};
