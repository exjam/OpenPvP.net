#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {

				class PlayerParticipant : public amf::Object {
				public:
					PlayerParticipant(){
						setName("com.riotgames.platform.game.PlayerParticipant");

						set("profileIconId", -1);
						set("summonerLevel", (amf::Null*)nullptr);
						set("accountId", (amf::Null*)nullptr);
						set("clientInSynch", (amf::Null*)nullptr);
						set("summonerId", (amf::Null*)nullptr);
						set("lifetimeStatistics", new amf::Array());
					}

					int getProfileIconId() const {
						return get("profileIconId");
					}

					double getSummonerLevel() const {
						return get("summonerLevel");
					}

					double getAccountId() const {
						return get("accountId");
					}

					bool getClientInSynch() const {
						return get("clientInSynch");
					}

					double getSummonerId() const {
						return get("summonerId");
					}

					const amf::Reference<amf::Array> getLifetimeStatistics() const {
						return get("lifetimeStatistics");
					}

					void setProfileIconId(int value){
						get("profileIconId") = value;
					}

					void setSummonerLevel(double value){
						get("summonerLevel") = value;
					}

					void setAccountId(double value){
						get("accountId") = value;
					}

					void setClientInSynch(bool value){
						get("clientInSynch") = value;
					}

					void setSummonerId(double value){
						get("summonerId") = value;
					}

					void setLifetimeStatistics(amf::Array* value){
						get("lifetimeStatistics") = value;
					}
				};
			};
		};
	};
};
