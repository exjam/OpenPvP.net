#pragma once

#include "amf.h"

#include <map>
#include <vector>

namespace amf {
	class Variant {
	public:
		Variant(int type) : mType(type) {}
		virtual ~Variant() {}

		int type() const { return mType; }

		int32 toInt() const;
		bool toBool() const;
		Date* toDate() const;
		uint32 toUInt() const;
		Array* toArray() const;
		double toDouble() const;
		Object* toObject() const;
		std::string toString() const;
		ByteArray* toByteArray() const;

		static Variant* fromValue(const std::string& value);
		static Variant* fromValue(const char* value);
		static Variant* fromValue(const uint32& value);
		static Variant* fromValue(const int32& value);
		static Variant* fromValue(const bool& value);
		static Variant* fromValue(const double& value);

		virtual Variant* copy() const = 0;

	private:
		int mType;
	};
	
	class Null : public Variant {
	public:
		static const int Type = AMF_NULL;

		Null() : Variant(Type) {}
		
		Variant* copy() const {
			return new Null();
		}

	private:
	};

	class Number : public Variant {
	public:
		static const int Type = AMF_NUMBER;

		Number() : Variant(Type), mValue(0.0) {}
		Number(double value) : Variant(Type), mValue(value) {}

		double& value(){
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
		
		Variant* copy() const {
			return new Number(mValue);
		}

	private:
		double mValue;
	};

	class Integer : public Variant {
	public:
		static const int Type = AMF_INTEGER;

		Integer() : Variant(Type), mValue(0) {}
		Integer(int value) : Variant(Type), mValue(value) {}

		int& value(){
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
		
		Variant* copy() const {
			return new Integer(mValue);
		}

	private:
		int mValue;
	};

	class Boolean : public Variant {
	public:
		static const int Type = AMF_BOOLEAN;

		Boolean() : Variant(Type), mValue(false) {}
		Boolean(bool value) : Variant(Type), mValue(value) {}

		bool& value(){
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
		
		Variant* copy() const {
			return new Boolean(mValue);
		}

	private:
		bool mValue;
	};

	class String : public Variant {
	public:
		static const int Type = AMF_STRING;

		String() : Variant(Type) {}
		String(const std::string& value) : mValue(value), Variant(Type) {}

		std::string& value(){
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
		
		Variant* copy() const {
			return new String(mValue);
		}

	private:
		std::string mValue;
	};
	
	class Date : public Variant {
	public:
		static const int Type = AMF_DATE;

		Date() : Variant(Type), mValue(0.0), mTimezone(0) {}
		Date(double value, uint16 timezone = 0) : Variant(Type), mValue(value), mTimezone(timezone) {}

		double& value(){
			return mValue;
		}

		void setValue(double value){
			mValue = value;
		}

		uint16& timezone(){
			return mTimezone;
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
		
		Variant* copy() const {
			return new Date(mValue, mTimezone);
		}

	private:
		double mValue;
		uint16 mTimezone;
	};

	class ByteArray : public Variant {
	public:
		static const int Type = AMF_BYTE_ARRAY;

		ByteArray() : Variant(Type), mSize(0), mData(0) {}

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

		void setSize(uint32 size){
			mSize = size;

			if(mData)
				delete [] mData;

			mData = new uint8[size];
		}
		
		Variant* copy() const {
			ByteArray* arr = new ByteArray();
			arr->mSize = mSize;
			arr->mData = new uint8[mSize];
			memcpy(arr->mData, mData, mSize);
			return arr;
		}

	private:
		uint32 mSize;
		uint8* mData;
	};

	struct var_t {
		var_t(const std::string& name, Variant* value) : mName(name), mValue(value) {}

		std::string mName;
		Variant* mValue;
	};

