#pragma once

#include "rtmp/types.h"

#include <string>
#include <vector>
#include <sstream>
#include <stdarg.h>

namespace amf {
	typedef enum {
		AMF0,
		AMF3,
	} Version;

	class Entity : public Serializable {
	public:
		Entity(uint32 type, uint32 version);
		
		uint32 type() const;

		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

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

		static Entity* read(Packet* pak);
		static Entity* read(uint32 version, Packet* pak);
		
		static Entity* readAMF0(Packet* pak);
		static Entity* readAMF3(Packet* pak);

	private:
		uint8 mType;
		uint32 mVersion;
		static uint32 mActiveVersion;
	};
	
	class Container : public Serializable {
	public:
		Container();
		~Container();

		std::string toString() const;
	
		virtual void serialize(Packet* pak) const;
		virtual void deserialize(Packet* pak);

		template<typename T> void add(T value){
			add(Entity::create(value));
		}

		template<> void add(Entity* child){
			if(child)
				mChildren.push_back(child);
		}

	private:
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
