#include "packet.h"
#include "messages.h"
#include "bytestream.h"

#include "amf/amf.h"
#include "amf/amf0.h"
#include "amf/amf3.h"
#include "amf/variant.h"

namespace rtmp {
	namespace messages {
		double AmfCommand::id(){
			return mID;
		}
			
		void AmfCommand::setID(double id){
			mID = id;
		}

		Amf0Command::Amf0Command(const std::string& name, amf::Variant& object)
			: Packet(Type), mName(name), mProperties(object), mInformation(0)
		{
		}

		Amf0Command::Amf0Command(Packet& source)
			: Packet(Type), mInformation(0)
		{
			amf::String _string;
			amf::Number _number;

			amf::Encoder encoder(0);
			mName = encoder.deserialise(source.mData);
			mID = encoder.deserialise(source.mData);
			mProperties = encoder.deserialise(source.mData);
			mInformation = encoder.deserialise(source.mData);
		}
		
		Amf0Command::~Amf0Command(){
		}

		Packet* Amf0Command::packet(){
			mData.clear();
			
			amf::Encoder encoder(0);
			encoder.serialise(mName, mData);
			encoder.serialise(mID, mData);
			encoder.serialise(mProperties, mData);

			return (Packet*)this;
		}

		const std::string& Amf0Command::name(){
			return mName;
		}

		const amf::Variant& Amf0Command::properties(){
			return mProperties;
		}

		const amf::Variant& Amf0Command::information(){
			return mInformation;
		}

		Amf3Command::Amf3Command(amf::Variant& object)
			: Packet(Type), mObject(object)
		{
		}

		Amf3Command::Amf3Command(Packet& source)
			: Packet(Type), mObject(0)
		{
			ByteStream& stream = source.mData;


			uint8 tmp;
			stream >> tmp;
			
			amf::Encoder encoder(0);
			encoder.deserialise(stream);
			mID = encoder.deserialise(stream);
			encoder.deserialise(stream);
			mObject = encoder.deserialise(stream);
		}

		Amf3Command::~Amf3Command(){
		}

		Packet* Amf3Command::packet(){
			mData.clear();

			amf::Encoder encoder(0);

			mData << uint8(0);
			encoder.serialise(amf::Variant((amf::BaseAmf*)nullptr), mData);
			encoder.serialise(mID, mData);
			encoder.serialise(amf::Variant((amf::BaseAmf*)nullptr), mData);
			mData << uint8(amf::amf0::AMF0_AVMPLUS);
			
			encoder.setVersion(3);
			encoder.serialise(mObject, mData);

			return (Packet*)this;
		}

		const amf::Variant& Amf3Command::object(){
			return mObject;
		}
	};
};
