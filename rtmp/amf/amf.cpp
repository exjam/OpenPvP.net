#include "amf.h"
#include "amf0.h"
#include "amf3.h"

#include "log.h"

#include <stdarg.h>
#include <assert.h>

namespace amf {
	Encoder_ Encoder;
	log::indent_t amf::log::indent(1);
	log::indent_t amf::log::outdent(-1);
	int log::obj::mIndent = 0;
	bool log::obj::mLineStart = true;

	Encoder_::Encoder_(){
		memset(mVersions, 0, sizeof(EncoderImpl*) * (mMaxVersion + 1));
		mVersions[0] = new amf0();
		mVersions[3] = new amf3();
	}

	void Encoder_::defineObject(Object* object){
		for(int i = 0; i <= mMaxVersion; ++i)
			if(mVersions[i])
				mVersions[i]->defineObject(object);
	}

	void Encoder_::addExternalizable(flex::utils::IExternalizable* object){
		for(int i = 0; i <= mMaxVersion; ++i)
			if(mVersions[i])
				mVersions[i]->addExternalizable(object);
	}

	void Encoder_::start(uint8 version){
		setVersion(version);

		for(auto itr = mCache.begin(); itr != mCache.end(); ++itr){
			if(*itr)
				delete *itr;
		}
		
		mCache.clear();

		for(int i = 0; i <= mMaxVersion; ++i)
			if(mVersions[i])
				mVersions[i]->start();
	}

	void Encoder_::end(){
		for(int i = 0; i <= mMaxVersion; ++i)
			if(mVersions[i])
				mVersions[i]->end();
	}

	void Encoder_::setVersion(uint8 version){
		assert(mVersion <= mMaxVersion);
		assert(mVersions[mVersion]);

		mVersion = version;
	}

	Variant* Encoder_::deserialise(ByteStream& stream, bool cache){
		assert(stream.tell() < stream.size());
		amf::Variant* result = mVersions[mVersion]->deserialise(mVersion, stream);
		if(cache && result)
			mCache.push_back(result);
		
		return result;
	}

	void Encoder_::serialise(Variant* value, ByteStream& stream){
		mVersions[mVersion]->serialise(mVersion, value, stream);
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
