#include "amf3.h"
#include "rtmp/packet.h"

namespace amf3 {
	/*
	AMF3_UNDEFINED
	*/
	Undefined::Undefined()
		: Entity(Type, AMF3)
	{
	}

	std::string Undefined::toString() const {
		log::obj obj;
		obj << "(undefined)";
		return obj;
	}

	/*
	AMF3_NULL
	*/
	Null::Null()
		: Entity(Type, AMF3)
	{
	}
		
	std::string Null::toString() const {
		log::obj obj;
		obj << "(null)";
		return obj;
	}

	/*
	AMF3_TRUE and AMF3_FALSE
	*/
	Boolean::Boolean(bool value)
		: Entity(Type, AMF3), mValue(value)
	{
	}

	std::string Boolean::toString() const {
		log::obj obj;
		obj << (mValue ? "true" : "false");
		return obj;
	}
	
	void Boolean::serialize(Packet* pak) const {
		if(mValue)
			pak->add<uint8>(AMF3_TRUE);
		else
			pak->add<uint8>(AMF3_FALSE);
	}

	void Boolean::deserialize(Packet* pak){
		mValue = pak->read<uint8>() == AMF3_TRUE;
	}

	/*
	AMF3_INTEGER
	*/
	Integer::Integer(int32 value)
		: Entity(Type, AMF3), mValue(value)
	{
	}
		
	std::string Integer::toString() const {
		log::obj obj;
		obj << mValue;
		return obj;
	}
	
	void Integer::serialize(Packet* pak) const {
		Entity::serialize(pak);
		serialize(mValue, pak);
	}

	void Integer::deserialize(Packet* pak){
		Entity::deserialize(pak);
		deserialize(mValue, pak);
	}

	void Integer::deserialize(uint32& value, Packet* pak){
		int32 tmp;
		deserialize(tmp, pak);
		value = tmp;
	}

	void Integer::deserialize(int32& value, Packet* pak){
		value = 0;

		for(int i = 0, byte = 0x80; i < 4 && byte & 0x80; ++i){
			byte = pak->read<uint8>();
			if(i < 3){
				value <<= 7;
				value |= byte & 0x7F;
			}else{
				value = (value << 8) | byte;
			}
		}

		if(value & 0x10000000)
            value |= ~0x1fffffff;
	}

	void Integer::serialize(int32 value, Packet* pak){
		uint32 tmp = value;

		if(value < 0)
			tmp = (1 << 29) + value;

		if(tmp < 1 << 7){
			pak->add<uint8>(tmp);
		}else if(tmp < 1 << 14){
			pak->add<uint8>(0x80 | ((tmp >>  7) & 0xFF));
			pak->add<uint8>(tmp & 0x7F);
		}else if(tmp < 1 << 21){
			pak->add<uint8>(0x80 | ((tmp >> 14) & 0xFF));
			pak->add<uint8>(0x80 | ((tmp >>  7) & 0xFF));
			pak->add<uint8>(tmp & 0x7F);
		}else{
			pak->add<uint8>(0x80 | ((tmp >> 22) & 0xFF));
			pak->add<uint8>(0x80 | ((tmp >> 15) & 0xFF));
			pak->add<uint8>(0x80 | ((tmp >>  8) & 0xFF));
			pak->add<uint8>(tmp & 0xFF);
		}
	}

	/*
	AMF3_DOUBLE
	*/
	Double::Double(double value)
		: Entity(Type, AMF3), mValue(value)
	{
	}
		
	std::string Double::toString() const {
		log::obj obj;
		obj << mValue;
		return obj;
	}
	
	void Double::serialize(Packet* pak) const {
		Entity::serialize(pak);
		serialize(mValue, pak);
	}

	void Double::deserialize(Packet* pak){
		Entity::deserialize(pak);
		deserialize(mValue, pak);
	}
	
	void Double::serialize(double value, Packet* pak){
		pak->add<double>(value);
	}

	void Double::deserialize(double& value, Packet* pak){
		pak->read<double>(value);
	}

	/*
	AMF3_STRING
	*/
	String::String()
		: Entity(Type, AMF3)
	{
	}

	String::String(const std::string& value)
		: Entity(Type, AMF3), mValue(value)
	{
	}

	std::string String::toString() const {
		log::obj obj;
		obj << "\"" << mValue << "\"";
		return obj;
	}
	
	void String::serialize(Packet* pak) const {
		Entity::serialize(pak);
		serialize(mValue, pak);
	}

	void String::deserialize(Packet* pak){
		Entity::deserialize(pak);
		deserialize(mValue, pak);
	}

	void String::deserialize(std::string& str, Packet* pak){
		uint32 length;
		Integer::deserialize(length, pak);

		if(length & 1){
			length >>= 1;
			if(length > 0){
				str.assign((char*)pak->data() + pak->position(), length);
				pak->skip(length);

				ReferenceTables::Strings.add(str);
			}
		}else{
			str = ReferenceTables::Strings.get(length >> 1);
		}
	}

