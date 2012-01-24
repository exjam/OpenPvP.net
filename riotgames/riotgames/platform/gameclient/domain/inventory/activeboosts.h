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

						double getIpLoyaltyBoost(){
							return get("ipLoyaltyBoost")->toDouble();
						}

						double getIpBoostPerWinCount(){
							return get("ipBoostPerWinCount")->toDouble();
						}

						double getIpBoostEndDate(){
							return get("ipBoostEndDate")->toDouble();
						}

						double getSummonerId(){
							return get("summonerId")->toDouble();
						}

						double getXpBoostEndDate(){
							return get("xpBoostEndDate")->toDouble();
						}

						double getXpBoostPerWinCount(){
							return get("xpBoostPerWinCount")->toDouble();
						}

						double getXpLoyaltyBoost(){
							return get("xpLoyaltyBoost")->toDouble();
						}

						void setIpLoyaltyBoost(double value){
							((amf::Number*)get("ipLoyaltyBoost"))->setValue(value);
						}

						void setIpBoostPerWinCount(double value){
							((amf::Number*)get("ipBoostPerWinCount"))->setValue(value);
						}

						void setIpBoostEndDate(double value){
							((amf::Number*)get("ipBoostEndDate"))->setValue(value);
						}

						void setSummonerId(double value){
							((amf::Number*)get("summonerId"))->setValue(value);
						}

						void setXpBoostEndDate(double value){
							((amf::Number*)get("xpBoostEndDate"))->setValue(value);
						}

						void setXpBoostPerWinCount(double value){
							((amf::Number*)get("xpBoostPerWinCount"))->setValue(value);
						}

						void setXpLoyaltyBoost(double value){
							((amf::Number*)get("xpLoyaltyBoost"))->setValue(value);
						}
					};
				};
			};
		};
	};
};
