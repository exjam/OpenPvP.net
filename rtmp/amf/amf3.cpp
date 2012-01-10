#include "amf.h"
#include "amf3.h"
#include <assert.h>
#include <algorithm>

namespace amf3 {
	using namespace amf;

	std::vector<std::string> ReferenceTable::mStrings;
	std::vector<ObjectDefinition*> ReferenceTable::mObjectDefinitions;
	std::map<std::string, ExternalisedObjectDefinition*> ReferenceTable::mExternalisedObjectDefinitions;
		
	
	void ReferenceTable::startGroup(){
		mStrings.clear();

		for(auto itr = mObjectDefinitions.begin(); itr != mObjectDefinitions.end(); ++itr)
			delete *itr;

		mObjectDefinitions.clear();
	}

	void ReferenceTable::addString(const std::string& value){
		mStrings.push_back(value);
	}

	std::string ReferenceTable::getString(size_t index){
		if(index >= mStrings.size())
			return nullptr;

		return mStrings[index];
	}
			
	ObjectDefinition* ReferenceTable::getObjectDefinition(size_t index){
		if(index >= mObjectDefinitions.size())
			return nullptr;

		return mObjectDefinitions[index];
	}
		
	ObjectDefinition* ReferenceTable::getObjectDefinitionByName(const std::string& name){
		for(auto itr = mObjectDefinitions.begin(); itr != mObjectDefinitions.end(); ++itr){
			if((*itr)->mName.compare(name) == 0)
				return *itr;
		}

		return nullptr;
	}
		
	void ReferenceTable::addObjectDefinition(ObjectDefinition* definition){
		mObjectDefinitions.push_back(definition);
	}
			
	ExternalisedObjectDefinition* ReferenceTable::getExternalisedObjectDefinition(const std::string& key){
		auto itr = mExternalisedObjectDefinitions.find(key);
		if(itr == mExternalisedObjectDefinitions.end())
			return nullptr;

		return itr->second;
	}

	void ReferenceTable::addExternalisedObjectDefinition(const std::string& key, ExternalisedObjectDefinition* definition){
		mExternalisedObjectDefinitions[key] = definition;
	}

	ExternalisedObjectDefinition::ExternalisedObjectDefinition(const std::string& name, bool useFlags)
		: mParent(nullptr), mName(name), mUsesFlags(useFlags)
	{
	}
	
	uint32 ExternalisedObjectDefinition::readFlags(std::vector<uint8>& flags, ByteStream& stream){
		uint8 flag;
		uint32 count = 0;
		do {
			stream >> flag;
			flags.push_back(flag);
		} while(flag & 0x80);

		return count;
	}
	
	void ExternalisedObjectDefinition::read(Object* obj, ByteStream& stream){
		if(mParent)
			mParent->read(obj, stream);

		if(mUsesFlags){
			std::vector<uint8> flags;
			readFlags(flags, stream);

			for(uint32 i = 0; i < flags.size(); ++i){
				uint8 byte = flags[i];

				for(uint32 j = 0; j < 7; ++j){
					uint32 index = i*7 + j;
					if((byte >> j) & 1){
						Variant* entity = amf::deserialise(stream);
						if(index >= mFields.size())
							delete entity;
						else
							obj->insert(mFields[i*7 + j], entity);
					}
				}
			}
		}else{
			for(auto itr = mFields.begin(); itr != mFields.end(); ++itr)
				obj->insert(*itr, amf::deserialise(stream));
		}
	}

	std::string ExternalisedObjectDefinition::name() const {
		return mName;
	}

	void ExternalisedObjectDefinition::addField(const std::string& name){
		mFields.push_back(name);
	}

	void ExternalisedObjectDefinition::setParent(ExternalisedObjectDefinition* parent){
		mParent = parent;
	}