	void String::serialize(const std::string& str, Packet* pak){
		Integer::serialize((str.length() << 1) | 1, pak);
		pak->add(str.c_str(), str.length());
	}

	/*
	AMF3_XML_DOC
	*/
	XmlDocument::XmlDocument()
		: Entity(Type, AMF3)
	{
	}

	XmlDocument::XmlDocument(const std::string& value)
		: Entity(Type, AMF3), mValue(value)
	{
	}
		
	std::string XmlDocument::toString() const {
		log::obj obj;
		obj << "{ xml ";
		obj << log::indent;
		obj << mValue;
		obj << log::outdent;
		obj << "}";
		return obj;
	}
	
	void XmlDocument::serialize(Packet* pak) const {
		Entity::serialize(pak);
		String::serialize(mValue, pak);
	}

	void XmlDocument::deserialize(Packet* pak){
		Entity::deserialize(pak);
		String::deserialize(mValue, pak);
	}

	/*
	AMF3_DATE
	*/
	Date::Date()
		: Entity(Type, AMF3)
	{
	}

	Date::Date(double value)
		: Entity(Type, AMF3), mValue(value)
	{
	}
		
	std::string Date::toString() const {
		log::obj obj;
		obj << mValue;
		return obj;
	}
	
	void Date::serialize(Packet* pak) const {
		Entity::serialize(pak);

		pak->add<uint8>(1);
		pak->add<double>(mValue);
	}

	void Date::deserialize(Packet* pak){
		Entity::deserialize(pak);

		uint32 length;
		Integer::deserialize(length, pak);
		if(length & 1){
			pak->read<double>(mValue);
		}else{
			throw DecodeException("TODO: Date references not supported");
		}
	}

	/*
	AMF3_ARRAY
	*/
	Array::Array()
		: Entity(Type, AMF3)
	{
	}

	Array::~Array(){
		for(auto itr = mDense.begin(); itr != mDense.end(); ++itr)
			delete *itr;

		for(auto itr = mAssociative.begin(); itr != mAssociative.end(); ++itr)
			delete itr->second;
	}

	std::string Array::toString() const {
		log::obj obj;

		obj << "{ array" << std::endl;
		obj << log::indent;

		for(auto itr = mAssociative.begin(); itr != mAssociative.end(); ++itr){
			obj << "'" << itr->first << "' =>";
			obj << itr->second->toString() << std::endl;
		}

		int i = 0;
		for(auto itr = mDense.begin(); itr != mDense.end(); ++itr, ++i){
			obj << "[" << i << "] =>";
			obj << log::indent;
			obj << (*itr)->toString() << std::endl;
			obj << log::outdent;
		}

		obj << log::outdent;
		obj << "}";

		return obj;
	}

	void Array::serialize(Packet* pak) const {
		Entity::serialize(pak);
		Integer::serialize(mDense.size() << 1 | 1, pak);

		for(auto itr = mAssociative.begin(); itr != mAssociative.end(); ++itr){
			String::serialize(itr->first, pak);
			itr->second->serialize(pak);
		}

		for(auto itr = mDense.begin(); itr != mDense.end(); ++itr)
			(*itr)->serialize(pak);
	}

	void Array::deserialize(Packet* pak){
		Entity::deserialize(pak);
			
		uint32 length;
		Integer::deserialize(length, pak);

		if(length & 1){
			length >>= 1;
				
			while(true){
				std::string key;
				String::deserialize(key, pak);

				if(key.length() == 0) break;

				mAssociative[key] = Entity::read(pak);
			}

			for(uint32 i = 0; i < length; ++i)
				mDense.push_back(Entity::read(pak));
		}else{
			throw DecodeException("TODO: Array references not supported");
		}
	}

	/*
	AMF3_OBJECT
	*/
	Object::Object()
		: Entity(Type, AMF3), mDefinition(nullptr)
	{
	}

	Object::~Object(){
		for(auto itr = mStaticValues.begin(); itr != mStaticValues.end(); ++itr)
			delete itr->second;

		for(auto itr = mDynamicMembers.begin(); itr != mDynamicMembers.end(); ++itr)
			delete itr->second;
	}
		
	std::string Object::toString() const {
		log::obj obj;

		obj << "{ object " << mDefinition->mTypename << std::endl;
		obj << log::indent;

		for(auto itr = mStaticValues.begin(); itr != mStaticValues.end(); ++itr){
			obj << itr->first << " = ";
			obj << itr->second->toString() << std::endl;
		}

		for(auto itr = mDynamicMembers.begin(); itr != mDynamicMembers.end(); ++itr){
			obj << "'" << itr->first << "' => ";
			obj << itr->second->toString() << std::endl;
		}
			
		obj << log::outdent;
		obj << "}";

		return obj;
	}

