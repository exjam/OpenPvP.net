#include "amf.h"
#include "amf0.h"
#include "amf3.h"

#include "log.h"

#include <stdarg.h>
#include <assert.h>

namespace amf {
	log::indent_t amf::log::indent(1);
	log::indent_t amf::log::outdent(-1);
	int log::obj::mIndent = 0;
	bool log::obj::mLineStart = true;

	Encoder::Encoder(uint8 version)
		: mVersion(version)
	{
		mAmf0 = new amf0(this);
		mAmf3 = new amf3(this);
	}

	Encoder::~Encoder(){
		delete mAmf0;
		delete mAmf3;
	}

	void Encoder::defineObject(Object* object){
		amf3::defineObject(object);
	}

	void Encoder::addExternalizable(flex::utils::IExternalizable* object){
		amf3::addExternalizable(object);
	}

	void Encoder::setVersion(uint8 version){
		mVersion = version;
	}

	Variant Encoder::deserialise(ByteStream& stream, bool cache){
		assert(stream.tell() < stream.size());
		
		if(mVersion == 0)
			return mAmf0->deserialise(mVersion, stream);
		else if(mVersion == 3)
			return mAmf3->deserialise(mVersion, stream);
		
		return Variant();
	}

	void Encoder::serialise(const Variant& value, ByteStream& stream){
		if(mVersion == 0)
			mAmf0->serialise(mVersion, value, stream);
		else if(mVersion == 3)
			mAmf3->serialise(mVersion, value, stream);
	}

	DecodeException::DecodeException(const std::string& what)
		: mWhat(what)
	{
	}

	DecodeException::DecodeException(char* format, ...){
		char buffer[256];

		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, 256, format, args);
		va_end(args);

		mWhat = buffer;
	}

	const char* DecodeException::what() const throw() {
		return mWhat.c_str();
	}

	EncodeException::EncodeException(const std::string& what)
		: mWhat(what)
	{
	}

	EncodeException::EncodeException(char* format, ...){
		char buffer[256];

		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, format, args);
		va_end(args);

		mWhat = buffer;
	}

	const char* EncodeException::what() const throw() {
		return mWhat.c_str();
	}
};