	struct init {
		init(){
			const char* abstractMessageFields[] = {
				"body", "clientId", "destination", "headers", "messageId", "timestamp",
				"timeToLive", "clientIdBytes", "messageIdBytes", NULL
			};

			const char* asyncMessageFields[] = {
				"correlationId", "correlationIdBytes", NULL
			};

			const char* commandMessageFields[] = {
				"operation", NULL
			};

			const char* arrayCollectionFields[] = {
				"source", NULL
			};

			ExternalisedObjectDefinition* abstractMessage = new ExternalisedObjectDefinition("flex.messaging.messages.AbstractMessage");
			for(const char** ptr = abstractMessageFields; *ptr; ++ptr)
				abstractMessage->addField(*ptr);

			ExternalisedObjectDefinition* asyncMessageExt = new ExternalisedObjectDefinition("flex.messaging.messages.AsyncMessageExt");
			asyncMessageExt->setParent(abstractMessage);
			for(const char** ptr = asyncMessageFields; *ptr; ++ptr)
				asyncMessageExt->addField(*ptr);

			ExternalisedObjectDefinition* acknowledgeMessageExt = new ExternalisedObjectDefinition("flex.messaging.messages.AcknowledgeMessageExt");
			acknowledgeMessageExt->setParent(asyncMessageExt);

			ExternalisedObjectDefinition* commandMessageExt = new ExternalisedObjectDefinition("flex.messaging.messages.CommandMessageExt");
			commandMessageExt->setParent(asyncMessageExt);
			for(const char** ptr = commandMessageFields; *ptr; ++ptr)
				commandMessageExt->addField(*ptr);

			ExternalisedObjectDefinition* arrayCollectionExt = new ExternalisedObjectDefinition("flex.messaging.io.ArrayCollection", false);
			for(const char** ptr = arrayCollectionFields; *ptr; ++ptr)
				arrayCollectionExt->addField(*ptr);

			ReferenceTable::addExternalisedObjectDefinition(abstractMessage->name(), abstractMessage);
			ReferenceTable::addExternalisedObjectDefinition(asyncMessageExt->name(), asyncMessageExt);
			ReferenceTable::addExternalisedObjectDefinition(acknowledgeMessageExt->name(), acknowledgeMessageExt);
			ReferenceTable::addExternalisedObjectDefinition(commandMessageExt->name(), commandMessageExt);
			ReferenceTable::addExternalisedObjectDefinition(arrayCollectionExt->name(), arrayCollectionExt);

			ReferenceTable::addExternalisedObjectDefinition("DSA", asyncMessageExt);
			ReferenceTable::addExternalisedObjectDefinition("DSK", acknowledgeMessageExt);
			ReferenceTable::addExternalisedObjectDefinition("DSC", commandMessageExt);
		}
	} amf3init;

	void serialise(uint8 version, Variant* value, ByteStream& stream){
		assert(version == 3);

		uint8 type = value ? value->type() : AMF_NULL;
		switch(type){
			case AMF_NULL:
				serialise(AMF3_INVALID, (Null*)value, stream);
				break;
			case AMF_NUMBER:
				serialise(AMF3_INVALID, (Number*)value, stream);
				break;
			case AMF_INTEGER:
				serialise(AMF3_INVALID, (Integer*)value, stream);
				break;
			case AMF_BOOLEAN:
				serialise(AMF3_INVALID, (Boolean*)value, stream);
				break;
			case AMF_STRING:
				serialise(AMF3_INVALID, (String*)value, stream);
				break;
			case AMF_DATE:
				serialise(AMF3_INVALID, (Date*)value, stream);
				break;
			case AMF_ARRAY:
				serialise(AMF3_INVALID, (Array*)value, stream);
				break;
			case AMF_BYTE_ARRAY:
				serialise(AMF3_INVALID, (ByteArray*)value, stream);
				break;
			case AMF_OBJECT:
				serialise(AMF3_INVALID, (Object*)value, stream);
				break;
			default:
				throw new EncodeException("Invalid AMF data type %u", type);
				break;
		}
	}
		
	void serialise(uint8 type, Null* value, ByteStream& stream){
		assert(type == AMF3_INVALID);

		stream << uint8(AMF3_NULL);
	}

	void serialise(uint8 type, Number* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_DOUBLE);

		if(type == AMF3_INVALID)
			stream << uint8(AMF3_DOUBLE);

