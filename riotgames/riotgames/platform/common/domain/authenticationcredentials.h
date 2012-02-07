#pragma once

#include "amf/amf.h"

namespace riotgames {
	namespace platform {
		namespace common {
			namespace domain {
				class AuthenticationCredentials : public amf::Object {
				public:
					AuthenticationCredentials(){
						setName("com.riotgames.platform.login.AuthenticationCredentials");

						set("partnerCredentials", (amf::Null*)nullptr);
						set("oldPassword", (amf::Null*)nullptr);
						set("domain", (amf::Null*)nullptr);
						set("ipAddress", (amf::Null*)nullptr);
						set("authToken", (amf::Null*)nullptr);
						set("locale", (amf::Null*)nullptr);
						set("clientVersion", (amf::Null*)nullptr);
						set("password", (amf::Null*)nullptr);
						set("username", (amf::Null*)nullptr);
						set("securityAnswer", (amf::Null*)nullptr);

						defineObject();
					}

					std::string getPartnerCredentials() const {
						return get("partnerCredentials");
					}

					std::string getOldPassword() const {
						return get("oldPassword");
					}

					std::string getDomain() const {
						return get("domain");
					}

					std::string getIpAddress() const {
						return get("ipAddress");
					}

					std::string getAuthToken() const {
						return get("authToken");
					}

					std::string getLocale() const {
						return get("locale");
					}

					std::string getClientVersion() const {
						return get("clientVersion");
					}

					std::string getPassword() const {
						return get("password");
					}

					std::string getUsername() const {
						return get("username");
					}

					std::string getSecurityAnswer() const {
						return get("securityAnswer");
					}

					void setPartnerCredentials(const std::string& value){
						get("partnerCredentials") = value;
					}

					void setOldPassword(const std::string& value){
						get("oldPassword") = value;
					}

					void setDomain(const std::string& value){
						get("domain") = value;
					}

					void setIpAddress(const std::string& value){
						get("ipAddress") = value;
					}

					void setAuthToken(const std::string& value){
						get("authToken") = value;
					}

					void setLocale(const std::string& value){
						get("locale") = value;
					}

					void setClientVersion(const std::string& value){
						get("clientVersion") = value;
					}

					void setPassword(const std::string& value){
						get("password") = value;
					}

					void setUsername(const std::string& value){
						get("username") = value;
					}

					void setSecurityAnswer(const std::string& value){
						get("securityAnswer") = value;
					}
				};
			};
		};
	};
};
