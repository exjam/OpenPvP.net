#pragma once

#include "flex/services.h"
#include "../domain/authenticationcredentials.h"

namespace riotgames {
	namespace platform {
		namespace common {
			namespace services {
				using namespace riotgames::platform::common::domain;

				class LoginService : private flex::messaging::services::Service {
				public:
					LoginService()
						: flex::messaging::services::Service("loginService")
					{
					}

					void performLCDSHeartBeat(double param1, const std::string& param2, int param3, const std::string& param4, const rtmp::CommandCallback& callback){
						invoke("performLCDSHeartBeat", callback, &amf::Number(param1), &amf::String(param2), &amf::Integer(param3), &amf::String(param4));
					}

					void getLoggedInAccountView(const rtmp::CommandCallback& callback){
						invoke("getLoggedInAccountView", callback);
					}

					void login(const std::string& username, const std::string& password, const std::string& authToken, const std::string& domain, const std::string& ipAddress, const std::string& locale, const std::string& clientVersion, const rtmp::CommandCallback& callback){
						AuthenticationCredentials auth;
						auth.setUsername(username);
						auth.setPassword(password);
						auth.setAuthToken(authToken);
						auth.setDomain(domain);
						auth.setIpAddress(ipAddress);
						auth.setLocale(locale);
						auth.setClientVersion(clientVersion);
						invoke("login", callback, &auth);
					}

					void logout(const std::string& param1, const rtmp::CommandCallback& callback){
						invoke("logout", callback, &amf::String(param1));
					}

					void getStoreUrl(const rtmp::CommandCallback& callback){
						invoke("getStoreUrl", callback);
					}

					void authenticateChannel(const std::string& param1, const std::string& param2, const rtmp::CommandCallback& callback){
						invoke("authenticateChannel", callback, &amf::String(param1), &amf::String(param2));
					}

					/*
					void loginWithSuppliedCredentials(const std::string& param1, const std::string& param2, const std::string& param3, const std::string& param4, const std::string& param5, const std::string& param6, const std::string& param7, const rtmp::CommandCallback& callback){
						invoke("loginWithSuppliedCredentials", callback, &amf::String(param1), &amf::String(param2), &amf::String(param3), &amf::String(param4), &amf::String(param5), &amf::String(param6), &amf::String(param7));
					}
					*/
				};

				extern LoginService loginService;
			};
		};
	};
};
