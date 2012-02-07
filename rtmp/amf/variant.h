#pragma once

#include <map>
#include <vector>

#include "types.h"

namespace amf {
	class Null;
	class Date;
	class Array;
	class Object;
	class Number;
	class String;
	class Integer;
	class Boolean;
	class ByteArray;

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

	class ReferenceCounter {
	public:
		ReferenceCounter()
			: mReferences(0)
		{
		}

		int addReference(){
			return ++mReferences;
		}

		int removeReference(){
			return --mReferences;
		}

	private:
		volatile int mReferences;
	};

	template<class T>
	class Reference {
	public:
		Reference()
			: mObject(nullptr)
		{
		}

		Reference(T* object)
			: mObject(object)
		{
			if(mObject)
				mObject->addReference();
		}

		Reference(const Reference& other)
			: mObject(other.mObject)
		{
			if(mObject)
				mObject->addReference();
		}

		template<class X>
		Reference(const Reference<X>& other){
			mObject = (T*)other.__InternalObject();

			if(mObject)
				mObject->addReference();
		}

		virtual ~Reference(){
			if(mObject){
				if(mObject->removeReference() <= 0){
					delete mObject;
				}
			}
		}

		operator T*() const {
			return mObject;
		}

		T* operator ->() const {
			return mObject;
		}

		Reference& operator =(T* object){
			if(mObject){
				if(mObject->removeReference() <= 0){
					delete mObject;
				}
			}
			
			mObject = object;

			if(mObject)
				mObject->addReference();

			return *this;
		}

		Reference& operator =(const Reference& other){
			(*this) = other.mObject;
			return *this;
		}

		T* __InternalObject() const {
			return mObject;
		}

	protected:
		T* mObject;
	};

	class BaseAmf : public ReferenceCounter {
	public:
		BaseAmf(int type) : mType(type) {}
		virtual ~BaseAmf(){}

		int type() const {
			return mType;
		}

	private:
		int mType;
	};

	class Variant : public Reference<BaseAmf> {
	public:
		Variant();
		Variant(BaseAmf* obj);
		Variant(const Variant& other);

		Variant(const char* value);
		Variant(const bool& value);
		Variant(const int32& value);
		Variant(const uint32& value);
		Variant(const double& value);
		Variant(const std::string& value);

		virtual ~Variant();

		int type() const;
		bool operator !() const;
		/*
		BaseAmf* operator ->(){
			return mObject;
		}
		*/

		void fromBool(const bool& value);
		void fromInt(const int32& value);
		void fromUInt(const uint32& value);
		void fromDouble(const double& value);
		void fromString(const std::string& value);
		
		Variant& operator =(BaseAmf* v);
		Variant& operator =(const Variant& v);

		Variant& operator =(const bool& v);
		Variant& operator =(const int32& v);
		Variant& operator =(const uint32& v);
		Variant& operator =(const double& v);
		Variant& operator =(const std::string& v);
		
		int32 toInt() const;
		bool toBool() const;
		uint32 toUInt() const;
		double toDouble() const;
		std::string toString() const;

		Reference<Date> toDate() const;
		Reference<Array> toArray() const;
		Reference<Object> toObject() const;
		Reference<ByteArray> toByteArray() const;

		operator bool() const;
		operator int32() const;
		operator uint32() const;
		operator double() const;
		operator std::string() const;
		
		operator Null*() const;
		operator Date*() const;
		operator Array*() const;
		operator Object*() const;
		operator Number*() const;
		operator String*() const;
		operator Integer*() const;
		operator Boolean*() const;
		operator ByteArray*() const;
	};
	
	struct var_t {
		var_t(const std::string& name, const Variant& value) : mName(name), mValue(value) {}

		std::string mName;
		Variant mValue;
	};

	var_t var(const std::string& name, const Variant& obj);

	Variant& operator<<(Variant& lhs, const var_t& var);

	class Null : public BaseAmf {
	public:
		static const int Type = AMF_NULL;

		Null() : BaseAmf(Type) {}

	private:
	};

	class Number : public BaseAmf {
	public:
		static const int Type = AMF_NUMBER;

		Number() : BaseAmf(Type), mValue(0.0) {}
		Number(double value) : BaseAmf(Type), mValue(value) {}

		double value() const {
			return mValue;
		}

		void setValue(double value){
			mValue = value;
		}

		Number& operator=(double value){
			mValue = value;
			return *this;
		}

		operator double() const {
			return mValue;
		}

	private:
		double mValue;
	};

	class Integer : public BaseAmf {
	public:
		static const int Type = AMF_INTEGER;

		Integer() : BaseAmf(Type), mValue(0) {}
		Integer(int value) : BaseAmf(Type), mValue(value) {}

		int value() const {
			return mValue;
		}

		void setValue(int value){
			mValue = value;
		}

		Integer& operator=(int value){
			mValue = value;
			return *this;
		}

		operator int() const {
			return mValue;
		}

	private:
		int mValue;
	};

	class Boolean : public BaseAmf {
	public:
		static const int Type = AMF_BOOLEAN;

		Boolean() : BaseAmf(Type), mValue(false) {}
		Boolean(bool value) : BaseAmf(Type), mValue(value) {}

		bool value() const {
			return mValue;
		}

