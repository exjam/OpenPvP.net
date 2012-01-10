#pragma once

#include <stack>
#include <string>
#include <vector>
#include "rtmp/types.h"

namespace amf {
	typedef enum {
		AMF_NULL,
		AMF_NUMBER,
		AMF_INTEGER,
		AMF_BOOLEAN,
		AMF_STRING,
		AMF_DATE,
		AMF_ARRAY,
		AMF_BYTE_ARRAY,
		AMF_OBJECT,
		AMF_UNKNOWN_TYPE,
	} AmfTypes;

	class Variant;
	class Object;
	class Null;
	class Number;
	class Integer;
	class Boolean;
	class String;
	class Date;
	class Array;
	class ByteArray;
	class Container;
	
	void setVersion(uint8 version);

	Variant* deserialise(ByteStream& stream);
	void serialise(Variant* value, ByteStream& stream);

	void deserialise(Container* container, ByteStream& stream);
	void serialise(Container* container, ByteStream& stream);

	struct object_begin_t {
		object_begin_t(){}
		object_begin_t(const std::string& n) : mName(n) {}
		std::string mName;
	};
	struct object_end_t {};
	
	void object_begin(class Container*);
	void object_end(class Container*);
	object_begin_t object_begin(const std::string& name);

	struct var_t {
		var_t(const std::string& name, Variant* value)
			: mName(name), mValue(value) {}

		std::string mName;
		Variant* mValue;
	};

	struct object_creator_t {
		object_creator_t(bool value);
		object_creator_t(int32 value);
		object_creator_t(uint32 value);
		object_creator_t(double value);
		object_creator_t(const std::string& value);

		Variant* mValue;
	};

	var_t var(const std::string& name, Variant* value);
	var_t var(const std::string& name, object_creator_t obj);

	class Container {
	public:
		Container& operator<<(Variant* obj);
		Container& operator<<(object_creator_t obj);

		Container& operator<<(const var_t& var);
		Container& operator<<(const object_begin_t& obj);
		Container& operator<<(const object_end_t& obj);

		Container& operator<<(void (*pf)(Container*));

		size_t size() const;
		Variant* at(size_t index) const;
		void push_back(Variant* child);

	private:
		std::stack<Object*> mStreamObjects;
		std::vector<Variant*> mChildren;
	};

	class DecodeException : public std::exception {
	public:
		DecodeException(char* format, ...);
		DecodeException(const std::string& what);

		virtual const char* what() const throw();

	private:
		std::string mWhat;
	};

	class EncodeException : public std::exception {
	public:
		EncodeException(char* format, ...);
		EncodeException(const std::string& what);

		virtual const char* what() const throw();
		
	private:
		std::string mWhat;
	};
};

#include "amf/amf_types.h"
#include "amf/amf_log.h"
