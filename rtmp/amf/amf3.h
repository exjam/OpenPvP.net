#pragma once

#include "amf.h"
#include <map>

namespace amf3 {
	using namespace amf;

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

	struct ObjectDefinition {
		bool mDynamic;
		bool mTemporary;
		bool mExternalisable;
		std::string mName;
		std::vector<std::string> mMembers;
	};

	class ExternalisedObjectDefinition {
	public:
		ExternalisedObjectDefinition(const std::string& name, bool useFlags = true);
	
		uint32 readFlags(std::vector<uint8>& flags, ByteStream& stream);
		void read(class Object* obj, ByteStream& stream);

		void addField(const std::string& name);
		void setParent(ExternalisedObjectDefinition* parent);

		std::string name() const;

	private:
		bool mUsesFlags;
		std::string mName;
		ExternalisedObjectDefinition* mParent;
		std::vector<std::string> mFields;
	};
		
	class ReferenceTable {
	public:
		static void startGroup();

		static void addString(const std::string& value);
		static std::string getString(size_t index);

		static ObjectDefinition* getObjectDefinition(size_t index);
		static ObjectDefinition* getObjectDefinitionByName(const std::string& name);
		static void addObjectDefinition(ObjectDefinition* definition);

		static ExternalisedObjectDefinition* getExternalisedObjectDefinition(const std::string& key);
		static void addExternalisedObjectDefinition(const std::string& key, ExternalisedObjectDefinition* definition);
			
	private:
		static std::vector<std::string> mStrings;
		static std::vector<ObjectDefinition*> mObjectDefinitions;
		static std::map<std::string, ExternalisedObjectDefinition*> mExternalisedObjectDefinitions;
	};
		
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
};
