#include "amf.h"
#include "amf3.h"
#include "variant.h"
#include "flex/messages.h"
#include "flex/iexternalizable.h"

#include <assert.h>
#include <algorithm>

namespace amf {
	ExternalisedDefinition::ExternalisedDefinition(const std::string& name, bool useFlags)
		: mParent(nullptr), mName(name), mUsesFlags(useFlags)
	{
	}
	
	uint32 ExternalisedDefinition::readFlags(std::vector<uint8>& flags, ByteStream& stream){
		uint8 flag;
		uint32 count = 0;
		do {
			stream >> flag;
			flags.push_back(flag);
		} while(flag & 0x80);

		return count;
	}
	
	void ExternalisedDefinition::readExternal(Object* obj, ByteStream& stream){
		if(mParent)
			mParent->readExternal(obj, stream);

		if(mUsesFlags){
			std::vector<uint8> flags;
			readFlags(flags, stream);

			for(uint32 i = 0; i < flags.size(); ++i){
				uint8 byte = flags[i];

				for(uint32 j = 0; j < 7; ++j){
					uint32 index = i*7 + j;
					if((byte >> j) & 1){
						Variant* entity = Encoder.deserialise(stream, false);
						if(index < mFields.size())
							obj->insert(mFields[i*7 + j], entity);
						else if(entity)
							delete entity;
					}
				}
			}
		}else{
			for(auto itr = mFields.begin(); itr != mFields.end(); ++itr)
				obj->insert(*itr, Encoder.deserialise(stream, false));
		}
	}

	void ExternalisedDefinition::writeExternal(amf::Object* object, ByteStream& stream){
	}

	std::string ExternalisedDefinition::name() const {
		return mName;
	}

	void ExternalisedDefinition::addField(const std::string& name){
		mFields.push_back(name);
	}

	void ExternalisedDefinition::setParent(ExternalisedDefinition* parent){
		mParent = parent;
	}

	void amf3::createDefaultExternalised(){
		const char* abstrf[] = {
			"body", "clientId", "destination", "headers", "messageId", "timestamp",
			"timeToLive", "clientIdBytes", "messageIdBytes", NULL
		};

		const char* asyncf[] = {
			"correlationId", "correlationIdBytes", NULL
		};

		const char* cmdf[] = {
			"operation", NULL
		};

		const char* arrf[] = {
			"source", NULL
		};

		auto abstr = new ExternalisedDefinition("flex.messaging.messages.AbstractMessage");
		for(auto ptr = abstrf; *ptr; ++ptr)
			abstr->addField(*ptr);

		auto async = new ExternalisedDefinition("flex.messaging.messages.AsyncMessageExt");
		async->setParent(abstr);
		for(auto ptr = asyncf; *ptr; ++ptr)
			async->addField(*ptr);

		auto cmd = new ExternalisedDefinition("flex.messaging.messages.CommandMessageExt");
		cmd->setParent(async);
		for(auto ptr = cmdf; *ptr; ++ptr)
			cmd->addField(*ptr);

		auto ack = new ExternalisedDefinition("flex.messaging.messages.AcknowledgeMessageExt");
		ack->setParent(async);

		auto arr = new ExternalisedDefinition("flex.messaging.io.ArrayCollection", false);
		for(auto ptr = arrf; *ptr; ++ptr)
			arr->addField(*ptr);

		addExternalizable(abstr);
		addExternalizable(async);
		addExternalizable(ack);
		addExternalizable(cmd);
		addExternalizable(arr);

		addExternalizable("DSA", async);
		addExternalizable("DSK", ack);
		addExternalizable("DSC", cmd);
	}

	amf3::amf3(){
		createDefaultExternalised();
	}

	void amf3::start(){
		mStrings.clear();
		mObjects.clear();

		for(auto itr = mDefinitions.begin(); itr != mDefinitions.end(); ){
			amf::ObjectDefinition* def = *itr;
			if(def->mTemporary){
				delete def;
				itr = mDefinitions.erase(itr);
			}else{
				++itr;
			}
		}
	}

