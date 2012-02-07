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

						set("summonerName", (amf::Null*)nullptr);
						set("items", new amf::Array());
						set("partnerMode", false);
						set("admin", false);
						set("hasBetaAccess", false);
						set("accountId", (amf::Null*)nullptr);
						set("username", (amf::Null*)nullptr);
						set("needsPasswordReset", false);
						set("summonerInternalName", (amf::Null*)nullptr);
						set("groupCount", 0);
					}

					std::string getSummonerName() const {
						return get("summonerName");
					}

					const amf::Reference<amf::Array> getItems() const {
						return get("items");
					}

					bool getPartnerMode() const {
						return get("partnerMode");
					}

					bool getAdmin() const {
						return get("admin");
					}

					bool getHasBetaAccess() const {
						return get("hasBetaAccess");
					}

					double getAccountId() const {
						return get("accountId");
					}

					std::string getUsername() const {
						return get("username");
					}

					bool getNeedsPasswordReset() const {
						return get("needsPasswordReset");
					}

					std::string getSummonerInternalName() const {
						return get("summonerInternalName");
					}

					double getGroupCount() const {
						return get("groupCount");
					}

					void setSummonerName(const std::string& value){
						get("summonerName") = value;
					}

					void setItems(amf::Array* value){
						get("items") = value;
					}

					void setPartnerMode(bool value){
						get("partnerMode") = value;
					}

					void setAdmin(bool value){
						get("admin") = value;
					}

					void setHasBetaAccess(bool value){
						get("hasBetaAccess") = value;
					}

					void setAccountId(double value){
						get("accountId") = value;
					}

					void setUsername(const std::string& value){
						get("username") = value;
					}

					void setNeedsPasswordReset(bool value){
						get("needsPasswordReset") = value;
					}

					void setSummonerInternalName(const std::string& value){
						get("summonerInternalName") = value;
					}

					void setGroupCount(double value){
						get("groupCount") = value;
					}
				};
			};
		};
	};
};