		stream << double(value->value());
	}

	void serialise(uint8 type, Integer* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_INTEGER);
			
		if(type == AMF3_INTEGER)
			stream << uint8(AMF3_INTEGER);
			
		uint32 tmp = value->value();

		if(value < 0)
			tmp = (1 << 29) + value->value();

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

	void serialise(uint8 type, Boolean* value, ByteStream& stream){
		assert(type == AMF3_INVALID);
		stream << uint8(value->value() ? AMF3_TRUE : AMF3_FALSE);
	}

	void serialise(uint8 type, String* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_STRING);

		if(type == AMF3_INVALID)
			stream << uint8(AMF3_STRING);
			
		const std::string& str = value->value();
		serialise(AMF3_INTEGER, &Integer((str.length() << 1) | 1), stream);
		stream.write(str.c_str(), str.length());
	}

	void serialise(uint8 type, Date* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_DATE);
			
		if(type == AMF3_DATE)
			stream << uint8(AMF3_DATE);

		stream << double(value->value());
	}

	void serialise(uint8 type, Array* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_ARRAY);

		if(type == AMF3_INVALID)
			stream << uint8(AMF3_ARRAY);
			
		serialise(AMF3_INTEGER, &Integer((value->keys() << 1) | 1), stream);

		for(auto itr = value->begin(); itr != value->end(); ++itr){
			serialise(AMF3_STRING, &String(itr->first), stream);
			serialise(itr->second, stream);
		}

		serialise(AMF3_STRING, &String(""), stream);

		for(size_t i = 0; i < value->size(); ++i)
			serialise(value->at(i), stream);
	}

	void serialise(uint8 type, ByteArray* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_BYTE_ARRAY);
			
		if(type == AMF3_INVALID)
			stream << uint8(AMF3_BYTE_ARRAY);

		serialise(AMF3_INTEGER, &Integer((value->size() << 1) | 1), stream);
		stream.write((const char*)value->value(), value->size());
	}

	void serialise(uint8 type, Object* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_OBJECT);
			
		if(type == AMF3_INVALID)
			stream << uint8(AMF3_OBJECT);
			
		ObjectDefinition* definition = ReferenceTable::getObjectDefinitionByName(value->name());
		ExternalisedObjectDefinition* extDef = ReferenceTable::getExternalisedObjectDefinition(value->name());
			
		uint32 dynamics = 0;
		uint32 statics = 0;

		for(auto itr = value->begin(); itr != value->end(); ++itr){
			if(definition){
				auto find = std::find(definition->mMembers.begin(), definition->mMembers.end(), itr->first);
				if(find != definition->mMembers.end()){
					++statics;
					continue;
				}
			}
				
			++dynamics;
		}

		uint32 ref = 0;
		ref |= 1;
		ref |= 1 << 1;
		ref |= (extDef ? 1 : 0) << 2;
		ref |= (dynamics > 0 ? 1 : 0) << 3;
		ref |= statics << 4;

		if(extDef)
			throw new EncodeException("Serialisation of external data types not yet supported");
			
		if(definition){
			for(auto itr = definition->mMembers.begin(); itr != definition->mMembers.end(); ++itr)
				serialise(AMF3_STRING, &String(*itr), stream);
			
			for(auto itr = definition->mMembers.begin(); itr != definition->mMembers.end(); ++itr)
				serialise(value->get(*itr), stream);
		}

		for(auto itr = value->begin(); itr != value->end(); ++itr){
			if(definition){
				auto find = std::find(definition->mMembers.begin(), definition->mMembers.end(), itr->first);
				if(find != definition->mMembers.end())
					continue;
			}
				
			serialise(AMF3_STRING, &String(itr->first), stream);
			serialise(itr->second, stream);
		}
	}
		
	Variant* deserialise(uint8 version, ByteStream& stream){
		assert(version == 3);

		uint8 type;
		stream >> type;

		Variant* value = nullptr;

		switch(type){
		case AMF3_NULL:
		case AMF3_UNDEFINED:
			value = new Null();
			deserialise(type, (Null*)value, stream);
			break;
		case AMF3_TRUE:
		case AMF3_FALSE:
			value = new Boolean();
			deserialise(type, (Boolean*)value, stream);
			break;
		case AMF3_INTEGER:
			value = new Integer();
			deserialise(type, (Integer*)value, stream);
			break;
		case AMF3_DOUBLE:
			value = new Number();
			deserialise(type, (Number*)value, stream);
			break;
		case AMF3_XML:
		case AMF3_XML_DOC:
		case AMF3_STRING:
			value = new String();
			deserialise(type, (String*)value, stream);
			break;
		case AMF3_DATE:
			value = new Date();
			deserialise(type, (Date*)value, stream);
			break;
		case AMF3_ARRAY:
			value = new Array();
			deserialise(type, (Array*)value, stream);
			break;
		case AMF3_OBJECT:
			value = new Object();
			deserialise(type, (Object*)value, stream);
			break;
		case AMF3_BYTE_ARRAY:
			value = new ByteArray();
			deserialise(type, (ByteArray*)value, stream);
			break;
		};

		return value;
	}
		
	void deserialise(uint8 type, Null* value, ByteStream& stream){
		assert(type == AMF3_NULL || type == AMF3_UNDEFINED);
	}

	void deserialise(uint8 type, Number* value, ByteStream& stream){
		assert(type == AMF3_DOUBLE);

		stream >> value->value();
	}

	void deserialise(uint8 type, Integer* value, ByteStream& stream){
		assert(type == AMF3_INTEGER);

		int32 tmp = 0;
		uint8 byte = 0x80;
		for(int i = 0; i < 4 && byte & 0x80; ++i){
			stream >> byte;
			if(i < 3){
				tmp <<= 7;
				tmp |= byte & 0x7F;
			}else{
				tmp = (tmp << 8) | byte;
			}
		}

		if(tmp & 0x10000000)
			tmp |= ~0x1fffffff;

		value->setValue(tmp);
	}

	void deserialise(uint8 type, Boolean* value, ByteStream& stream){
		assert(type == AMF3_TRUE || type == AMF3_FALSE);
		value->setValue(type == AMF3_TRUE);
	}

	void deserialise(uint8 type, String* value, ByteStream& stream){
		assert(type == AMF3_STRING || type == AMF3_XML || type == AMF3_XML_DOC);

		Integer size;
		deserialise(AMF3_INTEGER, &size, stream);
			
		uint32 length = size;
		if((length & 1) == 0){
			value->setValue(ReferenceTable::getString(length >> 1));
		}else{
			length >>= 1;
			value->value().assign((char*)stream.data() + stream.tell(), length);
			stream.skip(length);

			ReferenceTable::addString(value->value());
		}
	}

	void deserialise(uint8 type, Date* value, ByteStream& stream){
		assert(type == AMF3_DATE);

		stream >> value->value();
	}

	void deserialise(uint8 type, ByteArray* value, ByteStream& stream){
		assert(type == AMF3_BYTE_ARRAY);
		
		Integer _int;
		deserialise(AMF3_INTEGER, &_int, stream);

		uint32 length = _int;
		if((length & 1) == 0){//reference
			throw new DecodeException("ByteArray references not yet supported");
		}else{
			length >>= 1;
			value->setSize(length);
			stream.read((char*)value->value(), length);
		}
	}

	void deserialise(uint8 type, Array* value, ByteStream& stream){
		assert(type == AMF3_ARRAY);

		Integer _int;
		deserialise(AMF3_INTEGER, &_int, stream);
			
		uint32 length = _int;
		if((length & 1) == 0){//reference
			throw new DecodeException("Array references not yet supported");
		}else{
			length >>= 1;

			while(true){
				String _string;
				deserialise(AMF3_STRING, &_string, stream);
					
				if(_string.length() == 0)
					break;

				value->insert(_string, amf::deserialise(stream));
			}

			for(uint32 i = 0; i < length; ++i)
				value->push_back(amf::deserialise(stream));
		}
	}

	void deserialise(uint8 type, Object* value, ByteStream& stream){
		assert(type == AMF3_OBJECT);
			
		String _string;
		Integer _int;
		deserialise(AMF3_INTEGER, &_int, stream);
			
		uint32 ref = _int;
		if((ref & 1) == 0){//reference
			throw new DecodeException("Object references not yet supported");
		}else{
			ref >>= 1;

			ObjectDefinition* definition = nullptr;
			if((ref & 1) == 0){
				definition = ReferenceTable::getObjectDefinition(ref >> 1);
			}else{
				ref >>= 1;

				deserialise(AMF3_STRING, &_string, stream);

				definition = new ObjectDefinition();
				definition->mTemporary = true;
				definition->mName = _string;
				definition->mDynamic = (ref & 2) != 0;
				definition->mExternalisable = (ref & 1) != 0;
					
				uint32 members = ref >> 2;
				for(uint32 i = 0; i < members; ++i){
					deserialise(AMF3_STRING, &_string, stream);
					definition->mMembers.push_back(_string);
				}

				ReferenceTable::addObjectDefinition(definition);
			}

			if(!definition)
				throw new DecodeException("Definition for object not found");

			value->setName(definition->mName);

			if(definition->mExternalisable){
				ExternalisedObjectDefinition* extDef = ReferenceTable::getExternalisedObjectDefinition(value->name());

				if(!extDef)
					throw new DecodeException("Externalised Definition for object %s not found", value->name());

				extDef->read(value, stream);
			}else{
				for(auto itr = definition->mMembers.begin(); itr != definition->mMembers.end(); ++itr)
					value->insert(*itr, amf::deserialise(stream));
			}

			if(definition->mDynamic){
				while(true){
					deserialise(AMF3_STRING, &_string, stream);
					if(_string.length() == 0) break;
					
					value->insert(_string, amf::deserialise(stream));
				}
			}
		}
	}
};