		void setValue(bool value){
			mValue = value;
		}

		Boolean& operator=(bool value){
			mValue = value;
			return *this;
		}

		operator bool() const {
			return mValue;
		}

	private:
		bool mValue;
	};

	class String : public BaseAmf {
	public:
		static const int Type = AMF_STRING;

		String() : BaseAmf(Type) {}
		String(const std::string& value) : BaseAmf(Type), mValue(value) {}

		const std::string& value() const {
			return mValue;
		}

		const char* c_str() const {
			return mValue.c_str();
		}

		size_t length() const {
			return mValue.length();
		}

		void setValue(const std::string& value){
			mValue = value;
		}

		String& operator=(const std::string& value){
			mValue = value;
			return *this;
		}

		operator std::string() const {
			return mValue;
		}

	private:
		std::string mValue;
	};
	
	class Date : public BaseAmf {
	public:
		static const int Type = AMF_DATE;

		Date() : BaseAmf(Type), mValue(0.0), mTimezone(0) {}
		Date(double value, uint16 timezone = 0) : BaseAmf(Type), mValue(value), mTimezone(timezone) {}

		double value() const {
			return mValue;
		}

		uint16 timezone() const {
			return mTimezone;
		}

		void setValue(double value){
			mValue = value;
		}

		void setTimezone(uint16 value){
			mTimezone = value;
		}

		Date& operator=(double value){
			mValue = value;
			return *this;
		}

		operator double() const {
			return mValue;
		}

	private:
		double mValue;
		uint16 mTimezone;
	};

	class ByteArray : public BaseAmf {
	public:
		static const int Type = AMF_BYTE_ARRAY;

		ByteArray() : BaseAmf(Type), mSize(0), mData(0) {}

		~ByteArray(){
			if(mData)
				delete [] mData;
		}

		uint32 size() const {
			return mSize;
		}

		uint8* value(){
			return mData;
		}

		const uint8* value() const {
			return mData;
		}

		void setSize(uint32 size){
			mSize = size;

			if(mData)
				delete [] mData;

			mData = new uint8[size];
		}

	private:
		uint32 mSize;
		uint8* mData;
	};
	
	class Array : public BaseAmf {
	public:
		typedef std::map<std::string, Variant>::const_iterator iterator;

		static const int Type = AMF_ARRAY;

		Array() : BaseAmf(Type) {}
		~Array(){}

		const Variant& at(size_t index) const {
			return mDense[index];
		}

		const Variant& at(const std::string& key) const {
			return mAssociative.find(key)->second;
		}

		void insert(const std::string& key, const Variant& value){
			mAssociative[key] = value;
		}

		void push_back(const Variant& value){
			mDense.push_back(value);
		}

		size_t size() const {
			return mDense.size();
		}

		size_t keys() const {
			return mAssociative.size();
		}

		bool hasAssociative() const {
			return mAssociative.size() > 0;
		}

		bool hasDense() const {
			return mDense.size() > 0;
		}

		Variant& operator[](size_t index){
			return mDense[index];
		}

		Variant& operator[](const std::string& key){
			return mAssociative[key];
		}

		iterator begin() const {
			return mAssociative.begin();
		}

		iterator end() const {
			return mAssociative.end();
		}
		
		Array& operator<<(const Variant& var){
			push_back(var);
			return *this;
		}
		
		Array& operator<<(const var_t& var){
			insert(var.mName, var.mValue);
			return *this;
		}
		
	private:
		std::vector<Variant> mDense;
		std::map<std::string, Variant> mAssociative;
	};

	template<class T>
	class TypedArray : private Array {
	public:
		T* at(size_t index) const {
			return (T*)(Array::at(index).toObject());
		}

		T* at(const std::string& key) const {
			return (T*)(Array::at(key).toObject());
		}

		T* operator[](size_t index){
			return (T*)(Array::operator [](index).toObject());
		}

		Variant& operator[](const std::string& key){
			return (T*)(Array::operator [](key).toObject());
		}

		size_t size() const {
			return Array::size();
		}

		size_t keys() const {
			return Array::keys();
		}

	private:
	};
	
	class Object : public BaseAmf {
	public:
		typedef std::map<std::string, Variant>::const_iterator iterator;
		static const int Type = AMF_OBJECT;

		Object() : BaseAmf(Type) {}
		Object(const std::string& name) : BaseAmf(Type), mName(name) {}
		virtual ~Object(){}

		Variant& get(const std::string& key){
			return mProperties.find(key)->second;
		}

		const Variant& get(const std::string& key) const {
			return mProperties.find(key)->second;
		}

		void set(const std::string& key, const Variant& value){
			mProperties[key] = value;
		}

		std::string name() const {
			return mName;
		}

		void setName(const std::string& name){
			mName = name;
		}

		void insert(const std::string& key, const Variant& value){
			set(key, value);
		}

		const Variant& operator[](const std::string& key){
			return mProperties[key];
		}

		iterator begin() const {
			return mProperties.begin();
		}

		iterator end() const {
			return mProperties.end();
		}
		
		Object& operator<<(const var_t& var){
			set(var.mName, var.mValue);
			return *this;
		}
		
		void defineObject();

	private:
		std::string mName;
		std::map<std::string, Variant> mProperties;
	};
};
