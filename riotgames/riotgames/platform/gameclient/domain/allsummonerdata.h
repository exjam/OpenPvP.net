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

						set("summoner", new amf::Null());
						set("spellBook", new amf::Null());
						set("summonerDefaultSpells", new amf::Null());
						set("summonerTalentsAndPoints", new amf::Null());
						set("summonerLevelAndPoints", new amf::Null());
						set("summonerLevel", new amf::Null());
					}

					Summoner* getSummoner(){
						return (Summoner*)get("summoner")->toObject();
					}

					SpellBook* getSpellBook(){
						return (SpellBook*)get("spellBook")->toObject();
					}

					SummonerDefaultSpells* getSummonerDefaultSpells(){
						return (SummonerDefaultSpells*)get("summonerDefaultSpells")->toObject();
					}

					SummonerTalentsAndPoints* getSummonerTalentsAndPoints(){
						return (SummonerTalentsAndPoints*)get("summonerTalentsAndPoints")->toObject();
					}

					SummonerLevelAndPoints* getSummonerLevelAndPoints(){
						return (SummonerLevelAndPoints*)get("summonerLevelAndPoints")->toObject();
					}

					SummonerLevel* getSummonerLevel(){
						return (SummonerLevel*)get("summonerLevel")->toObject();
					}

					void setSummoner(Summoner* value){
						set("summoner", (Variant*)value);
					}

					void setSpellBook(SpellBook* value){
						set("spellBook", (Variant*)value);
					}

					void setSummonerDefaultSpells(SummonerDefaultSpells* value){
						set("summonerDefaultSpells", (Variant*)value);
					}

					void setSummonerTalentsAndPoints(SummonerTalentsAndPoints* value){
						set("summonerTalentsAndPoints", (Variant*)value);
					}

					void setSummonerLevelAndPoints(SummonerLevelAndPoints* value){
						set("summonerLevelAndPoints", (Variant*)value);
					}

					void setSummonerLevel(SummonerLevel* value){
						set("summonerLevel", (Variant*)value);
					}
				};
			};
		};
	};
};
