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

						set("partnerCredentials", new amf::Null());
						set("oldPassword", new amf::Null());
						set("domain", new amf::Null());
						set("ipAddress", new amf::Null());
						set("authToken", new amf::Null());
						set("locale", new amf::Null());
						set("clientVersion", new amf::Null());
						set("password", new amf::Null());
						set("username", new amf::Null());
						set("securityAnswer", new amf::Null());

						defineObject();
					}

					std::string getPartnerCredentials(){
						return get("partnerCredentials")->toString();
					}

					std::string getOldPassword(){
						return get("oldPassword")->toString();
					}

					std::string getDomain(){
						return get("domain")->toString();
					}

					std::string getIpAddress(){
						return get("ipAddress")->toString();
					}

					std::string getAuthToken(){
						return get("authToken")->toString();
					}

					std::string getLocale(){
						return get("locale")->toString();
					}

					std::string getClientVersion(){
						return get("clientVersion")->toString();
					}

					std::string getPassword(){
						return get("password")->toString();
					}

					std::string getUsername(){
						return get("username")->toString();
					}

					std::string getSecurityAnswer(){
						return get("securityAnswer")->toString();
					}

					void setPartnerCredentials(const std::string& value){
						set("partnerCredentials", amf::object_creator_t(value).mValue);
					}

					void setOldPassword(const std::string& value){
						set("oldPassword", amf::object_creator_t(value).mValue);
					}

					void setDomain(const std::string& value){
						set("domain", amf::object_creator_t(value).mValue);
					}

					void setIpAddress(const std::string& value){
						set("ipAddress", amf::object_creator_t(value).mValue);
					}

					void setAuthToken(const std::string& value){
						set("authToken", amf::object_creator_t(value).mValue);
					}

					void setLocale(const std::string& value){
						set("locale", amf::object_creator_t(value).mValue);
					}

					void setClientVersion(const std::string& value){
						set("clientVersion", amf::object_creator_t(value).mValue);
					}

					void setPassword(const std::string& value){
						set("password", amf::object_creator_t(value).mValue);
					}

					void setUsername(const std::string& value){
						set("username", amf::object_creator_t(value).mValue);
					}

					void setSecurityAnswer(const std::string& value){
						set("securityAnswer", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
