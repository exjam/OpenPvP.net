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

						set("profileIconId", (amf::Null*)nullptr);
						set("summonerId", (amf::Null*)nullptr);
						set("acctId", (amf::Null*)nullptr);
						set("name", (amf::Null*)nullptr);
						set("internalName", (amf::Null*)nullptr);
					}

					int getProfileIconId() const {
						return get("profileIconId");
					}

					double getSummonerId() const {
						return get("summonerId");
					}

					double getAcctId() const {
						return get("acctId");
					}

					std::string getName() const {
						return get("name");
					}

					std::string getInternalName() const {
						return get("internalName");
					}

					void setProfileIconId(int value){
						get("profileIconId") = value;
					}

					void setSummonerId(double value){
						get("summonerId") = value;
					}

					void setAcctId(double value){
						get("acctId") = value;
					}

					void setName(const std::string& value){
						get("name") = value;
					}

					void setInternalName(const std::string& value){
						get("internalName") = value;
					}
				};
			};
		};
	};
};
