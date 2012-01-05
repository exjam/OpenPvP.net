#include "amf3.h"

namespace amf3 {
	ReferenceTable<std::string> ReferenceTables::Strings;
	ReferenceTable<Entity*> ReferenceTables::Objects;
	ReferenceTable<ClassDefinition*> ReferenceTables::ClassDefinitions;
	std::map<std::string, ExternalDefinition*> ExternalDefinition::mDefinitions;
	
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

			ExternalDefinition* abstractMessage = new ExternalDefinition("flex.messaging.messages.AbstractMessage");
			for(const char** ptr = abstractMessageFields; *ptr; ++ptr)
				abstractMessage->addField(*ptr);

			ExternalDefinition* asyncMessageExt = new ExternalDefinition("flex.messaging.messages.AsyncMessageExt");
			asyncMessageExt->setParent(abstractMessage);
			for(const char** ptr = asyncMessageFields; *ptr; ++ptr)
				asyncMessageExt->addField(*ptr);

			ExternalDefinition* acknowledgeMessageExt = new ExternalDefinition("flex.messaging.messages.AcknowledgeMessageExt");
			acknowledgeMessageExt->setParent(asyncMessageExt);

			ExternalDefinition* commandMessageExt = new ExternalDefinition("flex.messaging.messages.CommandMessageExt");
			commandMessageExt->setParent(asyncMessageExt);
			for(const char** ptr = commandMessageFields; *ptr; ++ptr)
				commandMessageExt->addField(*ptr);

			ExternalDefinition::add(abstractMessage);
			ExternalDefinition::add(asyncMessageExt);
			ExternalDefinition::add(acknowledgeMessageExt);
			ExternalDefinition::add(commandMessageExt);

			ExternalDefinition::alias("DSA", asyncMessageExt);
			ExternalDefinition::alias("DSK", acknowledgeMessageExt);
			ExternalDefinition::alias("DSC", commandMessageExt);
		}
	} amf3init;

	ClassDefinition::ClassDefinition()
		: mDynamic(false), mExternalizable(false)
	{
	}

	ExternalDefinition::ExternalDefinition(const std::string& name)
		: mParent(nullptr), mName(name)
	{
	}
	
	uint32 ExternalDefinition::readFlags(ByteStream& stream){
		uint8 flag;
		uint32 count = 0;
		do {
			stream >> flag;
			mFlags.push_back(flag);
		} while(flag & 0x80);

		return count;
	}
	
	void ExternalDefinition::read(class Object* obj, ByteStream& stream){
		if(mParent)
			mParent->read(obj, stream);

		readFlags(stream);

		for(uint32 i = 0; i < mFlags.size(); ++i){
			uint8 byte = mFlags[i];

			for(uint32 j = 0; j < 7; ++j){
				uint32 index = i*7 + j;
				if((byte >> j) & 1){
					Entity* entity = Entity::read(amf::AMF3, stream);
					if(index > mFields.size())
						delete entity;
					else
						obj->set(mFields[i*7 + j], entity);
				}
			}
		}
	}

	void ExternalDefinition::addField(const std::string& name){
		mFields.push_back(name);
	}

	void ExternalDefinition::setParent(ExternalDefinition* parent){
		mParent = parent;
	}

	void ExternalDefinition::add(ExternalDefinition* definition){
		mDefinitions[definition->mName] = definition;
	}

	void ExternalDefinition::alias(const std::string& name, ExternalDefinition* definition){
		mDefinitions[name] = definition;
	}

	ExternalDefinition* ExternalDefinition::find(const std::string& name){
		auto itr = mDefinitions.find(name);
		if(itr == mDefinitions.end())
			return nullptr;

		return itr->second;
	}
};
