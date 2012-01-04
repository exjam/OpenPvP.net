#pragma once

#include "amf.h"
#include "rtmp/types.h"

#include <map>
#include <vector>
#include <string>

namespace amf0 {
	using namespace amf;

	typedef enum {
		AMF0_NUMBER = 0,
		AMF0_BOOLEAN,
		AMF0_STRING,
		AMF0_OBJECT,
		AMF0_MOVIECLIP,
		AMF0_NULL,
		AMF0_UNDEFINED,
		AMF0_REFERENCE,
		AMF0_ECMA_ARRAY,
		AMF0_OBJECT_END,
		AMF0_STRICT_ARRAY,
		AMF0_DATE,
		AMF0_LONG_STRING,
		AMF0_UNSUPPORTED,
		AMF0_RECORDSET,
		AMF0_XML_DOC,
		AMF0_TYPED_OBJECT,
		AMF0_AVMPLUS,
		AMF0_INVALID = 0xFF
	} DataTypes;

	class Number : public Entity {
	public:
		static const int Type = AMF0_NUMBER;

		Number(double value = 0.0);
		
		virtual std::string toString() const;
	
		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

		static void serialize(double value, Packet* pak);
		static void deserialize(double& value, Packet* pak);

	private:
		double mValue;
	};

	class Boolean : public Entity {
	public:
		static const int Type = AMF0_BOOLEAN;

		Boolean(bool value = false);
		
		virtual std::string toString() const;

		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

		static void serialize(bool value, Packet* pak);
		static void deserialize(bool& value, Packet* pak);

	private:
		bool mValue;
	};

	class Object : public Entity {
	public:
		static const int Type = AMF0_OBJECT;

		Object();
		~Object();

		virtual std::string toString() const;

		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

		template<typename T>
		void set(const std::string& key, T value){
			set(key, Entity::create(value));
		}

		template<>
		void set(const std::string& key, Entity* value){
			if(!value) return;
			mProperties[key] = value;
		}

	private:
		std::map<std::string, Entity*> mProperties;
	};

	class MovieClip : public Entity {
	public:
		static const int Type = AMF0_MOVIECLIP;

		MovieClip();

		virtual std::string toString() const;
	};

	class Null : public Entity {
	public:
		static const int Type = AMF0_NULL;

		Null();

		virtual std::string toString() const;
	};

	class Undefined : public Entity {
	public:
		static const int Type = AMF0_UNDEFINED;

		Undefined();

		virtual std::string toString() const;
	};

	class Reference : public Entity {
	public:
		static const int Type = AMF0_REFERENCE;

		Reference(uint16 value = 0);

		virtual std::string toString() const;
	
		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

	private:
		uint16 mValue;
	};

	class AssociativeArray : public Entity {
	public:
		static const int Type = AMF0_ECMA_ARRAY;

		AssociativeArray();
		~AssociativeArray();

		virtual std::string toString() const;
	
		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

		template<typename T>
		void add(const std::string& key, T value){
			add(key, Entity::create(value));
		}

		template<>
		void add(const std::string& key, Entity* value){
			if(!value) return;
			mEntries[key] = value;
		}

	private:
		std::map<std::string, Entity*> mEntries;
	};

	class ObjectEnd : public Entity {
	public:
		static const int Type = AMF0_OBJECT_END;

		ObjectEnd();
	};

	class StrictArray : public Entity {
	public:
		static const int Type = AMF0_STRICT_ARRAY;

		StrictArray();
		~StrictArray();

		virtual std::string toString() const;
	
		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

		template<typename T>
		void add(T value){
			add(Entity::create(value));
		}

		template<>
		void add(Entity* value){
			if(!value) return;
			mEntries.push_back(value);
		}

	private:
		std::vector<Entity*> mEntries;
	};

	class Date : public Entity {
	public:
		static const int Type = AMF0_DATE;

		Date(double value = 0.0, uint16 timezone = 0);

		virtual std::string toString() const;
	
		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

	private:
		double mValue;
		uint16 mTimeZone;
	};

	class Unsupported : public Entity {
	public:
		static const int Type = AMF0_UNSUPPORTED;

		Unsupported();

		virtual std::string toString() const;
	};

	class RecordSet : public Entity {
	public:
		static const int Type = AMF0_RECORDSET;

		RecordSet();

		virtual std::string toString() const;
	};

	class XmlDocument : public Entity {
	public:
		static const int Type = AMF0_XML_DOC;

		XmlDocument();
		XmlDocument(const std::string& value);

		virtual std::string toString() const;

		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

	private:
		std::string mValue;
	};

	class TypedObject : public Entity {
	public:
		static const int Type = AMF0_TYPED_OBJECT;

		TypedObject();
		TypedObject(const std::string& name);

		~TypedObject();

		virtual std::string toString() const;

		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);
		
		template<typename T>
		void set(const std::string& key, T value){
			setProperty(key, Entity::create(value));
		}

		template<>
		void set(const std::string& key, Entity* value){
			if(!value) return;
			mProperties[key] = value;
		}

	private:
		std::string mTypename;
		std::map<std::string, Entity*> mProperties;
	};

	template<typename T, const int _Type>
	class String_t : public Entity {
	public:		
		static const int Type = _Type;

		String_t()
			: Entity(Type, AMF0)
		{
		}

		String_t(const std::string& value)
			: Entity(Type, AMF0), mValue(value)
		{
		}

		virtual std::string toString() const {
			log::obj obj;
			obj << "\"" << mValue << "\"";
			return obj;
		}
	
		virtual void serialize(Packet* pak) const {
			Entity::serialize(pak);
			serialize(mValue, pak);
		}

		virtual void deserialize(Packet* pak){
			Entity::deserialize(pak);
			deserialize(mValue, pak);
		}

		static void serialize(const std::string& value, Packet* pak){
			pak->add<T>(value.length());
			pak->add(value.c_str(), value.length());
		}

		static void deserialize(std::string& value, Packet* pak){
			T length = pak->read<T>();
			if(length == 0){
				value = std::string();
				return;
			}
		
			value.assign((char*)pak->data() + pak->position(), length);
			pak->skip(length);
		}

	private:
		std::string mValue;
	};

	typedef String_t<uint16, AMF0_STRING> String;
	typedef String_t<uint32, AMF0_LONG_STRING> LongString;
}
