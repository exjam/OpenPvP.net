#include "riotgames/platform/common/services/loginservice.h"
#include "riotgames/platform/common/services/messagerouterservice.h"
#include "riotgames/platform/common/services/inventoryservice.h"
#include "riotgames/platform/gameclient/services/matchmakerservice.h"
#include "riotgames/platform/gameclient/services/clientfacadeservice.h"
#include "riotgames/platform/gameclient/services/teamservice.h"
#include "riotgames/platform/gameclient/services/summonerruneservice.h"
#include "riotgames/platform/gameclient/domain/systemstates/clientsystemstatesnotification.h"
#include "riotgames/platform/gameclient/domain/broadcast/broadcastnotification.h"

namespace riotgames {
	namespace platform {
		namespace common {
			namespace services {
				LoginService loginService;
				MessageRouterService messageRouterService;
				InventoryService inventoryService;
			};
		};

		namespace gameclient {
			namespace services {
				ClientFacadeService clientFacadeService;
				MatchMakerService matchmakerService;
				SummonerRuneService summonerRuneService;
				TeamService summonerTeamService;
			};
		};
	};
};

namespace riotgames {
	void init(){
		using namespace platform::gameclient::domain::broadcast;
		using namespace platform::gameclient::domain::systemstates;

		BroadcastNotificationExt* broadcastNotificationExt = new BroadcastNotificationExt();
		ClientSystemStatesNotificationExt* clientSystemStatesNotificationExt = new ClientSystemStatesNotificationExt();
	}
};