	void Object::serialize(Packet* pak) const {
		if(mDefinition->mMembers.size() != mStaticValues.size())
			throw new EncodeException("Class definition member count != value count");

		Entity::serialize(pak);

		uint32 ref = 0;
		ref |= 1;//Not an object reference
		ref |= 1 << 1;//Not a class definition reference
		ref |= (mDefinition->mExternalizable ? 1 : 0) << 2;//extern
		ref |= (mDynamicMembers.size() > 0 ? 1 : 0) << 3;
		ref |= mDefinition->mMembers.size() << 4;

		for(auto itr = mDefinition->mMembers.begin(); itr != mDefinition->mMembers.end(); ++itr)
			String::serialize(*itr, pak);

		for(auto itr = mStaticValues.begin(); itr != mStaticValues.end(); ++itr)
			itr->second->serialize(pak);
			
		for(auto itr = mDynamicMembers.begin(); itr != mDynamicMembers.end(); ++itr){
			String::serialize(itr->first, pak);
			itr->second->serialize(pak);
		}
	}

	void Object::deserialize(Packet* pak){
		Entity::deserialize(pak);

		uint32 ref;
		Integer::deserialize(ref, pak);
		if(ref & 1){
			ref >>= 1;

			mDefinition = NULL;
			if(ref & 1){
				ref >>= 1;

				mDefinition = new ClassDefinition();
				String::deserialize(mDefinition->mTypename, pak);
				mDefinition->mExternalizable = (ref & 1) != 0;
				mDefinition->mDynamic = ((ref >> 1) & 1) != 0;
					
				uint32 members = ref >> 2;
				for(uint32 i = 0; i < members; ++i){
					std::string tmp;
					String::deserialize(tmp, pak);
					mDefinition->mMembers.push_back(tmp);
				}
				
				ReferenceTables::ClassDefinitions.add(mDefinition);
			}else{
				mDefinition = ReferenceTables::ClassDefinitions.get(ref >> 1);
			}

			if(!mDefinition)
				throw DecodeException("Object class definition '%s' not found", mDefinition->mTypename);
				
			if(mDefinition->mExternalizable){
				ExternalDefinition* extDef = ExternalDefinition::find(mDefinition->mTypename);

				if(!extDef)
					throw DecodeException("Externalizable class '%s' not found", mDefinition->mTypename);

				extDef->read(this, pak);
			}else{
				for(auto itr = mDefinition->mMembers.begin(); itr != mDefinition->mMembers.end(); ++itr)
					mStaticValues[*itr] = Entity::read(pak);
			}

			if(mDefinition->mDynamic){
				while(true){
					std::string key;
					String::deserialize(key, pak);
					if(key.length() == 0) break;
					
					mDynamicMembers[key] = Entity::read(pak);
				}
			}
		}else{
			throw DecodeException("TODO: Object references not supported");
		}
	}

	/*
	AMF3_XML
	*/
	Xml::Xml()
		: Entity(Type, AMF3)
	{
	}

	std::string Xml::toString() const {
		log::obj obj;
		obj << "{ xml ";
		obj << log::indent;
		obj << mValue;
		obj << log::outdent;
		obj << "}";
		return obj;
	}

	void Xml::serialize(Packet* pak) const {
		Entity::serialize(pak);

		Integer::serialize((mValue.length() << 1) | 1, pak);
		pak->add(mValue.c_str(), mValue.length());
	}

	void Xml::deserialize(Packet* pak){
		Entity::deserialize(pak);

		uint32 length;
		Integer::deserialize(length, pak);
		if(length & 1){
			length >>= 1;
			mValue.assign((char*)pak->data() + pak->position(), length);
			pak->skip(length);
		}else{
			throw new DecodeException("TODO: XML Object references are unsupported"); 
		}
	}

	/*
	AMF3_BYTE_ARRAY
	*/
	ByteArray::ByteArray()
		: Entity(Type, AMF3), mLength(0), mValue(nullptr)
	{
	}

	ByteArray::~ByteArray(){
		if(mValue != nullptr)
			delete [] mValue;
	}

	std::string ByteArray::toString() const {
		log::obj obj;
			
		obj << "{ raw " << mLength << std::endl;
		obj << log::indent;

		for(uint32 i = 0; i < mLength; ++i){
			obj << log::hex(mValue[i]) << " ";

			if(i > 0 && i % 16 == 0)
				obj << std::endl;
		}

		obj << log::outdent;
		obj << std::endl << "}";

		return obj;
	}

	void ByteArray::serialize(Packet* pak) const {
		Entity::serialize(pak);

		Integer::serialize((mLength << 1) | 1, pak);
		pak->add(mValue, mLength);
	}

	void ByteArray::deserialize(Packet* pak){
		Entity::deserialize(pak);

		Integer::deserialize(mLength, pak);
		if(mLength & 1){
			mLength >>= 1;
			mValue = new uint8[mLength];
			memcpy(mValue, (char*)pak->data() + pak->position(), mLength);
			pak->skip(mLength);
		}else{
			throw new DecodeException("TODO: Byte Array references are unsupported"); 
		}
	}
};
