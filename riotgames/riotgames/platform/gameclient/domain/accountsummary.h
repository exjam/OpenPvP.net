#pragma once

#include "amf/variant.h"
#include "abstractdomainobject.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class AccountSummary : public AbstractDomainObject {
				public:
					AccountSummary(){
						setName("com.riotgames.platform.account.AccountSummary");

						set("summonerName", new amf::Null());
						set("items", new amf::Array());
						set("partnerMode", amf::object_creator_t(false).mValue);
						set("admin", amf::object_creator_t(false).mValue);
						set("hasBetaAccess", amf::object_creator_t(false).mValue);
						set("accountId", new amf::Null());
						set("username", new amf::Null());
						set("needsPasswordReset", amf::object_creator_t(false).mValue);
						set("summonerInternalName", new amf::Null());
						set("groupCount", amf::object_creator_t(0).mValue);
					}

					std::string getSummonerName(){
						return get("summonerName")->toString();
					}

					amf::Array* getItems(){
						return get("items")->toArray();
					}

					bool getPartnerMode(){
						return get("partnerMode")->toBool();
					}

					bool getAdmin(){
						return get("admin")->toBool();
					}

					bool getHasBetaAccess(){
						return get("hasBetaAccess")->toBool();
					}

					double getAccountId(){
						return get("accountId")->toDouble();
					}

					std::string getUsername(){
						return get("username")->toString();
					}

					bool getNeedsPasswordReset(){
						return get("needsPasswordReset")->toBool();
					}

					std::string getSummonerInternalName(){
						return get("summonerInternalName")->toString();
					}

					double getGroupCount(){
						return get("groupCount")->toDouble();
					}

					void setSummonerName(const std::string& value){
						set("summonerName", amf::object_creator_t(value).mValue);
					}

					void setItems(amf::Array* value){
						set("items", (Variant*)value);
					}

					void setPartnerMode(bool value){
						set("partnerMode", amf::object_creator_t(value).mValue);
					}

					void setAdmin(bool value){
						set("admin", amf::object_creator_t(value).mValue);
					}

					void setHasBetaAccess(bool value){
						set("hasBetaAccess", amf::object_creator_t(value).mValue);
					}

					void setAccountId(double value){
						set("accountId", amf::object_creator_t(value).mValue);
					}

					void setUsername(const std::string& value){
						set("username", amf::object_creator_t(value).mValue);
					}

					void setNeedsPasswordReset(bool value){
						set("needsPasswordReset", amf::object_creator_t(value).mValue);
					}

					void setSummonerInternalName(const std::string& value){
						set("summonerInternalName", amf::object_creator_t(value).mValue);
					}

					void setGroupCount(double value){
						set("groupCount", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
