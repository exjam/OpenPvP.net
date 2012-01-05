#include "amf3.h"

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
	
	void Boolean::serialize(ByteStream& stream) const {
		if(mValue)
			stream << uint8(AMF3_TRUE);
		else
			stream << uint8(AMF3_FALSE);
	}

	void Boolean::deserialize(ByteStream& stream){
		uint8 value;
		stream >> value;
		mValue = value == AMF3_TRUE;
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
	
	void Integer::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		serialize(mValue, stream);
	}

	void Integer::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		deserialize(mValue, stream);
	}

	void Integer::deserialize(uint32& value, ByteStream& stream){
		int32 tmp;
		deserialize(tmp, stream);
		value = tmp;
	}

	void Integer::deserialize(int32& value, ByteStream& stream){
		value = 0;
		uint8 byte = 0x80;
		for(int i = 0; i < 4 && byte & 0x80; ++i){
			stream >> byte;
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

	void Integer::serialize(int32 value, ByteStream& stream){
		uint32 tmp = value;

		if(value < 0)
			tmp = (1 << 29) + value;

		if(tmp < 1 << 7){
			stream << uint8(tmp);
		}else if(tmp < 1 << 14){
			stream << uint8(0x80 | ((tmp >>  7) & 0xFF));
			stream << uint8(tmp & 0x7F);
		}else if(tmp < 1 << 21){
			stream << uint8(0x80 | ((tmp >> 14) & 0xFF));
			stream << uint8(0x80 | ((tmp >>  7) & 0xFF));
			stream << uint8(tmp & 0x7F);
		}else{
			stream << uint8(0x80 | ((tmp >> 22) & 0xFF));
			stream << uint8(0x80 | ((tmp >> 15) & 0xFF));
			stream << uint8(0x80 | ((tmp >>  8) & 0xFF));
			stream << uint8(tmp & 0xFF);
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
	
	void Double::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		serialize(mValue, stream);
	}

	void Double::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		deserialize(mValue, stream);
	}
	
	void Double::serialize(double value, ByteStream& stream){
		stream << value;
	}

	void Double::deserialize(double& value, ByteStream& stream){
		stream >> value;
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
	
	void String::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		serialize(mValue, stream);
	}

	void String::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		deserialize(mValue, stream);
	}

	void String::deserialize(std::string& str, ByteStream& stream){
		uint32 length;
		Integer::deserialize(length, stream);

		if(length & 1){
			length >>= 1;
			if(length > 0){
				str.assign((char*)stream.data() + stream.tell(), length);
				stream.skip(length);

				ReferenceTables::Strings.add(str);
			}
		}else{
			str = ReferenceTables::Strings.get(length >> 1);
		}
	}

	void String::serialize(const std::string& str, ByteStream& stream){
		Integer::serialize((str.length() << 1) | 1, stream);
		stream.write(str.c_str(), str.length());
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
	
	void XmlDocument::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		String::serialize(mValue, stream);
	}

	void XmlDocument::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
		String::deserialize(mValue, stream);
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
	
	void Date::serialize(ByteStream& stream) const {
		Entity::serialize(stream);

		stream << uint8(1);
		stream << mValue;
	}

	void Date::deserialize(ByteStream& stream){
		Entity::deserialize(stream);

		uint32 length;
		Integer::deserialize(length, stream);
		if(length & 1){
			stream >> mValue;
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

	void Array::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		Integer::serialize(mDense.size() << 1 | 1, stream);

		for(auto itr = mAssociative.begin(); itr != mAssociative.end(); ++itr){
			String::serialize(itr->first, stream);
			itr->second->serialize(stream);
		}

		for(auto itr = mDense.begin(); itr != mDense.end(); ++itr)
			(*itr)->serialize(stream);
	}

	void Array::deserialize(ByteStream& stream){
		Entity::deserialize(stream);
			
		uint32 length;
		Integer::deserialize(length, stream);

		if(length & 1){
			length >>= 1;
				
			while(true){
				std::string key;
				String::deserialize(key, stream);

				if(key.length() == 0) break;

				mAssociative[key] = Entity::read(stream);
			}

			for(uint32 i = 0; i < length; ++i)
				mDense.push_back(Entity::read(stream));
		}else{
			throw DecodeException("TODO: Array references not supported");
		}
	}

	/*
	AMF3_OBJECT
	*/
	Object::Object()
		: Entity(Type, AMF3)
	{
	}

	Object::Object(const std::string& name)
		: Entity(Type, AMF3), mName(name)
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

		obj << "{ object " << mName << std::endl;
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

	void Object::serialize(ByteStream& stream) const {
		Entity::serialize(stream);
		ExternalDefinition* ext = ExternalDefinition::find(mName);

		uint32 ref = 0;
		ref |= 1;//Not an object reference
		ref |= 1 << 1;//Not a class definition reference
		ref |= (ext ? 1 : 0) << 2;
		ref |= (mDynamicMembers.size() > 0 ? 1 : 0) << 3;
		ref |= mStaticValues.size() << 4;

		Integer::serialize(ref, stream);
		String::serialize(mName, stream);

		if(ext)
			throw new EncodeException("TODO: add serialize of external classes");

		for(auto itr = mStaticValues.begin(); itr != mStaticValues.end(); ++itr)
			String::serialize(itr->first, stream);

		for(auto itr = mStaticValues.begin(); itr != mStaticValues.end(); ++itr)
			itr->second->serialize(stream);
			
		for(auto itr = mDynamicMembers.begin(); itr != mDynamicMembers.end(); ++itr){
			String::serialize(itr->first, stream);
			itr->second->serialize(stream);
		}
	}

	void Object::deserialize(ByteStream& stream){
		Entity::deserialize(stream);

		uint32 ref;
		Integer::deserialize(ref, stream);
		if(ref & 1){
			ref >>= 1;

			ClassDefinition* def = NULL;
			if(ref & 1){
				ref >>= 1;

				def = new ClassDefinition();
				String::deserialize(def->mTypename, stream);
				def->mExternalizable = (ref & 1) != 0;
				def->mDynamic = ((ref >> 1) & 1) != 0;
					
				uint32 members = ref >> 2;
				for(uint32 i = 0; i < members; ++i){
					std::string tmp;
					String::deserialize(tmp, stream);
					def->mMembers.push_back(tmp);
				}
				
				ReferenceTables::ClassDefinitions.add(def);
			}else{
				def = ReferenceTables::ClassDefinitions.get(ref >> 1);
			}

			if(!def)
				throw DecodeException("Object class definition '%s' not found", def->mTypename);
			
			mName = def->mTypename;

			if(def->mExternalizable){
				ExternalDefinition* extDef = ExternalDefinition::find(def->mTypename);

				if(!extDef)
					throw DecodeException("Externalizable class '%s' not found", def->mTypename);

				extDef->read(this, stream);
			}else{
				for(auto itr = def->mMembers.begin(); itr != def->mMembers.end(); ++itr)
					mStaticValues[*itr] = Entity::read(stream);
			}

			if(def->mDynamic){
				while(true){
					std::string key;
					String::deserialize(key, stream);
					if(key.length() == 0) break;
					
					mDynamicMembers[key] = Entity::read(stream);
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

	void Xml::serialize(ByteStream& stream) const {
		Entity::serialize(stream);

		Integer::serialize((mValue.length() << 1) | 1, stream);
		stream.write(mValue.c_str(), mValue.length());
	}

	void Xml::deserialize(ByteStream& stream){
		Entity::deserialize(stream);

		uint32 length;
		Integer::deserialize(length, stream);
		if(length & 1){
			length >>= 1;
			mValue.assign((char*)stream.data() + stream.tell(), length);
			stream.skip(length);
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

	void ByteArray::serialize(ByteStream& stream) const {
		Entity::serialize(stream);

		Integer::serialize((mLength << 1) | 1, stream);
		stream.write(mValue, mLength);
	}

	void ByteArray::deserialize(ByteStream& stream){
		Entity::deserialize(stream);

		Integer::deserialize(mLength, stream);
		if(mLength & 1){
			mLength >>= 1;
			mValue = new uint8[mLength];
			memcpy(mValue, (char*)stream.data() + stream.tell(), mLength);
			stream.skip(mLength);
		}else{
			throw new DecodeException("TODO: Byte Array references are unsupported"); 
		}
	}
};
