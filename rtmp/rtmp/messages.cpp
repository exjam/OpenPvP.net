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

		Amf0Command::Amf0Command(const std::string& name, amf::Object* object)
			: Packet(Type), mName(name), mProperties(object->copy()->toObject()), mInformation(0)
		{
		}

		Amf0Command::Amf0Command(Packet& source)
			: Packet(Type), mInformation(0)
		{
			amf::String _string;
			amf::Number _number;

			amf::Encoder.start(0);
			mName = amf::Encoder.deserialise(source.mData)->toString();
			mID = amf::Encoder.deserialise(source.mData)->toDouble();
			mProperties = amf::Encoder.deserialise(source.mData)->copy()->toObject();
			mInformation = amf::Encoder.deserialise(source.mData)->copy()->toObject();
			amf::Encoder.end();
		}
		
		Amf0Command::~Amf0Command(){
			if(mProperties)
				delete mProperties;

			if(mInformation)
				delete mInformation;
		}

		Packet* Amf0Command::packet(){
			mData.clear();
			
			amf::Encoder.start(0);
			amf::Encoder.serialise(&amf::String(mName), mData);
			amf::Encoder.serialise(&amf::Number(mID), mData);
			amf::Encoder.serialise(mProperties, mData);
			amf::Encoder.end();

			return (Packet*)this;
		}

		const std::string& Amf0Command::name(){
			return mName;
		}

		amf::Object* Amf0Command::properties(){
			return mProperties;
		}

		amf::Object* Amf0Command::information(){
			return mInformation;
		}

		Amf3Command::Amf3Command(amf::Object* object)
			: Packet(Type), mObject(object->copy()->toObject())
		{
		}

		Amf3Command::Amf3Command(Packet& source)
			: Packet(Type), mObject(0)
		{
			ByteStream& stream = source.mData;


			uint8 tmp;
			stream >> tmp;
			
			amf::Encoder.start(0);
			amf::Encoder.deserialise(stream);
			mID = amf::Encoder.deserialise(stream)->toDouble();
			amf::Encoder.deserialise(stream);
			mObject = amf::Encoder.deserialise(stream)->copy()->toObject();
			amf::Encoder.end();
		}

		Amf3Command::~Amf3Command(){
			if(mObject)
				delete mObject;
		}

		Packet* Amf3Command::packet(){
			mData.clear();

			amf::Encoder.start(0);

			mData << uint8(0);
			amf::Encoder.serialise(&amf::Null(), mData);
			amf::Encoder.serialise(&amf::Number(mID), mData);
			amf::Encoder.serialise(&amf::Null(), mData);
			mData << uint8(amf::amf0::AMF0_AVMPLUS);

			amf::Encoder.setVersion(3);
			amf::Encoder.serialise(mObject, mData);

			return (Packet*)this;
		}

		amf::Object* Amf3Command::object(){
			return mObject;
		}
	};
};
