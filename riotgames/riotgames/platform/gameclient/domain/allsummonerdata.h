#pragma once

#include "amf/variant.h"
#include "summoner.h"
#include "spellbook.h"
#include "summonerlevel.h"
#include "summonerdefaultspells.h"
#include "summonerlevelandpoints.h"
#include "summonertalentsandpoints.h"

namespace riotgames {
	namespace platform {
		namespace gameclient {
			namespace domain {
				class AllSummonerData : public amf::Object {
				public:
					AllSummonerData(){
						setName("com.riotgames.platform.summoner.AllSummonerData");

						set("summoner", (amf::Null*)nullptr);
						set("spellBook", (amf::Null*)nullptr);
						set("summonerDefaultSpells", (amf::Null*)nullptr);
						set("summonerTalentsAndPoints", (amf::Null*)nullptr);
						set("summonerLevelAndPoints", (amf::Null*)nullptr);
						set("summonerLevel", (amf::Null*)nullptr);
					}

					const amf::Reference<Summoner> getSummoner() const {
						return get("summoner").toObject();
					}

					const amf::Reference<SpellBook> getSpellBook() const {
						return get("spellBook").toObject();
					}

					const amf::Reference<SummonerDefaultSpells> getSummonerDefaultSpells() const {
						return get("summonerDefaultSpells").toObject();
					}

					const amf::Reference<SummonerTalentsAndPoints> getSummonerTalentsAndPoints() const {
						return get("summonerTalentsAndPoints").toObject();
					}

					const amf::Reference<SummonerLevelAndPoints> getSummonerLevelAndPoints() const {
						return get("summonerLevelAndPoints").toObject();
					}

					const amf::Reference<SummonerLevel> getSummonerLevel() const {
						return get("summonerLevel").toObject();
					}

					void setSummoner(Summoner* value){
						get("summoner") = value;
					}

					void setSpellBook(SpellBook* value){
						get("spellBook") = value;
					}

					void setSummonerDefaultSpells(SummonerDefaultSpells* value){
						get("summonerDefaultSpells") = value;
					}

					void setSummonerTalentsAndPoints(SummonerTalentsAndPoints* value){
						get("summonerTalentsAndPoints") = value;
					}

					void setSummonerLevelAndPoints(SummonerLevelAndPoints* value){
						get("summonerLevelAndPoints") = value;
					}

					void setSummonerLevel(SummonerLevel* value){
						get("summonerLevel") = value;
					}
				};
			};
		};
	};
};
