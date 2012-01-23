#pragma once

#include "amf.h"
#include "flex/iexternalizable.h"

#include <map>
#include <vector>

namespace amf {
	struct ObjectDefinition {
		bool mDynamic;
		bool mTemporary;
		bool mExternalisable;
		std::string mName;
		std::vector<std::string> mMembers;
	};

	class ExternalisedDefinition : public flex::utils::IExternalizable {
	public:
		ExternalisedDefinition(const std::string& name, bool useFlags = true);

		std::string name() const;
		void readExternal(amf::Object* object, ByteStream& stream);
		void writeExternal(amf::Object* object, ByteStream& stream);
		
		void addField(const std::string& name);
		void setParent(ExternalisedDefinition* parent);
	
	private:
		uint32 readFlags(std::vector<uint8>& flags, ByteStream& stream);

	private:
		bool mUsesFlags;
		std::string mName;
		ExternalisedDefinition* mParent;
		std::vector<std::string> mFields;
	};
		
	class amf3 : public EncoderImpl {
	public:
		typedef enum {
			AMF3_UNDEFINED = 0,
			AMF3_NULL,
			AMF3_FALSE,
			AMF3_TRUE,
			AMF3_INTEGER,
			AMF3_DOUBLE,
			AMF3_STRING,
			AMF3_XML_DOC,
			AMF3_DATE,
			AMF3_ARRAY,
			AMF3_OBJECT,
			AMF3_XML,
			AMF3_BYTE_ARRAY,
			AMF3_INVALID = 0xFF,
		} DataTypes;

		amf3();

		void start();
		void end();
		
		void defineObject(Object* object);
		void addExternalizable(flex::utils::IExternalizable* externalizable);

		void serialise(uint8 version, Variant* value, ByteStream& stream);
		void serialise(uint8 type, Null* value, ByteStream& stream);
		void serialise(uint8 type, Number* value, ByteStream& stream);
		void serialise(uint8 type, Integer* number, ByteStream& stream);
		void serialise(uint8 type, Boolean* value, ByteStream& stream);
		void serialise(uint8 type, String* value, ByteStream& stream);
		void serialise(uint8 type, Date* value, ByteStream& stream);
		void serialise(uint8 type, Array* value, ByteStream& stream);
		void serialise(uint8 type, ByteArray* value, ByteStream& stream);
		void serialise(uint8 type, Object* value, ByteStream& stream);
		
		Variant* deserialise(uint8 version, ByteStream& stream);
		void deserialise(uint8 type, Null* value, ByteStream& stream);
		void deserialise(uint8 type, Number* value, ByteStream& stream);
		void deserialise(uint8 type, Integer* number, ByteStream& stream);
		void deserialise(uint8 type, Boolean* value, ByteStream& stream);
		void deserialise(uint8 type, String* value, ByteStream& stream);
		void deserialise(uint8 type, Date* value, ByteStream& stream);
		void deserialise(uint8 type, Array* value, ByteStream& stream);
		void deserialise(uint8 type, ByteArray* value, ByteStream& stream);
		void deserialise(uint8 type, Object* value, ByteStream& stream);

	private:
		void createDefaultDefinitions();
		void createDefaultExternalised();
		
		void addDefinition(ObjectDefinition* def);
		void addString(const std::string& str);
		void addObject(Variant* obj);
		void addExternalizable(const std::string& name, flex::utils::IExternalizable* def);

		std::string getString(uint32 index);
		Variant* getObject(uint32 index);
		ObjectDefinition* getDefinition(uint32 index);
		ObjectDefinition* getDefinition(const std::string& name);
		flex::utils::IExternalizable* getExternalizable(const std::string& name);

	private:
		std::vector<std::string> mStrings;
		std::vector<Variant*> mObjects;
		std::vector<ObjectDefinition*> mDefinitions;
		std::vector<ObjectDefinition*> mPermanentDefinitions;
		std::map<std::string, flex::utils::IExternalizable*> mExternalizables;
	};
};
