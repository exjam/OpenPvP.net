#pragma once

#include "amf.h"
#include "rtmp/types.h"

#include <map>
#include <vector>
#include <string>

namespace amf3 {
	using amf::AMF3;
	using amf::Entity;
	using amf::EncodeException;
	using amf::DecodeException;
	namespace log = amf::log;

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
		AMF3_AVMPLUS = 17,
		AMF3_BOOLEAN = 0xFE,
		AMF3_INVALID = 0xFF,
	} DataTypes;

	class Undefined : public Entity {
	public:
		static const int Type = AMF3_UNDEFINED;

		Undefined();

		virtual std::string toString() const;
	};

	class Null : public Entity {
	public:
		static const int Type = AMF3_NULL;

		Null();

		virtual std::string toString() const;
	};

	class Boolean : public Entity {
	public:
		static const int Type = AMF3_BOOLEAN;

		Boolean(bool value = false);

		virtual std::string toString() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);
		
		bool value() const { return mValue; }

	private:
		bool mValue;
	};

	struct Integer : public Entity {
	public:
		static const int Type = AMF3_INTEGER;

		Integer(int32 value = 0);

		virtual std::string toString() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);
		
		static void serialize(int32 value, ByteStream& stream);
		static void deserialize(uint32& value, ByteStream& stream);
		static void deserialize(int32& value, ByteStream& stream);

		int32 value() const { return mValue; }

	private:
		int32 mValue;
	};

	class Double : public Entity {
	public:
		static const int Type = AMF3_DOUBLE;

		Double(double value = 0.0);
		
		virtual std::string toString() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);

		static void serialize(double value, ByteStream& stream);
		static void deserialize(double& value, ByteStream& stream);

		double value() const { return mValue; }

	private:
		double mValue;
	};

	class String : public Entity {
	public:
		static const int Type = AMF3_STRING;

		String();
		String(const std::string& value);

		virtual std::string toString() const;
	
		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);

		static void deserialize(std::string& str, ByteStream& stream);
		static void serialize(const std::string& str, ByteStream& stream);
		
		const std::string& value() const { return mValue; }

	private:
		std::string mValue;
	};

	class XmlDocument : public Entity {
	public:
		static const int Type = AMF3_XML_DOC;

		XmlDocument();
		XmlDocument(const std::string& value);
		
		virtual std::string toString() const;
	
		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);
		
		const std::string& value() const { return mValue; }

	private:
		std::string mValue;
	};

	class Date : public Entity {
	public:
		static const int Type = AMF3_DATE;

		Date();
		Date(double value);
		
		virtual std::string toString() const;
	
		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);
		
		double value() const { return mValue; }

	private:
		double mValue;
	};

	class Array : public amf::Object {
	public:
		static const int Type = AMF3_ARRAY;

		Array();
		~Array();

		virtual std::string toString() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);

		virtual void setProperty(const std::string& key, Entity* value){
			mAssociative[key] = value;
		}

		virtual Entity* getProperty(const std::string& key){
			auto itr = mAssociative.find(key);
			if(itr == mAssociative.end()) return nullptr;
			return itr->second;
		}

		virtual void setProperty(uint32 key, Entity* value){
			while(key >= mDense.size())
				mDense.push_back(nullptr);

			mDense[key] = value;
		}

		virtual Entity* getProperty(uint32 key){
			if(key > mDense.size()) return nullptr;
			return mDense[key];
		}

	private:
		std::vector<Entity*> mDense;
		std::map<std::string, Entity*> mAssociative;
	};

	class ClassDefinition {
	public:
		ClassDefinition();

		std::string mTypename;
		bool mDynamic;
		bool mExternalizable;
		std::vector<std::string> mMembers;
	};

	class ExternalDefinition {
	public:
		ExternalDefinition(const std::string& name, bool useFlags = true);
	
		uint32 readFlags(std::vector<uint8>& flags, ByteStream& stream);
		void read(class Object* obj, ByteStream& stream);

		void addField(const std::string& name);
		void setParent(ExternalDefinition* parent);

		static void add(ExternalDefinition* definition);
		static void alias(const std::string& name, ExternalDefinition* definition);

		static ExternalDefinition* find(const std::string& name);

	private:
		bool mUsesFlags;
		std::string mName;
		ExternalDefinition* mParent;
		std::vector<std::string> mFields;
		static std::map<std::string, ExternalDefinition*> mDefinitions;
	};

	class Object : public amf::Object {
	public:
		static const int Type = AMF3_OBJECT;

		Object();
		Object(const std::string& name);
		~Object();
		
		virtual std::string toString() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);

		virtual void setProperty(const std::string& key, Entity* value){
			if(mStaticValues.find(key) != mStaticValues.end()){
				delete mStaticValues[key];
				mStaticValues[key] = value;
			}else{
				if(mDynamicMembers.find(key) != mDynamicMembers.end())
					delete mDynamicMembers[key];

				mDynamicMembers[key] = value;
			}
		}

		virtual Entity* getProperty(const std::string& key){
			auto itr = mStaticValues.find(key);
			if(itr == mStaticValues.end()){
				itr = mDynamicMembers.find(key);
				if(itr == mDynamicMembers.end())
					return nullptr;
			}

			return itr->second;
		}

	private:
		std::string mName;
		std::map<std::string, Entity*> mStaticValues;
		std::map<std::string, Entity*> mDynamicMembers;
	};

	class Xml : public Entity {
	public:
		static const int Type = AMF3_XML;

		Xml();

		virtual std::string toString() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);
		
		const std::string& value() const { return mValue; }

	private:
		std::string mValue;
	};

	class ByteArray : public Entity {
	public:
		static const int Type = AMF3_BYTE_ARRAY;

		ByteArray();
		~ByteArray();

		virtual std::string toString() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);
		
		uint32 length() const { return mLength; }
		uint8* value() const { return mValue; }

	private:
		uint32 mLength;
		uint8* mValue;
	};

	template<typename T>
	class ReferenceTable {
	public:
		ReferenceTable(){}
		~ReferenceTable(){}

		void reset(){
			mTable.clear();
		}

		T get(uint32 ref){
			if(ref >= mTable.size())
				throw new DecodeException("Invalid reference index");

			return mTable[ref];
		}

		void add(const T& value){
			mTable.push_back(value);
		}

		std::vector<T> mTable;
	};

	struct ReferenceTables {
		static ReferenceTable<std::string> Strings;
		static ReferenceTable<Entity*> Objects;
		static ReferenceTable<class ClassDefinition*> ClassDefinitions;
	};
};