	void amf3::end(){
	}

	void amf3::defineObject(Object* object){
		if(getDefinition(object->name()))
			return;

		ObjectDefinition* def = new ObjectDefinition();
		def->mName = object->name();
		def->mDynamic = true;
		def->mExternalisable = false;
		def->mTemporary = false;
		
		for(auto itr = object->begin(); itr != object->end(); ++itr)
			def->mMembers.push_back(itr->first);

		addDefinition(def);
	}

	void amf3::addString(const std::string& str){
		if(str.length() > 0)
			mStrings.push_back(str);
	}

	void amf3::addObject(Variant* obj){
		if(obj)
			mObjects.push_back(obj);
	}

	void amf3::addDefinition(ObjectDefinition* def){
		if(def->mTemporary)
			mDefinitions.push_back(def);
		else
			mPermanentDefinitions.push_back(def);
	}

	void amf3::addExternalizable(flex::utils::IExternalizable* def){
		mExternalizables[def->name()] = def;
	}

	void amf3::addExternalizable(const std::string& name, flex::utils::IExternalizable* def){
		mExternalizables[name] = def;
	}

	std::string amf3::getString(uint32 index){
		return mStrings.at(index);
	}

	Variant* amf3::getObject(uint32 index){
		return mObjects.at(index);
	}

	ObjectDefinition* amf3::getDefinition(uint32 index){
		return mDefinitions.at(index);
	}

	ObjectDefinition* amf3::getDefinition(const std::string& name){
		for(auto itr = mDefinitions.begin(); itr != mDefinitions.end(); ++itr){
			if((*itr)->mName.compare(name) == 0)
				return *itr;
		}

		for(auto itr = mPermanentDefinitions.begin(); itr != mPermanentDefinitions.end(); ++itr){
			if((*itr)->mName.compare(name) == 0)
				return *itr;
		}

		return nullptr;
	}

	flex::utils::IExternalizable* amf3::getExternalizable(const std::string& name){
		auto itr = mExternalizables.find(name);
		if(itr == mExternalizables.end())
			return nullptr;

		return itr->second;
	}

	void amf3::serialise(uint8 version, Variant* value, ByteStream& stream){
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
		
	void amf3::serialise(uint8 type, Null* value, ByteStream& stream){
		assert(type == AMF3_INVALID);

		stream << uint8(AMF3_NULL);
	}

	void amf3::serialise(uint8 type, Number* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_DOUBLE);

		if(type == AMF3_INVALID)
			stream << uint8(AMF3_DOUBLE);

		stream << double(value->value());
	}

	void amf3::serialise(uint8 type, Integer* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_INTEGER);
			
		if(type == AMF3_INVALID)
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

	void amf3::serialise(uint8 type, Boolean* value, ByteStream& stream){
		assert(type == AMF3_INVALID);
		stream << uint8(value->value() ? AMF3_TRUE : AMF3_FALSE);
	}

	void amf3::serialise(uint8 type, String* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_STRING);

		if(type == AMF3_INVALID)
			stream << uint8(AMF3_STRING);
			
