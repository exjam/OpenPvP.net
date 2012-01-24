#pragma once

#include "amf/variant.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class RentableInventoryItem : public amf::Object {
				public:
					RentableInventoryItem(){
						setName("com.riotgames.platform.gameclient.domain.RentableInventoryItem");

						set("winCountRemaining", new amf::Null());
						set("endDate", new amf::Null());
						set("purchaseDate", new amf::Null());
					}

					int getWinCountRemaining(){
						return get("winCountRemaining")->toInt();
					}

					double getEndDate(){
						return get("endDate")->toDouble();
					}

					double getPurchaseDate(){
						return get("purchaseDate")->toDouble();
					}

					void setWinCountRemaining(int value){
						set("winCountRemaining", amf::object_creator_t(value).mValue);
					}

					void setEndDate(double value){
						set("endDate", amf::object_creator_t(value).mValue);
					}

					void setPurchaseDate(double value){
						set("purchaseDate", amf::object_creator_t(value).mValue);
					}
				};
			};
		};
	};
};
