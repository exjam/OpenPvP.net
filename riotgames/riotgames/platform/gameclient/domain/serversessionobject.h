#pragma once

#include "amf/variant.h"
#include "accountsummary.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class ServerSessionObject : public amf::Object {
				public:
					ServerSessionObject(){
						setName("com.riotgames.platform.login.Session");

						set("token", new amf::Null());
						set("accountSummary", new amf::Null());
						set("password", new amf::Null());
					}

					std::string getToken(){
						return get("token")->toString();
					}

					AccountSummary* getAccountSummary(){
						return (AccountSummary*)get("accountSummary")->toObject();
					}

					std::string getPassword(){
						return get("password")->toString();
					}

					void setToken(const std::string& value){
						set("token", amf::object_creator_t(value).mValue);
					}

					void setAccountSummary(AccountSummary* value){
						set("accountSummary", (Variant*)value);
					}

					void setPassword(const std::string& value){
						set("password", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
