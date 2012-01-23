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

						set("ipAddress", new amf::Null());
						set("offense", new amf::Null());
						set("gameId", new amf::Null());
						set("reportSource", new amf::Null());
						set("reportingSummonerId", new amf::Null());
						set("reportedSummonerId", new amf::Null());
						set("comment", new amf::Null());
					}

					std::string getIpAddress(){
						return get("ipAddress")->toString();
					}

					std::string getOffense(){
						return get("offense")->toString();
					}

					double getGameId(){
						return get("gameId")->toDouble();
					}

					std::string getReportSource(){
						return get("reportSource")->toString();
					}

					double getReportingSummonerId(){
						return get("reportingSummonerId")->toDouble();
					}

					double getReportedSummonerId(){
						return get("reportedSummonerId")->toDouble();
					}

					std::string getComment(){
						return get("comment")->toString();
					}

					void setIpAddress(const std::string& value){
						set("ipAddress", amf::object_creator_t(value).mValue);
					}

					void setOffense(const std::string& value){
						set("offense", amf::object_creator_t(value).mValue);
					}

					void setGameId(double value){
						set("gameId", amf::object_creator_t(value).mValue);
					}

					void setReportSource(const std::string& value){
						set("reportSource", amf::object_creator_t(value).mValue);
					}

					void setReportingSummonerId(double value){
						set("reportingSummonerId", amf::object_creator_t(value).mValue);
					}

					void setReportedSummonerId(double value){
						set("reportedSummonerId", amf::object_creator_t(value).mValue);
					}

					void setComment(const std::string& value){
						set("comment", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
