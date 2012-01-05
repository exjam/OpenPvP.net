#pragma once

#include "rtmp/types.h"

#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <stdarg.h>

namespace amf {
	typedef enum {
		AMF0,
		AMF3,
	} Version;
	
	struct null_t {};
	struct undefined_t {};
	
	extern null_t null;
	extern undefined_t undefined;

	class Entity : public Serializable {
	public:
		Entity(uint32 type, uint32 version);
		
		uint32 type() const;

		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);

		virtual std::string toString() const;
		
		static Entity* create(Entity* value);
		static Entity* create(const bool& value);
		static Entity* create(const uint8& value);
		static Entity* create(const uint16& value);
		static Entity* create(const uint32& value);
		static Entity* create(const int8& value);
		static Entity* create(const int16& value);
		static Entity* create(const int32& value);
		static Entity* create(const float& value);
		static Entity* create(const double& value);
		static Entity* create(const char* value);
		static Entity* create(const std::string& value);
		static Entity* create(const undefined_t& value);
		static Entity* createObject(const std::string& name = std::string());

		static Entity* read(ByteStream& stream);
		static Entity* read(uint32 version, ByteStream& stream);
		
		static Entity* readAMF0(ByteStream& stream);
		static Entity* readAMF3(ByteStream& stream);

	private:
		uint8 mType;
		uint32 mVersion;
		static uint32 mActiveVersion;
	};

	class Object : public Entity {
	public:
		Object(uint32 type, uint32 version) : Entity(type, version) {}

		template<typename T>
		void set(const std::string& n, const T& v){
			setProperty(n, Entity::create(v));
		}

		template<typename T>
		void set(uint32 n, const T& v){
			setProperty(n, Entity::create(v));
		}
		
		virtual void setProperty(uint32 n, Entity* v){}
		virtual void setProperty(const std::string& n, Entity* v){}

		virtual Entity* getProperty(uint32 n){ return NULL; }
		virtual Entity* getProperty(const std::string& n){ return NULL; }
	};

	struct object_begin_t {
		object_begin_t(){}
		object_begin_t(const std::string& n) : mName(n) {}
		std::string mName;
	};
	struct object_end_t {};

	struct var {
		template<typename T>
		var(const std::string& n, const T& v) : mName(n) { mValue = Entity::create(v); }

		std::string mName;
		Entity* mValue;
	};

	void object_begin(class Container*);
	void object_end(class Container*);
	object_begin_t object_begin(const std::string& name);
	
	class Container : public Serializable {
	public:
		Container();
		~Container();

		std::string toString() const;
	
		virtual void serialize(ByteStream& stream) const;
		virtual void deserialize(ByteStream& stream);

		template<typename T>
		void add(const T& value){
			add(Entity::create(value));
		}

		void add(Entity* child){
			if(child)
				mChildren.push_back(child);
		}

		template<typename T>
		Container& operator<<(const T& value){
			add(Entity::create(value));
			return *this;
		}

		Container& operator<<(const var& obj){
			if(mStreamObjects.size() > 0)
				mStreamObjects.top()->setProperty(obj.mName, obj.mValue);

			return *this;
		}

		Container& operator<<(const object_begin_t& _obj){
			Object* obj = (Object*)Entity::createObject(_obj.mName);
			mStreamObjects.push(obj);
			add((Entity*)obj);
			return *this;
		}

		Container& operator<<(const object_end_t& obj){
			mStreamObjects.pop();
			return *this;
		}
		
		Container& operator<<(void (*pf)(Container*)){
			(*pf)(this);
			return *this;
		}

	private:
		std::stack<Object*> mStreamObjects;
		std::vector<Entity*> mChildren;
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

	namespace log {
		struct hex {
			template<typename T>
			hex(const T& value){
				sprintf_s(v, 16, "%X", value);

				if(strlen(v) % 2){
					memcpy(v+1, v, 15);
					v[0] = '0';
				}
			}

			char v[16];
		};

		class obj {
		public:
			struct indent_t {
				indent_t(int i) : i(i) {}
				int i;
			};

			struct format_t {
				typedef enum {
					FMT_DECIMAL,
					FMT_HEX,
				};

				format_t(int f) : f(f) {}
				int f;
			};

		public:
			obj(){}

			obj& operator<< (const indent_t& i){
				mIndent += i.i;

				if(mIndent < 0)
					mIndent = 0;

				return *this;
			}

			obj& operator<< (const hex& h){
				(*this) << h.v;
				return *this;
			}

			obj& operator<< (std::ostream& ( *pf )(std::ostream&)){
				if(pf == std::endl)
					mLineStart = true;

				mOut << pf;
				return *this;
			}

			template<typename T> 
			obj& operator<< (const T& x){
				if(mLineStart){
					for(int i = 0; i < mIndent; ++i)
						mOut << "\t";

					mLineStart = false;
				}

				mOut << x;
				return *this;
			}

			std::string str() const {
				return mOut.str();
			}

			operator std::string() const {
				return mOut.str();
			}

		private:
			static int mIndent;
			static bool mLineStart;
			std::stringstream mOut;
		};

		extern obj::indent_t indent;
		extern obj::indent_t outdent;
	};
};
