#include "riotgames/platform/common/services/loginservice.h"
#include "riotgames/platform/common/services/messagerouterservice.h"
#include "riotgames/platform/gameclient/services/matchmakerservice.h"
#include "riotgames/platform/gameclient/services/clientfacadeservice.h"
#include "riotgames/platform/gameclient/domain/systemstates/clientsystemstatesnotification.h"
#include "riotgames/platform/gameclient/domain/broadcast/broadcastnotification.h"

namespace riotgames {
	namespace platform {
		namespace common {
			namespace services {
				LoginService loginService;
				MessageRouterService messageRouterService;
			};
		};

		namespace gameclient {
			namespace services {
				ClientFacadeService clientFacadeService;
				MatchMakerService matchmakerService;
			};

			namespace domain {
				namespace broadcast {
					BroadcastNotificationExt broadcastNotificationExt;
				};

				namespace systemstates {
					ClientSystemStatesNotificationExt clientSystemStatesNotificationExt;
				};
			};
		};
	};
};
