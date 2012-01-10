//out of date
/*
{ object com.riotgames.platform.account.AccountSummary
	accountId = 3.22884e+007
	admin = false
	dataVersion = 0
	futureData = (null)
	groupCount = 0
	hasBetaAccess = true
	needsPasswordReset = false
	partnerMode = false
	summonerInternalName = (null)
	summonerName = (null)
	username = "***"
}
*/

#include "amf/amf.h"

namespace riotgames {
	namespace platform {
		namespace login {
			class Session : public amf::ObjectWrapper {
			public:
				Session(amf::Object* obj)
					: amf::ObjectWrapper(obj)
				{
				}

				amf::Object* accountSummary(){
					return mObject->getProperty("accountSummary")->asObject();
				}

				const std::string& password(){
					return mObject->getProperty("password")->asString();
				}

				const std::string& token(){
					return mObject->getProperty("token")->asString();
				}

				void setAccountSummary(amf::Object* value){
					mObject->set("accountSummary", value);
				}

				void setPassword(const std::string& value){
					mObject->set("password", value);
				}

				void setToken(const std::string& value){
					mObject->set("token", value);
				}

			private:
				void init(){
					setAccountSummary(nullptr);
					setPassword("");
					setToken("");
				}
			};

/*
public class AuthenticationCredentials extends Object
{
public var partnerCredentials:String;
public var oldPassword:String;
public var domain:String;
public var ipAddress:String;
public var authToken:String;
public var locale:String;
public var clientVersion:String;
public var password:String;
public var username:String;
public var securityAnswer:String;
}
*/
			class AuthenticationCredentials : public amf::ObjectWrapper {
			public:
				AuthenticationCredentials(amf::Object* obj)
					: amf::ObjectWrapper(obj)
				{
				}

				const std::string& authToken(){
					return mObject->getProperty("authToken")->asString();
				}

				const std::string& clientVersion(){
					return mObject->getProperty("clientVersion")->asString();
				}

				const std::string& domain(){
					return mObject->getProperty("domain")->asString();
				}

				const std::string& ipAddress(){
					return mObject->getProperty("ipAddress")->asString();
				}

				const std::string& locale(){
					return mObject->getProperty("locale")->asString();
				}

				const std::string& oldPassword(){
					return mObject->getProperty("oldPassword")->asString();
				}

				const std::string& partnerCredentials(){
					return mObject->getProperty("partnerCredentials")->asString();
				}

				const std::string& password(){
					return mObject->getProperty("password")->asString();
				}

				const std::string& securityAnswer(){
					return mObject->getProperty("securityAnswer")->asString();
				}

				const std::string& username(){
					return mObject->getProperty("username")->asString();
				}

				void setAuthToken(const std::string& value){
					mObject->set("authToken", value);
				}

				void setClientVersion(const std::string& value){
					mObject->set("clientVersion", value);
				}

				void setDomain(const std::string& value){
					mObject->set("domain", value);
				}

				void setIpAddress(const std::string& value){
					mObject->set("ipAddress", value);
				}

				void setLocale(const std::string& value){
					mObject->set("locale", value);
				}

				void setOldPassword(const std::string& value){
					mObject->set("oldPassword", value);
				}

				void setPartnerCredentials(const std::string& value){
					mObject->set("partnerCredentials", value);
				}

				void setPassword(const std::string& value){
					mObject->set("password", value);
				}

				void setSecurityAnswer(const std::string& value){
					mObject->set("securityAnswer", value);
				}

				void setUsername(const std::string& value){
					mObject->set("username", value);
				}

			private:
				void init(){
					setAuthToken("");
					setClientVersion("1.50.11_12_20_17_53");
					setDomain("lolclient.lol.riotgames.com");
					setIpAddress("");
					setLocale("en_US");
					setOldPassword("");
					setPartnerCredentials("");
					setPassword("");
					setSecurityAnswer("");
					setUsername("");
				}
			};
		};
	};
};
