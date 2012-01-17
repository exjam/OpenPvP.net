#pragma once

#include <iostream>
#include <sstream>

#include "variant.h"

namespace amf {
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

		extern indent_t indent;
		extern indent_t outdent;

		class obj {
		public:
			obj(){}

			std::string str() const {
				return mOut.str();
			}

			operator std::string() const {
				return mOut.str();
			}
			
			obj& operator<< (const Variant& var){
				(*this) << &var;
				return *this;
			}

			obj& operator<< (Variant* const& var){
				(*this) << (const Variant*)var;
				return *this;
			}
			
			obj& operator<< (const Object& var){
				(*this) << &var;
				return *this;
			}

			obj& operator<< (Object* const& var){
				(*this) << (const Variant*)var;
				return *this;
			}

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
			
			obj& operator<< (const Variant* const& var){
				switch(var->type()){
					case AMF_NULL:
						(*this) << "(null)";
						break;
					case AMF_NUMBER:
						(*this) << ((Number*)var)->value();
						break;
					case AMF_INTEGER:
						(*this) << ((Integer*)var)->value();
						break;
					case AMF_BOOLEAN:
						(*this) << (((Boolean*)var)->value() ? true : false);
						break;
					case AMF_STRING:
						(*this) << "\"" << ((String*)var)->value() << "\"";
						break;
					case AMF_DATE:
						(*this) << ((Date*)var)->value();
						break;
					case AMF_ARRAY:
						{
							Array* arr = (Array*)var;
							(*this) << "{ array" << std::endl;
							(*this) << log::indent;

							for(auto itr = arr->begin(); itr != arr->end(); ++itr){
								(*this) << "'" << itr->first << "' =>";
								(*this) << itr->second << std::endl;
							}

							for(uint32 i = 0; i < arr->size(); ++i){
								(*this) << "[" << i << "] =>";
								(*this) << log::indent;
								(*this) << arr->at(i) << std::endl;
								(*this) << log::outdent;
							}

							(*this) << log::outdent;
							(*this) << "}";
						}
						break;
					case AMF_BYTE_ARRAY:
						{
							ByteArray* raw = (ByteArray*)var;
							(*this) << "{ raw " << raw->size() << std::endl;
							(*this) << log::indent;

							for(uint32 i = 0; i < raw->size(); ++i){
								(*this) << log::hex(raw->value()[i]) << " ";

								if(i > 0 && i % 16 == 0)
									(*this) << std::endl;
							}

							(*this) << log::outdent;
							(*this) << std::endl << "}";
						}
						break;
					case AMF_OBJECT:
						{
							Object* object = (Object*)var;

							(*this) << "{ object " << object->name() << std::endl;
							(*this) << log::indent;

							for(auto itr = object->begin(); itr != object->end(); ++itr){
								(*this) << itr->first << " = ";
								(*this) << itr->second << std::endl;
							}

							(*this) << log::outdent;
							(*this) << "}";
						}
						break;
				}

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

		private:
			static int mIndent;
			static bool mLineStart;
			std::stringstream mOut;
		};
	};
};
