#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class BaseSummoner : public amf::Object {
				public:
					BaseSummoner(){
						setName("com.riotgames.platform.summoner.BaseSummoner");

						set("profileIconId", new amf::Null());
						set("summonerId", new amf::Null());
						set("acctId", new amf::Null());
						set("name", new amf::Null());
						set("internalName", new amf::Null());
					}

					int getProfileIconId(){
						return get("profileIconId")->toInt();
					}

					double getSummonerId(){
						return get("summonerId")->toDouble();
					}

					double getAcctId(){
						return get("acctId")->toDouble();
					}

					std::string getName(){
						return get("name")->toString();
					}

					std::string getInternalName(){
						return get("internalName")->toString();
					}

					void setProfileIconId(int value){
						set("profileIconId", amf::object_creator_t(value).mValue);
					}

					void setSummonerId(double value){
						set("summonerId", amf::object_creator_t(value).mValue);
					}

					void setAcctId(double value){
						set("acctId", amf::object_creator_t(value).mValue);
					}

					void setName(const std::string& value){
						set("name", amf::object_creator_t(value).mValue);
					}

					void setInternalName(const std::string& value){
						set("internalName", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
