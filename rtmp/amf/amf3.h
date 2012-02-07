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
		void readExternal(Encoder* encoder, amf::Object* object, ByteStream& stream);
		void writeExternal(Encoder* encoder, amf::Object* object, ByteStream& stream);
		
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
		
	class amf3 {
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

		amf3(Encoder* parent);
		~amf3();
		
		static void defineObject(Object* object);
		static void addExternalizable(flex::utils::IExternalizable* externalizable);

		void serialise(uint8 version, const Variant& value, ByteStream& stream);
		Variant deserialise(uint8 version, ByteStream& stream);

	private:
		void serialise(uint8 type, const Null* value, ByteStream& stream);
		void serialise(uint8 type, const Number* value, ByteStream& stream);
		void serialise(uint8 type, const Integer* number, ByteStream& stream);
		void serialise(uint8 type, const Boolean* value, ByteStream& stream);
		void serialise(uint8 type, const String* value, ByteStream& stream);
		void serialise(uint8 type, const Date* value, ByteStream& stream);
		void serialise(uint8 type, const Array* value, ByteStream& stream);
		void serialise(uint8 type, const ByteArray* value, ByteStream& stream);
		void serialise(uint8 type, const Object* value, ByteStream& stream);

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
		static void createDefaultExternalised();
		static void addExternalizable(const std::string& name, flex::utils::IExternalizable* def);
		static flex::utils::IExternalizable* getExternalizable(const std::string& name);
		
		static void addPermanentDefinition(ObjectDefinition* def);
		static ObjectDefinition* getPermanentDefinition(const std::string& name);
		
		void addDefinition(ObjectDefinition* def);
		void addString(const std::string& str);
		void addObject(const Variant& obj);

		std::string getString(uint32 index);
		const Variant& getObject(uint32 index);
		ObjectDefinition* getDefinition(uint32 index);
		ObjectDefinition* getDefinition(const std::string& name);

	private:
		Encoder* mParent;
		std::vector<std::string> mStrings;
		std::vector<Variant> mObjects;
		std::vector<ObjectDefinition*> mDefinitions;
		
		static std::vector<ObjectDefinition*> mPermanentDefinitions;
		static std::map<std::string, flex::utils::IExternalizable*> mExternalizables;
	};
};