	struct object_creator_t {
		object_creator_t(Variant* value) : mValue(value) {}
		object_creator_t(const std::string& value) : mValue(Variant::fromValue(value)) {}
		object_creator_t(const char* value) : mValue(Variant::fromValue(value)) {}
		object_creator_t(const uint32& value) : mValue(Variant::fromValue(value)) {}
		object_creator_t(const int32& value) : mValue(Variant::fromValue(value)) {}
		object_creator_t(const bool& value) : mValue(Variant::fromValue(value)) {}
		object_creator_t(const double& value) : mValue(Variant::fromValue(value)) {}

		Variant* mValue;
	};

	var_t var(const std::string& name, object_creator_t obj);
	
	template<typename T>
	class Array_t : public Variant {
	public:
		typename std::map<std::string, T>::const_iterator iterator;
		static const int Type = AMF_ARRAY;

		Array_t() : Variant(Type) {}
		
		~Array_t(){
			for(auto itr = mDense.begin(); itr != mDense.end(); ++itr){
				if(*itr)
					delete *itr;
			}

			for(auto itr = mAssociative.begin(); itr != mAssociative.end(); ++itr){
				if(itr->second)
					delete itr->second;
			}
		}

		T at(size_t index) const {
			if(index >= mDense.size())
				return nullptr;

			return mDense[index];
		}

		T at(const std::string& key) const {
			auto itr = mAssociative.find(key);
			if(itr == mAssociative.end())
				return nullptr;

			return itr->second;
		}

		void insert(const std::string& key, T value){
			mAssociative[key] = value;
		}

		void push_back(T value){
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

		T& operator[](size_t index){
			while(mDense.size() <= index)
				mDense.push_back(nullptr);

			return mDense[index];
		}

		T& operator[](const std::string& key){
			return mAssociative[key];
		}

		typename std::map<std::string, T>::const_iterator begin(){
			return mAssociative.begin();
		}

		typename std::map<std::string, T>::const_iterator end(){
			return mAssociative.end();
		}
		
		Array_t<T>& operator<<(Variant* var){
			push_back((T)var);
			return *this;
		}
		
		Array_t<T>& operator<<(const var_t& var){
			insert(var.mName, var.mValue);
			return *this;
		}
		
		Variant* copy() const {
			Array* arr = new Array();
			for(auto itr = mDense.begin(); itr != mDense.end(); ++itr)
				arr->push_back((*itr)->copy());

			for(auto itr = mAssociative.begin(); itr != mAssociative.end(); ++itr)
				arr->insert(itr->first, itr->second->copy());
			
			return arr;
		}

	private:
		std::vector<T> mDense;
		std::map<std::string, T> mAssociative;
	};

	class Array : public Array_t<Variant*> {};
	
	class Object : public Variant {
	public:
		static const int Type = AMF_OBJECT;

		Object() : Variant(Type) {}
		Object(const std::string& name) : Variant(Type), mName(name) {}
		
		virtual ~Object(){
			for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr){
				if(itr->second)
					delete itr->second;
			}
		}

		Variant* get(const std::string& key) const {
			auto itr = mProperties.find(key);
			if(itr == mProperties.end())
				return nullptr;

			return itr->second;
		}

		void set(const std::string& key, Variant* value){
			auto itr = mProperties.find(key);
			if(itr != mProperties.end())
				delete itr->second;

			mProperties[key] = value;
		}

		std::string name() const {
			return mName;
		}

		void setName(const std::string& name){
			mName = name;
		}

		void insert(const std::string& key, Variant* value){
			set(key, value);
		}

		Variant*& operator[](const std::string& key){
			return mProperties[key];
		}

		std::map<std::string, Variant*>::const_iterator begin(){
			return mProperties.begin();
		}

		std::map<std::string, Variant*>::const_iterator end(){
			return mProperties.end();
		}
		
		Object& operator<<(const var_t& var){
			set(var.mName, var.mValue);
			return *this;
		}
		
		void defineObject();
		
		Variant* copy() const {
			Object* obj = new Object(mName);

			for(auto itr = mProperties.begin(); itr != mProperties.end(); ++itr)
				obj->insert(itr->first, itr->second->copy());

			return obj;
		}

	private:
		std::string mName;
		std::map<std::string, Variant*> mProperties;
	};
};
