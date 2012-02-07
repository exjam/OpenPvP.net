#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				namespace inventory {
					class ActiveBoosts : public amf::Object {
					public:
						ActiveBoosts(){
							setName("com.riotgames.platform.summoner.boost.SummonerActiveBoostsDTO");

							set("ipLoyaltyBoost", new amf::Number());
							set("ipBoostPerWinCount", new amf::Number());
							set("ipBoostEndDate", new amf::Number());
							set("summonerId", new amf::Number());
							set("xpBoostEndDate", new amf::Number());
							set("xpBoostPerWinCount", new amf::Number());
							set("xpLoyaltyBoost", new amf::Number());
						}

						double getIpLoyaltyBoost() const {
							return get("ipLoyaltyBoost");
						}

						double getIpBoostPerWinCount() const {
							return get("ipBoostPerWinCount");
						}

						double getIpBoostEndDate() const {
							return get("ipBoostEndDate");
						}

						double getSummonerId() const {
							return get("summonerId");
						}

						double getXpBoostEndDate() const {
							return get("xpBoostEndDate");
						}

						double getXpBoostPerWinCount() const {
							return get("xpBoostPerWinCount");
						}

						double getXpLoyaltyBoost() const {
							return get("xpLoyaltyBoost");
						}

						void setIpLoyaltyBoost(double value){
							get("ipLoyaltyBoost") = value;
						}

						void setIpBoostPerWinCount(double value){
							get("ipBoostPerWinCount") = value;
						}

						void setIpBoostEndDate(double value){
							get("ipBoostEndDate") = value;
						}

						void setSummonerId(double value){
							get("summonerId") = value;
						}

						void setXpBoostEndDate(double value){
							get("xpBoostEndDate") = value;
						}

						void setXpBoostPerWinCount(double value){
							get("xpBoostPerWinCount") = value;
						}

						void setXpLoyaltyBoost(double value){
							get("xpLoyaltyBoost") = value;
						}
					};
				};
			};
		};
	};
};
