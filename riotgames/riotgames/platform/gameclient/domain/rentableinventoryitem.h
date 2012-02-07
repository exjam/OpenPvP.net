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

						set("winCountRemaining", (amf::Null*)nullptr);
						set("endDate", (amf::Null*)nullptr);
						set("purchaseDate", (amf::Null*)nullptr);
					}

					int getWinCountRemaining() const {
						return get("winCountRemaining");
					}

					double getEndDate() const {
						return get("endDate");
					}

					double getPurchaseDate() const {
						return get("purchaseDate");
					}

					void setWinCountRemaining(int value){
						get("winCountRemaining") = value;
					}

					void setEndDate(double value){
						get("endDate") = value;
					}

					void setPurchaseDate(double value){
						get("purchaseDate") = value;
					}
				};
			};
		};
	};
};