		const std::string& str = value->value();
		int length = str.length();
		serialise(AMF3_INTEGER, &Integer((length << 1) | 1), stream);
		stream.write(str.c_str(), str.length());
	}

	void amf3::serialise(uint8 type, Date* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_DATE);
			
		if(type == AMF3_INVALID)
			stream << uint8(AMF3_DATE);
		
		//not a ref
		serialise(AMF3_INTEGER, &Integer(1), stream);

		stream << double(value->value());
	}

	void amf3::serialise(uint8 type, Array* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_ARRAY);

		if(type == AMF3_INVALID)
			stream << uint8(AMF3_ARRAY);
			
		serialise(AMF3_INTEGER, &Integer((value->size() << 1) | 1), stream);

		for(auto itr = value->begin(); itr != value->end(); ++itr){
			serialise(AMF3_STRING, &String(itr->first), stream);
			Encoder.serialise(itr->second, stream);
		}

		serialise(AMF3_STRING, &String(""), stream);

		for(size_t i = 0; i < value->size(); ++i)
			Encoder.serialise(value->at(i), stream);
	}

	void amf3::serialise(uint8 type, ByteArray* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_BYTE_ARRAY);
			
		if(type == AMF3_INVALID)
			stream << uint8(AMF3_BYTE_ARRAY);

		serialise(AMF3_INTEGER, &Integer((value->size() << 1) | 1), stream);
		stream.write((const char*)value->value(), value->size());
	}

	void amf3::serialise(uint8 type, Object* value, ByteStream& stream){
		assert(type == AMF3_INVALID || type == AMF3_OBJECT);
			
		if(type == AMF3_INVALID)
			stream << uint8(AMF3_OBJECT);
			
		ObjectDefinition* definition = getDefinition(value->name());
		flex::utils::IExternalizable* extDef = getExternalizable(value->name());
			
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

		extDef = 0;

		uint32 ref = 0;
		ref |= 1;//not ref'd
		ref |= 1 << 1;//not def ptr
		ref |= (extDef ? 1 : 0) << 2;
		ref |= (dynamics > 0 ? 1 : 0) << 3;
		ref |= statics << 4;

		if(extDef)
			throw new EncodeException("Serialisation of external data types not yet supported");
		
		serialise(AMF3_INTEGER, &amf::Integer(ref), stream);
		serialise(AMF3_STRING, &amf::String(value->name()), stream);

		if(definition){
			for(auto itr = definition->mMembers.begin(); itr != definition->mMembers.end(); ++itr)
				serialise(AMF3_STRING, &String(*itr), stream);
			
			for(auto itr = definition->mMembers.begin(); itr != definition->mMembers.end(); ++itr)
				Encoder.serialise(value->get(*itr), stream);
		}

		for(auto itr = value->begin(); itr != value->end(); ++itr){
			if(definition){
				auto find = std::find(definition->mMembers.begin(), definition->mMembers.end(), itr->first);
				if(find != definition->mMembers.end())
					continue;
			}
				
			serialise(AMF3_STRING, &String(itr->first), stream);
			Encoder.serialise(itr->second, stream);
		}

		if(dynamics > 0)
			serialise(AMF3_STRING, &String(""), stream);
	}
		
	Variant* amf3::deserialise(uint8 version, ByteStream& stream){
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
		
	void amf3::deserialise(uint8 type, Null* value, ByteStream& stream){
		assert(type == AMF3_NULL || type == AMF3_UNDEFINED);
	}

	void amf3::deserialise(uint8 type, Number* value, ByteStream& stream){
		assert(type == AMF3_DOUBLE);

		stream >> value->value();
	}

	void amf3::deserialise(uint8 type, Integer* value, ByteStream& stream){
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

	void amf3::deserialise(uint8 type, Boolean* value, ByteStream& stream){
		assert(type == AMF3_TRUE || type == AMF3_FALSE);
		value->setValue(type == AMF3_TRUE);
	}

	void amf3::deserialise(uint8 type, String* value, ByteStream& stream){
		assert(type == AMF3_STRING || type == AMF3_XML || type == AMF3_XML_DOC);

		Integer size;
		deserialise(AMF3_INTEGER, &size, stream);
			
		uint32 length = size;
		if((length & 1) == 0){
			if(type == AMF3_STRING){
				value->setValue(getString(length >> 1));
			}else{
				String* source = (String*)getObject(length >> 1);
				if(source->type() != value->type())
					throw new DecodeException("Referenced object was not of same type");

				value->setValue(value->value());
			}
		}else{
			length >>= 1;
			value->value().assign((char*)stream.data() + stream.tell(), length);
			stream.skip(length);

			if(type == AMF3_STRING)
				addString(value->value());
			else
				addObject(value);
		}
	}

	void amf3::deserialise(uint8 type, Date* value, ByteStream& stream){
		assert(type == AMF3_DATE);
		
		Integer _int;
		deserialise(AMF3_INTEGER, &_int, stream);

		uint32 length = _int;
		if((length & 1) == 0){
			Date* source = (Date*)getObject(length >> 1);
			if(source->type() != Date::Type)
				throw new DecodeException("Referenced object was not of type Date");

			value->setValue(source->value());
		}else{
			stream >> value->value();

			addObject(value);
		}
	}

	void amf3::deserialise(uint8 type, ByteArray* value, ByteStream& stream){
		assert(type == AMF3_BYTE_ARRAY);
		
		Integer _int;
		deserialise(AMF3_INTEGER, &_int, stream);

		uint32 length = _int;
		if((length & 1) == 0){
			ByteArray* source = (ByteArray*)getObject(length >> 1);
			if(source->type() != ByteArray::Type)
				throw new DecodeException("Referenced object was not of type ByteArray");

			value->setSize(source->size());
			memcpy(value->value(), source->value(), source->size());
		}else{
			length >>= 1;
			value->setSize(length);
			stream.read((char*)value->value(), length);

			addObject(value);
		}
	}

	void amf3::deserialise(uint8 type, Array* value, ByteStream& stream){
		assert(type == AMF3_ARRAY);

		Integer _int;
		deserialise(AMF3_INTEGER, &_int, stream);
			
		uint32 length = _int;
		if((length & 1) == 0){
			Array* source = (Array*)getObject(length >> 1);
			if(source->type() != Array::Type)
				throw new DecodeException("Referenced object was not of type Array");
			
			for(auto itr = source->begin(); itr != source->end(); ++itr)
				value->insert(itr->first, itr->second->copy());

			for(uint32 i = 0; i < source->size(); ++i)
				value->push_back(source->at(i)->copy());
		}else{
			addObject(value);

			length >>= 1;

			while(true){
				String _string;
				deserialise(AMF3_STRING, &_string, stream);
					
				if(_string.length() == 0)
					break;

				value->insert(_string, Encoder.deserialise(stream, false));
			}

			for(uint32 i = 0; i < length; ++i)
				value->push_back(Encoder.deserialise(stream, false));
		}
	}

	void amf3::deserialise(uint8 type, Object* value, ByteStream& stream){
		assert(type == AMF3_OBJECT);
			
		String _string;
		Integer _int;
		deserialise(AMF3_INTEGER, &_int, stream);
			
		uint32 ref = _int;
		if((ref & 1) == 0){
			Object* source = (Object*)getObject(ref >> 1);
			if(source->type() != Object::Type)
				throw new DecodeException("Referenced object was not of type Object");

			value->setName(source->name());

			for(auto itr = source->begin(); itr != source->end(); ++itr)
				value->insert(itr->first, itr->second->copy());
		}else{
			addObject(value);

			ref >>= 1;

			ObjectDefinition* definition = nullptr;
			if((ref & 1) == 0){
				definition = getDefinition(ref >> 1);
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

				addDefinition(definition);
			}

			if(!definition)
				throw new DecodeException("Definition for object not found");

			value->setName(definition->mName);

			if(definition->mExternalisable){
				flex::utils::IExternalizable* extDef = getExternalizable(value->name());

				if(!extDef)
					throw new DecodeException("Externalised Definition for object %s not found", value->name().c_str());

				extDef->readExternal(value, stream);
			}else{
				for(auto itr = definition->mMembers.begin(); itr != definition->mMembers.end(); ++itr)
					value->insert(*itr, Encoder.deserialise(stream, false));
			}

			if(definition->mDynamic){
				while(true){
					deserialise(AMF3_STRING, &_string, stream);
					if(_string.length() == 0) break;
					
					value->insert(_string, Encoder.deserialise(stream, false));
				}
			}
		}
	}
};