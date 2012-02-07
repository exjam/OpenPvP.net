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

						set("token", (amf::Null*)nullptr);
						set("accountSummary", (amf::Null*)nullptr);
						set("password", (amf::Null*)nullptr);
					}

					std::string getToken() const {
						return get("token");
					}

					const amf::Reference<AccountSummary> getAccountSummary() const {
						return get("accountSummary").toObject();
					}

					std::string getPassword() const {
						return get("password");
					}

					void setToken(const std::string& value){
						get("token") = value;
					}

					void setAccountSummary(AccountSummary* value){
						get("accountSummary") = value;
					}

					void setPassword(const std::string& value){
						get("password") = value;
					}
				};
			};
		};
	};
};
