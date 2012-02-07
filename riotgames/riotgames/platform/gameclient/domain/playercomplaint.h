#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class PlayerComplaint : public amf::Object {
				public:
					PlayerComplaint(){
						setName("com.riotgames.platform.gameclient.domain.PlayerComplaint");

						set("ipAddress", (amf::Null*)nullptr);
						set("offense", (amf::Null*)nullptr);
						set("gameId", (amf::Null*)nullptr);
						set("reportSource", (amf::Null*)nullptr);
						set("reportingSummonerId", (amf::Null*)nullptr);
						set("reportedSummonerId", (amf::Null*)nullptr);
						set("comment", (amf::Null*)nullptr);
					}

					std::string getIpAddress() const {
						return get("ipAddress");
					}

					std::string getOffense() const {
						return get("offense");
					}

					double getGameId() const {
						return get("gameId");
					}

					std::string getReportSource() const {
						return get("reportSource");
					}

					double getReportingSummonerId() const {
						return get("reportingSummonerId");
					}

					double getReportedSummonerId() const {
						return get("reportedSummonerId");
					}

					std::string getComment() const {
						return get("comment");
					}

					void setIpAddress(const std::string& value){
						get("ipAddress") = value;
					}

					void setOffense(const std::string& value){
						get("offense") = value;
					}

					void setGameId(double value){
						get("gameId") = value;
					}

					void setReportSource(const std::string& value){
						get("reportSource") = value;
					}

					void setReportingSummonerId(double value){
						get("reportingSummonerId") = value;
					}

					void setReportedSummonerId(double value){
						get("reportedSummonerId") = value;
					}

					void setComment(const std::string& value){
						get("comment") = value;
					}
				};
			};
		};
	};
};
